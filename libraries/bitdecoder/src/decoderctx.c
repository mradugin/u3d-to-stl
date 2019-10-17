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

#ifndef U3D_DECODERBE
U32 c64De[]        = { 0, 1, 2, 3, 4, 5, 6, 7};
U32 c32De[]        = { 0, 1, 2, 3};
U32 c24De[]        = { 0, 1, 2};
U32 c16De[]        = { 0, 1};
#else
U32 c64De[]        = { 7, 6, 5, 4, 3, 2, 1, 0};
U32 c32De[]        = { 3, 2, 1, 0};
U32 c24De[]        = { 2, 1, 0};
U32 c16De[]        = { 1, 0};
#endif

/*
 * U3D Bitstream decoder function u3dDecoderInit
 * Purpose
 *      Create an instance of the U3D decoder.
 *  Parameters
 *  (out)pCtx - the pointer to the variable which will be initialized with the
 *              pointer to new U3D decoder
 *  (in)pMemUtls - the pointer to the user defined memory management service
 *  (in)pStreamCtx - the pointer to the user defined stream context
 *  (in)cbMap - callback function pointer that will be used to get data
 *  Return
 *      u3dStsNoErr if initialization was successful.
 *      u3dStsNullPtrErr if pCtx or pMemUtls are null.
 *      u3dStsBadArgErr if pMemUtls doesn't contain valid pointers to alloc and
 *          free function (see OxlMemory). And if cbMap is 0 pointer
 *      u3dStsNoMemErr if system cannot allocate enough memory.
 *  Notes
 *      u3dDecoderInit is the only way to instantiate the U3D decoder, so it 
 *      must be the first function in the calling sequence.
 *      u3dDecoderDelete must be invoked in order to delete each object created
 *      by u3dDecoderInit function.
 */
U3D_METHOD(U3dStatus, u3dDecoderInit,(
    U3dDecoder**    pCtx,
    U3dMemory       *pMemUtls,
    U3dStream_cbCtx *pStreamCtx,
    U3dCb_Map       cbMap))
{
    U32     size = sizeof(U3dDecoder);
    U64     rez;
    U32     index;

    if(pCtx == 0 || pMemUtls == 0 || cbMap == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pMemUtls->alloc == 0 || pMemUtls->free == 0) {
        *pCtx   = 0;
        return u3dStsBadArgErr;
    } /* if */

    *pCtx   = (U3dDecoder*)pMemUtls->alloc(pMemUtls->pCtx, size);
    if(*pCtx == 0) {
        return u3dStsNoMemErr;
    }
    (*pCtx)->id                     = U3DDECODERCTX_ID;

    (*pCtx)->memUtls.pCtx           = pMemUtls->pCtx;
    (*pCtx)->memUtls.alloc          = pMemUtls->alloc;
    (*pCtx)->memUtls.realloc        = pMemUtls->realloc;
    (*pCtx)->memUtls.free           = pMemUtls->free;

    (*pCtx)->pStreamCtx             = pStreamCtx;
    (*pCtx)->cbMap                  = cbMap;

    (*pCtx)->bitstreamallocated     = 0;
    (*pCtx)->bitstreamallocatedsize = 0;
    (*pCtx)->bitstreamposition      = 0;
    (*pCtx)->bitstreamlastposition  = 0;
    (*pCtx)->bitshift               = 0;
    (*pCtx)->tailSize               = 0;
    
    /* Create CompCtxes and make the first Empty to handle errors */
    size    = sizeof(U3DCompCtx) * (NUM_DYNAMIC_COMPCTX + 1);
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
   
    rez = GetStreamData(*pCtx);
    if(rez == 0) {
        return u3dStsStreamOpErr;
    } /* if */
#ifdef U3D_LOGDECODER
    (*pCtx)->logFile    = fopen("u3ddecoder.log", "wt");
#endif
    return u3dStsNoErr;
} /* u3dDecoderInit */

/**
 * u3dDecoderReset @brief U3D Bitstream decoder reinitialize function 
 * 
 * @b Purpose \n
 *      Reset internal state of the U3D decoder instance.
 *  @param pCtx (out) the pointer to the decoder context to be resed
 *  @param pStreamCtx (in) the pointer to the user defined stream context
 *  @param cbMap (in) callback function pointer that will be used to get data
 * @return
 *      Status of decoder initialze procedure
 *      @retval u3dStsNoErr if initialization was successful.
 *      @retval u3dStsBadArgErr if cbMap is 0 pointer
 *      @retval u3dStsNoMemErr if system cannot allocate enough memory.
 * @note
 *      u3dDecoderReset() is a way to reinitialize the U3D decoder
 */

U3D_METHOD(U3dStatus, u3dDecoderReset,(
    U3dDecoder*     pCtx,
    U3dStream_cbCtx *pStreamCtx,
    U3dCb_Map       cbMap))
{
    U64     rez;
    U32     index;

    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DDECODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */
    /* Init All CompCtxes */
    pCtx->high                 = 0x0000FFFF;
    pCtx->low                  = 0x00000000;
    pCtx->underflowCount       = 0;
    /* Reset CompCtxes */
    if(pCtx->compCtx && pCtx->compCtxAllocatedSize) {
        /* Delete histogram from dynamic context */
        for(index = 0; index < pCtx->compCtxAllocatedSize; index++) {
           if(pCtx->compCtx[index].histogram) {
               u3dHistogramDynamicDelete(pCtx->compCtx[index].histogram);
               pCtx->compCtx[index].histogram   = 0;
               pCtx->compCtx[index].inuse       = 0;
           } /* if */
           if(pCtx->compCtx[index].inuse) {
               pCtx->compCtx[index].inuse       = 0;
           } /* if */
        } /* for */
    } /* if */
    /* Reset Stream */
    pCtx->pStreamCtx             = pStreamCtx;
    pCtx->cbMap                  = cbMap;

    pCtx->bitstreamallocated     = 0;
    pCtx->bitstreamallocatedsize = 0;
    pCtx->bitstreamposition      = 0;
    pCtx->bitstreamlastposition  = 0;
    pCtx->bitshift               = 0;
    pCtx->tailSize               = 0;
    rez = GetStreamData(pCtx);
    if(rez == 0) {
        return u3dStsStreamOpErr;
    } /* if */

#ifdef U3D_LOGDECODER
    fprintf(pCtx->logFile, "Context was reset \n");
#endif
    return u3dStsNoErr;
} /* u3dDecoderReset */

/*
 * U3D Bitstream decoder function u3dDecoderDelete
 * Purpose
 *      Delete an instance of the U3D decoder.
 *  Parameters
 *  (in)pCtx - the pointer to the decoder context to be deleted
 *  Return
 *      u3dStsNoErr if the object was successfully deleted.
 *      u3dStsContextMatchErr if pCtx isn't valid
 *      u3dStsNullPtrErr if pCtx is null
 */
U3D_METHOD(U3dStatus, u3dDecoderDelete,(U3dDecoder* pCtx))
{
    U32 index;
    
    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DDECODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */
#ifdef U3D_LOGDECODER
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
} /* u3dDecoderDelete */

INT_METHOD(U64, GetStreamData, (U3dDecoder* pCtx))
{
    U64     rezult = 0;

    if(pCtx->tailSize > 4) {
        if(pCtx->bitstreamallocated == 0) {
            // use tail_array as bitstream to avoid overflow problems
            pCtx->bitstreamposition     = pCtx->bitstreamTail;
            pCtx->bitstreamlastposition = &pCtx->bitstreamTail[8];
            return pCtx->tailSize;
        } /* if */
        pCtx->tailSize  = 0;
    } else {
        // Request as more data as possible to be mapped 
        rezult  = pCtx->cbMap(pCtx->pStreamCtx, &(pCtx->bitstreamallocated),
                              0xFFFFFFFF);
        // check problems with mapped array
        if(pCtx->bitstreamallocated == 0) {
            rezult  = 0;
        } /* if */
        if(rezult == 0) {
            pCtx->bitstreamallocated    = 0;
            if(pCtx->tailSize == 0) {
                pCtx->bitstreamallocatedsize = 0;
                return 0;
            } /* if */
        } /* if */
        pCtx->bitstreamallocatedsize = rezult;
    } /* if */
    
    if(pCtx->bitstreamallocatedsize > 4) {
        if(pCtx->tailSize == 0) {
            pCtx->bitstreamallocatedsize    -= 4;
            // use map_array as bitstream
            pCtx->bitstreamposition         = pCtx->bitstreamallocated;
            pCtx->bitstreamlastposition     = pCtx->bitstreamallocated + 
                                              pCtx->bitstreamallocatedsize;
            // last bits are moved to the beginning of tail array
            pCtx->bitstreamTail[0]  = pCtx->bitstreamlastposition[0];
            pCtx->bitstreamTail[1]  = pCtx->bitstreamlastposition[1];
            pCtx->bitstreamTail[2]  = pCtx->bitstreamlastposition[2];
            pCtx->bitstreamTail[3]  = pCtx->bitstreamlastposition[3];
            pCtx->tailSize          = 4;

            return pCtx->bitstreamallocatedsize;
        } else {
            pCtx->tailSize  = 8;
            // first bits are moved to the end of tail array
            pCtx->bitstreamTail[4] = pCtx->bitstreamallocated[0];
            pCtx->bitstreamTail[5] = pCtx->bitstreamallocated[1];
            pCtx->bitstreamTail[6] = pCtx->bitstreamallocated[2];
            pCtx->bitstreamTail[7] = pCtx->bitstreamallocated[3];
        } /* if */
    } else {
        U32 index;
        // move all mapped date from Map_Array to Tail_Array
        for(index = 0; index < pCtx->bitstreamallocatedsize; 
             index++, pCtx->tailSize++ ) {
            pCtx->bitstreamTail[pCtx->tailSize] = 
                                            pCtx->bitstreamallocated[index];
        } /* for */
        while(pCtx->tailSize < 8) {
            if(pCtx->bitstreamallocated) {
                // request data to fill up Tail_Array
                rezult  = pCtx->cbMap(pCtx->pStreamCtx, 
                                      &(pCtx->bitstreamallocated),
                                      8 - pCtx->tailSize);
            } /* if */
            if(((8 - pCtx->tailSize) > rezult) || 
               pCtx->bitstreamallocated == 0) {
                if(rezult == 0 || pCtx->bitstreamallocated == 0) {
                    // no more data can be mapped from user stream
                    rezult                       = pCtx->tailSize;
                    pCtx->tailSize               = 8;
                    // use tail_array as bitstream
                    pCtx->bitstreamposition      = pCtx->bitstreamTail;
                    pCtx->bitstreamlastposition  = pCtx->bitstreamTail + rezult;
                    pCtx->bitstreamallocated     = 0;
                    pCtx->bitstreamallocatedsize = 0;
                    // Set tail_array values to 0 from tail_size
                    for(index = (U32)rezult; index < 8; index++) {
                        pCtx->bitstreamTail[index]  = 0;
                    } /* for */
                    return rezult;
                } /* if */
            } else {
                rezult  = 8 - pCtx->tailSize;
            } /* */
            // move all mapped date from Map_Array to Tail_Array
            for(index = 0; index < rezult; index++, pCtx->tailSize++ ) {
                pCtx->bitstreamTail[pCtx->tailSize] = 
                                                pCtx->bitstreamallocated[index];
            } /* for */
        } /* while */
        // Tail_Array was totally filled
        pCtx->tailSize  = 0;
    } /* if */
    // use tail_array as bitstream
    pCtx->bitstreamposition     = pCtx->bitstreamTail;
    pCtx->bitstreamlastposition = pCtx->bitstreamTail + 8;

    return 8;
} /* GetStreamData */

