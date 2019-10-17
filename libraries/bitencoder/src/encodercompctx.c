//***************************************************************************
//
//  Copyright (c) 1999 - 2006 Intel Corporation
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//***************************************************************************
//

#include "encoderctx.h"
U8 cSwap8[]	     = {0, 8, 4, 12, 2, 10, 6, 14, 
					1, 9, 5, 13, 3, 11, 7, 15};

/**
 * u3dEncoderCreateCompCtx @brief U3D Bitstream encoder function to create 
 * compressed context
 * 
 * @b Purpose \n
 *      create an compressed context to write compressed value to bitstream by
 *      using u3dAddCompressedU16() and u3dAddCompressedU8() functions
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be used to associate compression context with
 *  @param compCtxID (out) the ID of compressed context 
 * @return
 *      Status of creating compressed context for encoder context
 *      @retval u3dStsNoErr if the dynamic compressed context was successfully 
 *              created and associated with encoder context
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *      @retval u3dStsNoMemErr if system cannot allocate enough memory to
 *              create compresion context for u3dCompessionDynamic @e mode
 *      @retval u3dStsNotSupportedErr if compression context isn't available
 *              for specified @e pCtx
 * @note
 *  Created compression context can be release by calling 
 *  u3dEncoderReleaseCompCtx() function. All compression contexts that 
 *  associated with encoder context will be automatically released during 
 *  delete encoder context. See u3dEncoderDelete().
 *  @e compCtxID will equal 0 in case of impossibility to create compression 
 *  context.
 */
U3D_METHOD(U3dStatus, u3dEncoderCreateCompCtx,(    
    U3dEncoder*     pCtx, 
    U3DCompCtxID*   compCtxID
    ))
{
    U3dStatus   rez;
    U32			index;
    
    *compCtxID  = 0;
    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DENCODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */
    if(pCtx->compCtx == 0) {
        return u3dStsNotSupportedErr;
    } /* if */

    for(index = 1; index < pCtx->compCtxLast; index++) {
        if(pCtx->compCtx[index].inuse == 0) {
            break;
        } /* if */
    } /* for */
    if(index == pCtx->compCtxAllocatedSize) {
        //reallocate compCtx buffer
		/* Create CompCtxes */
		U3DCompCtx*	newCompCtx;
		U32			size = 0;

		size    = sizeof(U3DCompCtx)*(NUM_DYNAMIC_COMPCTX + 
									  pCtx->compCtxAllocatedSize);
		newCompCtx	= (U3DCompCtx*)pCtx->memUtls.alloc(pCtx->memUtls.pCtx, size);
		if(newCompCtx == 0) {
			return u3dStsNoMemErr;
		} /* if */
		pCtx->compCtxAllocatedSize += NUM_DYNAMIC_COMPCTX;
		// copy old data
		for(index = 0; index < pCtx->compCtxLast; index++) {
			newCompCtx[index].histogram = pCtx->compCtx[index].histogram;
			newCompCtx[index].inuse = 1;
		} /* for */
		for(; index < pCtx->compCtxAllocatedSize; index++) {
			newCompCtx[index].histogram = 0;
			newCompCtx[index].inuse = 0;
		} /* for */
		pCtx->memUtls.free(pCtx->memUtls.pCtx, pCtx->compCtx);
		pCtx->compCtx	= newCompCtx;
		index			= pCtx->compCtxLast;
    } /* if */
    /* Init Dynamic CompCtx */
    rez = u3dHistogramDynamicInit(&(pCtx->compCtx[index].histogram),
                                    &pCtx->memUtls,
                                    u3dDynamicHistogramU16,
                                    0x1FFF);
    if(rez != u3dStsNoErr) {
        return rez;
    } /* if */
	pCtx->compCtx[index].inuse = 1;
    /* initial histogram for a dynamic context: 
     *                                 escape symbol frequency = 1 
     */
    rez = u3dHistogramDynamicAddSymbol(pCtx->compCtx[index].histogram, 0);
    if(rez != u3dStsNoErr) {
        return rez;
    } /* if */
    *compCtxID  = index;
	if(pCtx->compCtxLast == index) {
		pCtx->compCtxLast++;
	} /* if */
    
    return u3dStsNoErr;
} /* u3dEncoderCreateCompCtx */

/**
 * u3dEncoderReleaseCompCtx @brief U3D Bitstream encoder function to release 
 * compressed context
 * 
 * @b Purpose \n
 *      release an compressed context that associated with encoder
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be used to associate compression context with
 *  @param compCtxID (in) the ID of compressed context to be released
 * @return
 *      Status of releasing compressed context for encoder context
 *      @retval u3dStsNoErr if the compressed context was successfully 
 *              released from encoder context
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *      @retval u3dStsBadArgErr if @e compCtxID wasn't associated with @e pCtx 
 */
U3D_METHOD(U3dStatus, u3dEncoderReleaseCompCtx,(    
    U3dEncoder*     pCtx, 
    U3DCompCtxID    compCtxID
    ))
{
    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DENCODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */
    if(pCtx->compCtx == 0) {
        return u3dStsContextMatchErr;
    } /* if */
    if(compCtxID > pCtx->compCtxLast) {
        return u3dStsBadArgErr;
    } /* if */
    
    if(pCtx->compCtx[compCtxID].inuse) {
        if(pCtx->compCtx[compCtxID].histogram) {
            u3dHistogramDynamicDelete(pCtx->compCtx[compCtxID].histogram);
        } /* if */
        pCtx->compCtx[compCtxID].histogram  = 0;
		pCtx->compCtx[compCtxID].inuse		= 0;

        if(pCtx->compCtxLast == compCtxID && compCtxID != 0) {
            pCtx->compCtxLast--;
        } /* if */
    } else {
        return u3dStsBadArgErr;
    } /* if */
    
    return u3dStsNoErr;
} /* u3dEncoderReleaseCompCtx */
