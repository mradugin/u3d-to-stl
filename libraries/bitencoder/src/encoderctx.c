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

#ifndef U3D_ENCODERBE
U8 c64En[]	     = { 0, 1, 2, 3, 4, 5, 6, 7};
U8 c32En[]	     = { 0, 1, 2, 3};
U8 c24En[]	     = { 0, 1, 2};
U8 c16En[]	     = { 0, 1};
#else
U8 c64En[]	     = { 7, 6, 5, 4, 3, 2, 1, 0};
U8 c32En[]	     = { 3, 2, 1, 0};
U8 c24En[]	     = { 2, 1, 0};
U8 c16En[]	     = { 1, 0};
#endif

/*
 * U3D Bitstream encoder function u3dEncoderInit
 * Purpose
 *      Create an instance of the U3D encoder.
 *  Parameters
 *  (out)pCtx - the pointer to the variable which will be initialized with the
 *              pointer to new U3D encoder
 *  (in)pMemUtls - the pointer to the user defined memory management service
 *  (in)pStreamCtx - the pointer to the user defined stream context
 *  (in)cbWrite - callback function pointer that will be used to serialize data
 *  (in)limitSize - the maximum size of buffer that can be written at one call 
 *                  of cbWrite function
 *  Return
 *      u3dStsNoErr if initialization was successful.
 *      u3dStsNullPtrErr if pCtx or pMemUtls are null
 *      u3dStsBadArgErr if pMemUtls doesn't contain valid pointers to alloc and
 *          free function (see OxlMemory). And if cbWrite is 0 pointer also if 
 *          limitSize < 10
 *      u3dStsNoMemErr if system cannot allocate enough memory.
 *  Notes
 *      u3dEncoderInit is the only way to instantiate the U3D encoder, so it 
 *      must be the first function in the calling sequence.
 *      u3dEncoderDelete must be invoked in order to delete each object created
 *      by u3dEncoderInit function.
 */
U3D_METHOD(U3dStatus, u3dEncoderInit,(
    U3dEncoder**    pCtx,
    U3dMemory       *pMemUtls,
    U3dStream_cbCtx *pStreamCtx,
    U3dCb_Write     cbWrite,
    U64             limitSize))
{
    U32     size = sizeof(U3dEncoder);
    U32     sizebitstream = 0;
    U32     index;

    if(pCtx == 0 || pMemUtls == 0 || cbWrite == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pMemUtls->alloc == 0 || pMemUtls->free == 0 || limitSize < 10) {
        *pCtx   = 0;
        return u3dStsBadArgErr;
    } /* if */
    sizebitstream   = 0x100000; // 1048576 values
    if(sizebitstream > limitSize) {
		sizebitstream = (U32)limitSize;
    } /* if */
    size        += (sizebitstream) * sizeof(U8);
    *pCtx       = (U3dEncoder*)pMemUtls->alloc(pMemUtls->pCtx, size);
    if(*pCtx == 0) {
        return u3dStsNoMemErr;
    }
    (*pCtx)->id                     = U3DENCODERCTX_ID;

    (*pCtx)->memUtls.pCtx           = pMemUtls->pCtx;
    (*pCtx)->memUtls.alloc          = pMemUtls->alloc;
    (*pCtx)->memUtls.realloc        = pMemUtls->realloc;
    (*pCtx)->memUtls.free           = pMemUtls->free;

    (*pCtx)->pStreamCtx             = pStreamCtx;
    (*pCtx)->cbWrite                = cbWrite;

    (*pCtx)->bitstreamallocated     = ((U8*)(*pCtx) + sizeof(U3dEncoder));
    (*pCtx)->bitstreamallocatedsize = sizebitstream;
    (*pCtx)->limitSize              = limitSize;
    (*pCtx)->bitstreamposition      = (*pCtx)->bitstreamallocated;
    (*pCtx)->bitstreamlastposition  = (*pCtx)->bitstreamallocated + 
                                      (sizebitstream - 1)* sizeof(U8);
    (*pCtx)->bitshift               = 0;

	/* Create CompCtxes and make first empty to handle errors */
    size    = sizeof(U3DCompCtx)*(NUM_DYNAMIC_COMPCTX + 1);
    (*pCtx)->compCtx    = (U3DCompCtx*)pMemUtls->alloc(pMemUtls->pCtx, size);
    if((*pCtx)->compCtx == 0) {
        (*pCtx)->id    = 0xFFFF;
        (*pCtx)->memUtls.free((*pCtx)->memUtls.pCtx, *pCtx);
        return u3dStsNoMemErr;
    } /* if */
    /* Init All CompCtxes */
    (*pCtx)->high                 = 0x0000FFFF;
    (*pCtx)->low                  = 0x00000000;
    (*pCtx)->underflowCount       = 0;
    (*pCtx)->compCtxAllocatedSize = NUM_DYNAMIC_COMPCTX + 1;
    (*pCtx)->compCtxLast          = 1;

    for(index = 0; index < (*pCtx)->compCtxAllocatedSize; index++) {
        (*pCtx)->compCtx[index].inuse           = 0;
        (*pCtx)->compCtx[index].histogram       = 0;
    } /* for */
#ifdef U3D_LOGENCODER
	(*pCtx)->logFile	= fopen("u3dencoder.log", "wt");
#endif
    return u3dStsNoErr;
} /* u3dEncoderInit */

/*
 * U3D Bitstream encoder function u3dEncoderFlush
 * Purpose
 *      Force to flush the bitstream to user defined writer callbacks
 *  Parameters
 *  (in)pCtx - the pointer to the encoder context of bitstream that should be
 *             flushed
 *  Return
 *      u3dStsNoErr if the bitstream was successfully flushed.
 *      u3dStsNullPtrErr if pCtx is null.
 *      u3dStsContextMatchErr if pCtx isn't valid
 *      u3dStsStreamOpErr if error in the stream's callback when cbWriten 
 *      returned 0 or value that exiceed size byte to write
 *  Notes
 *      u3dEncoderFlush reset the bitstream encoder context to initial state by
 *      filling necessary zero pading data to the end stream and writing it to 
 *      user defined stream through corresponding writing callback function
*/
U3D_METHOD(U3dStatus, u3dEncoderFlush,(U3dEncoder* pCtx))
{
	U3dStatus status = u3dStsNoErr;

    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DENCODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */
	if(0xFFFF != pCtx->high || 0 != pCtx->low  || 0 != pCtx->underflowCount) {
		status = intAddU16(pCtx, 0);
		if(status == u3dStsNoErr)
			status = intAddU16(pCtx, 0);
	}  /* if */

	if(status == u3dStsNoErr) {
		status	= intEncoderFlush(pCtx);
	} /* if */

    return status;
} /* u3dEncoderFlush */

INT_METHOD(U3dStatus, intEncoderFlush,(U3dEncoder* pCtx))
{
    U64     writtenByte = 0;
    U64     toWriteByte = 0;

    // make zero padding
    if(pCtx->bitstreamposition < pCtx->bitstreamlastposition &&
       pCtx->bitshift) {
        pCtx->bitstreamposition++;
	} /* if */
    // write data
    toWriteByte    = pCtx->bitstreamposition - pCtx->bitstreamallocated;
    for(;writtenByte < toWriteByte;toWriteByte -= writtenByte){
         writtenByte = pCtx->cbWrite(pCtx->pStreamCtx, 
                                     pCtx->bitstreamallocated, 
                                     toWriteByte);
         if(writtenByte == 0 || writtenByte > toWriteByte) {
             return u3dStsStreamOpErr;
         } /* if */
    } /* for */

    // reset position
    pCtx->bitstreamposition      = pCtx->bitstreamallocated;
    pCtx->bitshift               = 0;

    return u3dStsNoErr;
} /* intEncoderFlush */

/*
 * U3D Bitstream encoder function u3dEncoderDelete
 * Purpose
 *      Delete an instance of the U3D encoder.
 *  Parameters
 *  (in)pCtx - the pointer to the encoder context to be deleted
 *  Return
 *      u3dStsNoErr if the object was successfully deleted.
 *      u3dStsNullPtrErr if pCtx is null.
 *      u3dStsContextMatchErr if pCtx isn't valid
 */
U3D_METHOD(U3dStatus, u3dEncoderDelete,(U3dEncoder* pCtx))
{
    U32 index;
    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DENCODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */

#ifdef U3D_LOGENCODER
	fclose(pCtx->logFile);
#endif

    /* Delete CompCtxes */
    if(pCtx->compCtx && pCtx->compCtxAllocatedSize) {
        /* Delete histogram from dynamic context */
        for(index = 0; index < pCtx->compCtxAllocatedSize; index++) {
           if(pCtx->compCtx[index].histogram) {
               u3dHistogramDynamicDelete(pCtx->compCtx[index].histogram);
               pCtx->compCtx[index].histogram = 0;
           } /* if */
        } /* for */
        pCtx->memUtls.free(pCtx->memUtls.pCtx, pCtx->compCtx);
        pCtx->compCtx               = 0;
        pCtx->compCtxAllocatedSize  = 0;
    } /* if */

    pCtx->id    = 0xFFFF;
    pCtx->memUtls.free(pCtx->memUtls.pCtx, pCtx);

    return u3dStsNoErr;
} /* u3dEncoderDelete */

