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

/**
 *     @file u3dhistogram.h @brief U3D dynamic histogram API definition
*/

#ifndef __u3dhistogram_h__
#define __u3dhistogram_h__

#include "u3ddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * U3dHistogramDynamic @brief dynamic histogram context defenition
 */
typedef struct U3dHistogramDynamic U3dHistogramDynamic;

/**
 * U3DDynamicHistogramType @brief dynamic histogram type enumeration
 */
typedef enum {
    u3dDynamicHistogramU8   = 1, /**< U8 values histogram                     */
    u3dDynamicHistogramU16  = 2  /**< U16 values histogram                    */
}U3DDynamicHistogramType;

/**
 * u3dHistogramDynamicInit @brief U3D Histogram initialize function 
 * 
 * @b Purpose \n
 *      Create an instance of the U3D Dynamic Histogram.
 *  
 *  @param pCtx (out) the pointer to the variable which will be initialized 
 *              with the pointer to new U3D Dynamic Histogram
 *  @param pMemUtls (in) the pointer to the user defined memory management 
 *              service
 *  @param type (in) type defines the maxim value that can be added into 
 *              histogram for u3dDynamicHistogramU8 the maximum is 
 *              0xFF = 2^8 - 1 for u3dDynamicHistogramU16 the maximu is 
 *              0xFFFF = 2^16 - 1
 * @param totalNumberLimit (in)
 * @return
 *      Status of histogram initialization procedure
 *      @retval u3dStsNoErr if initialization was successful.
 *      @retval u3dStsNullPtrErr if pCtx or pMemUtls are null.
 *      @retval u3dStsBadArgErr if pMemUtls doesn't contain valid pointers to 
 *              alloc and free function. See U3dMemory.
 *      @retval u3dStsNoMemErr if system cannot allocate enough memory.
 *  @note
 *      u3dHistogramDynamicInit() is the only way to instantiate the U3D Dynamic
 *      Histogram, so it must be the first function in the calling sequence.
 *      u3dHistogramDynamicDelete() must be invoked in order to delete each 
 *      object created by u3dHistogramDynamicInit() function.
 */
U3D_API(U3dStatus, u3dHistogramDynamicInit,(
    U3dHistogramDynamic**   pCtx,
    U3dMemory               *pMemUtls,
    U3DDynamicHistogramType type,
    U32                     totalNumberLimit))

/**
 * u3dHistogramDynamicReset @brief U3D Histogram reset function 
 * 
 * @b Purpose \n
 *      Reset of the U3D Dynamic Histogram internal data.
 *  @param pCtx (in)the pointer to the Dynamic Histogram context to be reseted
 * @return
 *      Status of histogram reset procedure
 *      @retval u3dStsNoErr if the internal data of the U3D Dynamic Histogram 
 *              was successfuly reset.
 *      @retval u3dStsNullPtrErr if pCtx is null.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
*/
U3D_API(U3dStatus, u3dHistogramDynamicReset,(U3dHistogramDynamic* pCtx))

/**
 * u3dHistogramDynamicDelete @brief U3D Histogram delete function
 * 
 * @b Purpose \n
 *      Delete an instance of the U3D Dynamic Histogram.
 *  @param pCtx (in) the pointer to the Dynamic Histogram context to be deleted
 *  @return
 *      @retval u3dStsNoErr if the object was successfully deleted.
 *      @retval u3dStsNullPtrErr if pCtx is null.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
*/
U3D_API(U3dStatus, u3dHistogramDynamicDelete,(U3dHistogramDynamic* pCtx))

/*----------------------------------------------------------------------------*/

/* 
 * Histogram functions                                                          
 */

/**
 * u3dHistogramDynamicAddSymbol @brief U3D Histogram function to add symbol
 * 
 * @b Purpose \n
 *      Add new value in specified dynamic histogram and update requried filed 
 *      in histogram like: u3dGetSymbolFreq(), u3dGetCumSymbolFreq(), 
 *      u3dGetTotalSymbolFreq(). 
 *      Functions automatically allocate neccessary memory if the context 
 *      wasn't allocated before. 
 *  @param pHistogram (in) the pointer to the dynamic histogram context
 *  @param symbol (in) value to be added to histogram 
 * @return
 *      Status of add symbol operation
 *      @retval u3dStsNoErr if symbol was successful added to histogram.
 *      @retval u3dStsNullPtrErr if pHistogram is null.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsBadArgErr if value exceed the maxim value size that was 
 *              specified by "type" in u3dHistogramDynamicInit() function
 *      @retval u3dStsDataOverflowErr if 
 */
U3D_API(U3dStatus, u3dHistogramDynamicAddSymbol,(
        U3dHistogramDynamic* pHistogram,
        U32 symbol))

/*
 * Symbol / Frequency conversion methods
 */

/**
 * u3dGetSymbolFreq @brief U3D Histogram function to get symbol frequency 
 *
 * @b Purpose \n
 *      Returns the approximate occurence count of this symbol
 *  @param pHistogram (in) the pointer to the dynamic histogram context
 *  @param symbol (in) the symbol for what occurence count will be defined 
 *  @param freq (out) the approximate occurence count of this symbol
 * @return
 *      Status of get symbol frequency operation
 *      @retval u3dStsNoErr if approximate occurence count of this symbol was 
 *              defined
 *      @retval u3dStsNullPtrErr if pHistogram is null.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsBadArgErr if value exceed the maxim value size that was 
 *              specified by "type" in u3dHistogramDynamicInit function
 */
U3D_API(U3dStatus, u3dGetSymbolFreq, (
            U3dHistogramDynamic* pHistogram,
            U32 symbol, U32 *freq))

/**
 * u3dGetCumSymbolFreq @brief U3D Histogram function to get cumulative symbol 
 * frequency 
 * 
 * @b Purpose \n
 *      Returns the approximate sum of all symbol freqs for symbols less than 
 *      the given symbol
 *  @param pHistogram (in) the pointer to the dynamic histogram context
 *  @param symbol (in) the symbol for what cumulative freq will be defined 
 *  @param cumFreq (out) the approximate cumulative freq for symbols less than 
 *      the given symbol
 * @return
 *      Status of get cumulative symbol frequency operation
 *      @retval u3dStsNoErr if approximate occurence count of this symbol was 
 *              defined
 *      @retval u3dStsNullPtrErr if pHistogram is null.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsBadArgErr if value exceed the maxim value size that was 
 *              specified by "type" in u3dHistogramDynamicInit() function
 */
U3D_API(U3dStatus, u3dGetCumSymbolFreq, (
            U3dHistogramDynamic* pHistogram,
            U32 symbol, U32 *cumFreq))

/**
 * u3dGetTotalSymbolFreq @brief U3D Histogram function to get total symbol 
 * frequency
 * 
 * @b Purpose \n
 *      Returns the approximate occurence count of all symbols
 *  @param pHistogram (in) the pointer to the dynamic histogram context
 *  @param total (out) the approximate occurence count of all symbols
 * @return
 *      Status of get total symbol frequency operation
 *      @retval u3dStsNoErr if approximate occurence count of this symbol was 
 *              defined
 *      @retval u3dStsNullPtrErr if pHistogram is null.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 */
U3D_API(U3dStatus, u3dGetTotalSymbolFreq, (
            U3dHistogramDynamic* pHistogram,
            U32 *total))

/**
 * u3dGetSymbolFromFreq @brief U3D Histogram function to get symbol from 
 * frequency
 * 
 * @b Purpose \n
 *      Return the symbol that corresponds to the given cumulative frequency
 *  @param pHistogram (in)the pointer to the dynamic histogram context
 *  @param freq (in) cumulative frequency
 *  @param symbol (out) the symbol that corresponds to the given cumulative 
 *         frequency
 * @return
 *      Status of get symbol from frequency operation
 *      @retval u3dStsNoErr if athe symbol that corresponds to the given 
 *              cumulative frequenc was defined
 *      @retval u3dStsNullPtrErr if pHistogram is null.
 *      @retval u3dStsBadArgErr if freq exceed the total number of symbols that
 *              were added to histogram
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 */
U3D_API(U3dStatus, u3dGetSymbolFromFreq, (
            U3dHistogramDynamic* pHistogram,
            U32 freq, U32 *symbol))

/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /*__u3dhistogram_h__*/
/* End of file u3dhistogram.h */
