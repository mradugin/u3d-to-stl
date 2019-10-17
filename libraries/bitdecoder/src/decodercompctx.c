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

#include "decoderctx.h"

U32 cReadCount[]	 = {4, 3, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0};
U32 cFastNotMask[] = {0xFFFFFFFF, 0x7FFF7FFF, 0x3FFF3FFF, 0x1FFF1FFF,
							0x0FFF0FFF};
U8  cSwap8Dec[]    = {0, 8, 4, 12, 2, 10, 6, 14, 
    				  1, 9, 5, 13, 3, 11, 7, 15};

U32 cHalfMask				= 0x80008000;
U32 cNotHalfMask			= 0x7FFF7FFF;
U32 cQuarterMask			= 0x40004000;
U32 cNotThreeQuarterMask	= 0x3FFF3FFF;

/**
 * u3dDecoderCreateCompCtx @brief U3D Bitstream decoder function to create 
 * compressed context
 * 
 * @b Purpose \n
 *      create a dynaimic compressed context to read compressed value from 
 *		bitstream by using u3dGetDyamicCompU16() and u3dGetDynamicCompU8() 
 *		functions
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to associate compression context with
 *  @param compCtxID (out) the ID of compressed context 
 * @return
 *      Status of creating compressed context for decoder context
 *      @retval u3dStsNoErr if the compressed context was successfully 
 *              created and associated with decoder context
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *      @retval u3dStsNotSupportedErr if compression context isn't available
 *              for specified @e pCtx
 * @note
 *  Created compression context can be release by calling 
 *  u3dDecoderReleaseCompCtx() function. All compression contexts that 
 *  associated with decoder context will be automatically released during 
 *  delete decoder context. See u3dDecoderDelete().
 */
U3D_METHOD(U3dStatus, u3dDecoderCreateCompCtx,(    
    U3dDecoder*     pCtx, 
    U3DCompCtxID*   compCtxID
    ))
{
    U32			index;
    U3dStatus	rez;
    
    *compCtxID  = 0;
    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DDECODERCTX_ID) {
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
    pCtx->compCtx[index].inuse  = 1;
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
} /* u3dDecoderCreateCompCtx */

/*
 * u3dDecoderReleaseCompCtx @brief U3D Bitstream decoder function to release 
 * compressed context
 * 
 * @b Purpose \n
 *      release an compressed context that associated with decoder
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to associate compression context with
 *  @param compCtxID (in) the ID of compressed context to be released
 * @return
 *      Status of releasing compressed context for decoder context
 *      @retval u3dStsNoErr if the compressed context was successfully 
 *              released from decoder context
 *      @retval u3dStsContextMatchErr if pCtx or compCtxId isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_METHOD(U3dStatus, u3dDecoderReleaseCompCtx,(    
    U3dDecoder*     pCtx, 
    U3DCompCtxID    compCtxID
    ))
{
    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DDECODERCTX_ID) {
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
        pCtx->compCtx[compCtxID].inuse      = 0;
        if(pCtx->compCtxLast == compCtxID && compCtxID != 1) {
            pCtx->compCtxLast--;
        } /* if */
    } else {
        return u3dStsBadArgErr;
    } /* if */
    
    return u3dStsNoErr;
} /* u3dDecoderReleaseCompCtx */


