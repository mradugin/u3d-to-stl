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
 *      @file u3dbitdecoder.h  @brief U3D bitdecoder API definition
*/

#ifndef __u3dbitdecoder_h__
#define __u3dbitdecoder_h__

#include "u3ddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * U3dDecoder @brief U3D bit decoder context defenition
 */
typedef struct U3dDecoder U3dDecoder;

/**
 * u3dDecoderInit @brief U3D Bitstream decoder initialize function 
 * 
 * @b Purpose \n
 *      Create an instance of the U3D decoder.
 *  @param pCtx (out) the pointer to the variable which will be initialized with
 *         the pointer to new U3D decoder
 *  @param pMemUtls (in) the pointer to the user defined memory management
 *         service
 *  @param pStreamCtx (in) the pointer to the user defined stream context
 *  @param cbMap (in) callback function pointer that will be used to get data
 * @return
 *      Status of decoder initialze procedure
 *      @retval u3dStsNoErr if initialization was successful.
 *      @retval u3dStsNullPtrErr if pCtx or pMemUtls are null.
 *      @retval u3dStsBadArgErr if pMemUtls doesn't contain valid pointers to
 *              alloc and free function (see OxlMemory). And if cbMap is 
 *              0 pointer
 *      @retval u3dStsNoMemErr if system cannot allocate enough memory.
 * @note
 *      u3dDecoderInit() is the only way to instantiate the U3D decoder, so it 
 *      must be the first function in the calling sequence.
 *      u3dDecoderDelete() must be invoked in order to delete each object 
 *      created by u3dDecoderInit() function.
 */
U3D_API(U3dStatus, u3dDecoderInit,(
    U3dDecoder**    pCtx,
    U3dMemory       *pMemUtls,
    U3dStream_cbCtx *pStreamCtx,
    U3dCb_Map       cbMap))

/**
 * u3dDecoderDelete @brief U3D Bitstream decoder delete function 
 * 
 * @b Purpose \n
 *      Delete an instance of the U3D decoder.
 *  @param pCtx (in) the pointer to the decoder context to be deleted
 * @return
 *      @retval u3dStsNoErr if the object was successfully deleted.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dDecoderDelete,(U3dDecoder* pCtx))

/*----------------------------------------------------------------------------*/
/* Decoder functions                                                          */
/*----------------------------------------------------------------------------*/

/**
 * u3dGetU64 @brief U3D Bitstream decoder function to get value from bitstream
 * 
 * @b Purpose \n 
 *      Get an U64 data from bitstream.
 *  
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to get U64 data
 *  @param value (out) the value that should be gotten from bitstream 
 * @return
 *      Status of get value from bitstream operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dGetU64,(U3dDecoder* pCtx, U64 *value))

/**
 * u3dGetU32 @brief U3D Bitstream decoder function to get value from bitstream
 * 
 * @b Purpose \n 
 *      Get an U32 data from bitstream.
 *  
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to get U32 data
 *  @param value (out) the value that should be gotten from bitstream 
 * @return
 *      Status of get value from bitstream operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dGetU32,(U3dDecoder* pCtx, U32 *value))

/**
 * u3dGetU16 @brief U3D Bitstream decoder function to get value from bitstream
 * 
 * @b Purpose \n 
 *      Get an U16 data from bitstream.
 *  
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to get U16 data
 *  @param value (out) the value that should be gotten from bitstream 
 * @return
 *      Status of get value from bitstream operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dGetU16,(U3dDecoder* pCtx, U16 *value))

/**
 * u3dGetU8 @brief U3D Bitstream decoder function to get value from bitstream
 * 
 * @b Purpose \n 
 *      Get an U8 data from bitstream.
 *  
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to get U8 data
 *  @param value (out) the value that should be gotten from bitstream 
 * @return
 *      Status of get value from bitstream operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dGetU8 ,(U3dDecoder* pCtx, U8  *value))

/**
 * u3dGetArrayU32 @brief U3D Bitstream decoder function to get array of bits
 * from bitstream to U32 array
 * 
 * @b Purpose \n
 *      Get an array of bits to U32 data array from bitstream.
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to get U32 data array
 *  @param values (out) the array of values that should be gotten from bitstream
 *  @param count (in) number of values in array
 *  @param stride (in) shift in array between values in elements
 *  @param actualBits (in) the size in bits of each values in values array
 * @return
 *      @retval u3dStsNoErr if the values were successfully gotten to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx or  values is null
 *      @retval u3dStsBadArgErr if count, stride or actualBits is 0 or 
 *              actualBits > 32
 */
U3D_API(U3dStatus, u3dGetArrayU32,(
    U3dDecoder*     pCtx, 
    U32*            values, 
    U32             count,
    U32             stride,
    U8              actualBits))

/*----------------------------------------------------------------------------*/
/* Decoder functions for Compressed context                                   */
/*----------------------------------------------------------------------------*/

/**
 * u3dDecoderCreateCompCtx @brief U3D Bitstream decoder function to create 
 * compressed context
 * 
 * @b Purpose \n
 *      create a dynaimic compressed context to read compressed value from 
 *		bitstream by using u3dGetDynamicCompressedU16() and 
 *		u3dGetDynamicCompressedU8() functions
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
U3D_API(U3dStatus, u3dDecoderCreateCompCtx,(    
    U3dDecoder*     pCtx, 
    U3DCompCtxID*   compCtxID
    ))

/**
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
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *      @retval u3dStsBadArgErr if @e compCtxID wasn't associated with @e pCtx 
 */
U3D_API(U3dStatus, u3dDecoderReleaseCompCtx,(    
    U3dDecoder*     pCtx, 
    U3DCompCtxID    compCtxID
    ))

/**
 * u3dGetStaticCompressedU32 @brief U3D Bitstream decoder function to get U32
 * compressed value from bitstream by using static context
 * 
 * @b Purpose \n
 *      Get an U32 data from bitstream by using static compresed context 
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to get U32 data using static compressed context
 *  @param range (in) the range of static compressed context 
 *  @param value (out) the value that will be gotten from bitstream 
 * @return
 *      Status of geting compressed value from bitstream operation
 *      @retval u3dStsNoErr if the value was successfully gotten from bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *      @retval u3dStsBadArgErr if range is equal to 0
*/
U3D_API(U3dStatus, u3dGetStaticCompressedU32,(    
    U3dDecoder*     pCtx, 
    U32			    range,
    U32             *value))

/**
 * u3dGetStaticCompressedU16 @brief U3D Bitstream decoder function to get U16
 * compressed value from bitstream by using static context
 * 
 * @b Purpose \n
 *      Get an U16 data from bitstream by using static compresed context 
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to get U16 data using static compressed context
 *  @param range (in) the range of static compressed context 
 *  @param value (out) the value that will be gotten from bitstream 
 * @return
 *      Status of geting compressed value from bitstream operation
 *      @retval u3dStsNoErr if the value was successfully gotten from bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *      @retval u3dStsBadArgErr if range is equal to 0
 */
U3D_API(U3dStatus, u3dGetStaticCompressedU16,(    
    U3dDecoder*     pCtx, 
    U16			    range,
    U16             *value))

/**
 * u3dGetCompressedU8 @brief U3D Bitstream decoder function to get U8 
 * compressed value from bitstream by using static compresed context
 * 
 * @b Purpose \n
 *      Get an U8 data from bitstream by using static compresed context 
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to get U8 data using static compressed context
 *  @param range (in) the range of static compressed context 
 *  @param value (out) the value that will be gotten from bitstream 
 * @return
 *      Status of geting compressed value from bitstream operation
 *      @retval u3dStsNoErr if the value was successfully gotten from bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *      @retval u3dStsBadArgErr if range is equal to 0
 */
U3D_API(U3dStatus, u3dGetStaticCompressedU8 ,(    
    U3dDecoder*     pCtx, 
    U16			    range,
    U8              *value))

/**
 * u3dGetDynamicCompressedU32 @brief U3D Bitstream decoder function to get U32
 * compressed value from bitstream by using dynamic compresed context
 * 
 * @b Purpose \n
 *      Get an U32 data from bitstream by using dynamic compresed context 
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to get U32 data using dynamic compressed context
 *  @param compCtxID (in) the ID of dynamic compressed context 
 *  @param value (out) the value that will be gotten from bitstream 
 * @return
 *      Status of geting compressed value from bitstream operation
 *      @retval u3dStsNoErr if the value was successfully gotten from bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *		@retval u3dStsNotSupportedErr if compressed context isn't available for
 *              defined encoder context 
 *      @retval u3dStsBadArgErr if specified compCtxId doesn't associated with 
 *              defined decoder context 
 */
U3D_API(U3dStatus, u3dGetDynamicCompressedU32,(
    U3dDecoder*     pCtx, 
    U3DCompCtxID    compCtxID,
    U32             *value))

/**
 * u3dGetDynamicCompressedU16 @brief U3D Bitstream decoder function to get U16
 * compressed value from bitstream by using dynamic compresed context
 * 
 * @b Purpose \n
 *      Get an U16 data from bitstream by using dynamic compresed context 
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to get U16 data using dynamic compressed context
 *  @param compCtxID (in) the ID of dynamic compressed context 
 *  @param value (out) the value that will be gotten from bitstream 
 * @return
 *      Status of geting compressed value from bitstream operation
 *      @retval u3dStsNoErr if the value was successfully gotten from bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *		@retval u3dStsNotSupportedErr if compressed context isn't available for
 *              defined encoder context 
 *      @retval u3dStsBadArgErr if specified compCtxId doesn't associated with 
 *              defined decoder context 
 */
U3D_API(U3dStatus, u3dGetDynamicCompressedU16,(
    U3dDecoder*     pCtx, 
    U3DCompCtxID    compCtxID,
    U16             *value))

/**
 * u3dGetDynamicCompressedU8 @brief U3D Bitstream decoder function to get U8
 * compressed value from bitstream by using dynamic compresed context
 * 
 * @b Purpose \n
 *      Get an U8 data from bitstream by using dynamic compresed context 
 *  @param pCtx (in) the pointer to the decoder context of bitstream that will 
 *         be used to get U16 data using dynamic compressed context
 *  @param compCtxID (in) the ID of dynamic compressed context 
 *  @param value (out) the value that will be gotten from bitstream 
 * @return
 *      Status of geting compressed value from bitstream operation
 *      @retval u3dStsNoErr if the value was successfully gotten from bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *		@retval u3dStsNotSupportedErr if compressed context isn't available for
 *              defined encoder context 
 *      @retval u3dStsBadArgErr if specified compCtxId doesn't associated with 
 *              defined decoder context 
 */
U3D_API(U3dStatus, u3dGetDynamicCompressedU8,(
    U3dDecoder*     pCtx, 
    U3DCompCtxID    compCtxID,
    U8              *value))

#ifdef __cplusplus
}
#endif

#endif /*__u3dbitdecoder_h__*/
/*End of file u3dbitdecoder.h*/
