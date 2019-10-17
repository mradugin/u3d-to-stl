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

#include "histogramdynamic.h"
const U32 cTableLevel[][4] = {
							  { 0, 0, 0, 0}, // shift = 0
							  { 0, 0, 0, 0}, // shift = 1
							  { 0, 0, 0, 0}, // shift = 2
							  { 0, 0, 0, 0}, // shift = 3
							  { 0x1000, 0x2000, 0x3000, 0x4000}, // shift = 4
							  { 0, 0, 0, 0}, // shift = 5
							  { 0x400, 0x800, 0xC00, 0x1000}, // shift = 6
							  { 0, 0, 0, 0}, // shift = 7
							  { 0x100, 0x200, 0x300, 0x400}, // shift = 8
							  { 0, 0, 0, 0}, // shift = 9
							  { 0x40, 0x80, 0xC0, 0x100}, // shift = 10
							  { 0, 0, 0, 0}, // shift = 11
							  { 0x10, 0x20, 0x30, 0x40}, // shift = 12
							  { 0, 0, 0, 0}, // shift = 13
							  { 0x4, 0x8, 0xC, 0x10}  // shift = 14
							 };

/*
 * U3D Histogram function u3dHistogramDynamicInit
 * Purpose
 *      Create an instance of the U3D Dynamic Histogram.
 *  Parameters
 *  (out)pCtx - the pointer to the variable which will be initialized with the
 *              pointer to new U3D Dynamic Histogram
 *  (in)pMemUtls - the pointer to the user defined memory management service
 *  (in)type - type defines the maxim value that can be added into histogram
 *             for u3dDynamicHistogramU8 the maximu is 0xFF = 2^8 - 1
 *             for u3dDynamicHistogramU16 the maximu is 0xFFFF = 2^16 - 1
 *  (in)totalNumberLimit - 
 *
 *  Return
 *      u3dStsNoErr if initialization was successful.
 *      u3dStsNullPtrErr if pCtx or pMemUtls are null.
 *      u3dStsBadArgErr if pMemUtls doesn't contain valid pointers to alloc and
 *                      free function. See U3dMemory.
 *      u3dStsNoMemErr if system cannot allocate enough memory.
 *  Notes
 *      u3dHistogramDynamicInit is the only way to instantiate the U3D Dynamic
 *      Histogram, so it must be the first function in the calling sequence.
 *      u3dHistogramDynamicDelete must be invoked in order to delete each 
 *      object created by u3dHistogramDynamicInit function.
 */
U3D_METHOD(U3dStatus, u3dHistogramDynamicInit,(
    U3dHistogramDynamic**   pCtx,
    U3dMemory               *pMemUtls,
    U3DDynamicHistogramType type,
    U32                     totalNumberLimit))
{
    U32     size = sizeof(U3dHistogramDynamic);
    U32     maxValue = 0xFFFF;
    U32     shiftValue = 0x5555;
    
    if(pCtx == 0 || pMemUtls == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pMemUtls->alloc == 0 || pMemUtls->free == 0) {
        return u3dStsBadArgErr;
    } /* if */

    if(type == u3dDynamicHistogramU8) {
        maxValue    = 0xFF;
        shiftValue  = 0x55;
    } /* if */
    
    size        += ((maxValue + 2) * 2 + shiftValue) * sizeof(U32);
    *pCtx       = (U3dHistogramDynamic*)pMemUtls->alloc(pMemUtls->pCtx, size);
    if(*pCtx == 0) {
        return u3dStsNoMemErr;
    }
    (*pCtx)->id                     = U3DHIST_ID;

    (*pCtx)->memUtls.pCtx           = pMemUtls->pCtx;
    (*pCtx)->memUtls.alloc          = pMemUtls->alloc;
    (*pCtx)->memUtls.realloc        = pMemUtls->realloc;
    (*pCtx)->memUtls.free           = pMemUtls->free;

    (*pCtx)->maxValue               = maxValue;
    (*pCtx)->pSymbolFreq            = (U32*)((U8*)(*pCtx) + 
                                             sizeof(U3dHistogramDynamic));
    (*pCtx)->pCumSymbolFreq         = (*pCtx)->pSymbolFreq + (maxValue + 1);
    (*pCtx)->pCumSymbolFreqShift    = (*pCtx)->pCumSymbolFreq + (maxValue + 1);
    (*pCtx)->maxAddedValue          = 0;
    (*pCtx)->totalSymbols           = 0;
    if(totalNumberLimit) {
        (*pCtx)->totalNumberLimit   = totalNumberLimit;
    } else {
        (*pCtx)->totalNumberLimit   = 0xFFFFFFFF;
    } /* if */
    if(type == u3dDynamicHistogramU8) {
        (*pCtx)->maxLevel           = 3;
        (*pCtx)->mask               = 0xFF;
        (*pCtx)->shift              = 6;
        (*pCtx)->invertShift        = 8;
    } else {
        (*pCtx)->maxLevel           = 7;
        (*pCtx)->mask               = 0xFFFF;
        (*pCtx)->shift              = 14;
        (*pCtx)->invertShift        = 16;
    } /* if */
    u3dHistogramDynamicReset(*pCtx);
    return u3dStsNoErr;
} /* u3dHistogramDynamicInit */

/*
 * U3D Histogram function u3dHistogramDynamicReset
 * Purpose
 *      Reset of the U3D Dynamic Histogram internal data.
 *  Parameters
 *  (in)pCtx - the pointer to the Dynamic Histogram context to be deleted
 *  Return
 *      u3dStsNoErr if the internal data of the U3D Dynamic Histogram 
 *      was successfuly reset.
 *      u3dStsNullPtrErr if pCtx is null.
 *      u3dStsContextMatchErr if pCtx isn't valid
*/
U3D_METHOD(U3dStatus, u3dHistogramDynamicReset,(U3dHistogramDynamic* pCtx))
{
    U32     index;
    U32     shift = 0x5555;

    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DHIST_ID) {
        return u3dStsContextMatchErr;
    } /* if */

    shift = (pCtx->maxValue == 0xFF) ? 0x55 : 0x5555;
    for(index = 0; index < shift; index++) {
        pCtx->pSymbolFreq[index]            = 0;
        pCtx->pCumSymbolFreq[index]         = 0;
        pCtx->pCumSymbolFreqShift[index]    = 0;
    } /* for */
    for(; index <= pCtx->maxValue; index++) {
        pCtx->pSymbolFreq[index]            = 0;
        pCtx->pCumSymbolFreq[index]         = 0;
    } /* for */
    
    return u3dStsNoErr;
} /* u3dHistogramDynamicReset */

/*
 * U3D Histogram function u3dHistogramDynamicDelete
 * Purpose
 *      Delete an instance of the U3D Dynamic Histogram.
 *  Parameters
 *  (in)pCtx - the pointer to the Dynamic Histogram context to be deleted
 *  Return
 *      u3dStsNoErr if the object was successfully deleted.
 *      u3dStsNullPtrErr if pCtx is null.
 *      u3dStsContextMatchErr if pCtx isn't valid
*/
U3D_METHOD(U3dStatus, u3dHistogramDynamicDelete,(U3dHistogramDynamic* pCtx))
{
    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DHIST_ID) {
        return u3dStsContextMatchErr;
    } /* if */

    pCtx->id    = 0xFFFF;
    pCtx->memUtls.free(pCtx->memUtls.pCtx, pCtx);

    return u3dStsNoErr;
} /* u3dHistogramDynamicDelete */

/* End of file histogramdynamic.c */
