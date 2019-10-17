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
 *        @file u3dbitencoder.h @brief U3D bitencoder API definition
*/

#ifndef __u3dbitencoder_h__
#define __u3dbitencoder_h__

#include "u3ddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * U3dEncoder @brief U3D bit encoder context defenition
 */
typedef struct U3dEncoder U3dEncoder;

/**
 * u3dEncoderInit @brief U3D Bitstream encoder initialize function 
 * 
 * @b Purpose \n
 *      Create an instance of the U3D encoder.
 *  @param pCtx (out) the pointer to the variable which will be initialized with 
 *         the pointer to new U3D encoder
 *  @param pMemUtls (in) the pointer to the user defined memory management 
 *         service
 *  @param pStreamCtx (in) the pointer to the user defined stream context
 *  @param cbWrite (in) callback function pointer that will be used to serialize
 *         data
 *  @param limitSize (in) the maximum size of buffer that can be written at one 
 *         call of cbWrite function
 * @return
 *      Status of encoder initialze procedure
 *      @retval u3dStsNoErr if initialization was successful.
 *      @retval u3dStsNullPtrErr if pCtx or pMemUtls are null.
 *      @retval u3dStsBadArgErr if pMemUtls doesn't contain valid pointers to 
 *              alloc and free function (see OxlMemory). And if cbWrite is 0 
 *              pointer also if limitSize < 10
 *      @retval u3dStsNoMemErr if system cannot allocate enough memory.
 * @note
 *      u3dEncoderInit() is the only way to instantiate the U3D encoder, so it 
 *      must be the first function in the calling sequence.
 *      u3dEncoderDelete() must be invoked in order to delete each object created
 *      by u3dEncoderInit function.
 */
U3D_API(U3dStatus, u3dEncoderInit,(
    U3dEncoder**    pCtx,
    U3dMemory       *pMemUtls,
    U3dStream_cbCtx *pStreamCtx,
    U3dCb_Write     cbWrite,
    U64             limitSize))

/**
 * u3dEncoderFlush @brief U3D Bitstream encoder flush function 
 * 
 * @b Purpose \n
 *      Force to flush the bitstream to user defined writer callbacks
 *  @param pCtx (in) the pointer to the encoder context of bitstream that should 
 *         be flushed
 * @return
 *      Status of encoder flush operation
 *      @retval u3dStsNoErr if the bitstream was successfully flushed.
 *      @retval u3dStsNullPtrErr if pCtx is null.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsStreamOpErr if error in the stream's callback when 
 *              cbWriten returned 0 or value that exiceed size of byte to write
 * @note
 *      u3dEncoderFlush() reset the bitstream encoder context to initial state 
 *      by filling necessary zero pading data to the end stream and writing it
 *      to user defined stream through corresponding writing callback function
*/
U3D_API(U3dStatus, u3dEncoderFlush,(U3dEncoder* pCtx))

/**
 * u3dEncoderDelete @brief U3D Bitstream encoder delete function
 * 
 * @b Purpose \n
 *      Delete an instance of the U3D encoder.
 *  @param pCtx (in) the pointer to the encoder context to be deleted
 * @return
 *      Status of encoder delete procedure
 *      @retval u3dStsNoErr if the object was successfully deleted.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dEncoderDelete,(U3dEncoder* pCtx))

/*----------------------------------------------------------------------------*/
/* Encoder functions                                                          */
/*----------------------------------------------------------------------------*/

/**
 * u3dAddU64 @brief U3D Bitstream encoder function to add value 
 * to bitstream
 * 
 * @b Purpose \n
 *      Added an U64 data to bitstream.
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be updated by new U64 data
 *  @param value (in) the value that should be added to bitstream 
 * @return
 *      Status of add operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dAddU64,(U3dEncoder* pCtx, U64 value))

/**
 * u3dAddU32 @brief U3D Bitstream encoder function to add value 
 * to bitstream
 * 
 * @b Purpose \n
 *      Added an U32 data to bitstream.
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be updated by new U32 data
 *  @param value (in) the value that should be added to bitstream 
 * @return
 *      Status of add operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dAddU32,(U3dEncoder* pCtx, U32 value))

/**
 * u3dAddU16 @brief U3D Bitstream encoder function to add value 
 * to bitstream
 * 
 * @b Purpose \n
 *      Added an U16 data to bitstream.
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be updated by new U16 data
 *  @param value (in) the value that should be added to bitstream 
 * @return
 *      Status of add operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dAddU16,(U3dEncoder* pCtx, U16 value))

/**
 * u3dAddU8 @brief U3D Bitstream encoder function to add value 
 * to bitstream
 * 
 * @b Purpose \n
 *      Added an U8 data to bitstream.
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be updated by new U8 data
 *  @param value (in) the value that should be added to bitstream 
 * @return
 *      Status of add operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dAddU8 ,(U3dEncoder* pCtx, U8  value))

/**
 * u3dAddString @brief U3D Bitstream encoder function to add value 
 * to bitstream
 * 
 * @b Purpose \n
 *      Added an String data to bitstream.
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be updated by new String data
 *  @param value (in) the value that should be added to bitstream 
 * @return
 *      Status of add operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dAddString ,(U3dEncoder* pCtx, U3dString  value))

/**
 * u3dAddArrayU32 @brief U3D Bitstream encoder function to add array of bits
 * to bitstream from U32 arrays 
 * 
 * @b Purpose \n
 *      Added an array of U32 data to bitstream.
 *  
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will be 
 *             updated by new U32 data array
 *  @param values (in) the array of values that should be added to bitstream
 *  @param count (in) number of values in array
 *  @param stride (in) shift in array between values in elements
 *  @param actualBits (in) the size in bits of each value in @e values array
 * @return
 *      Status of add array operation
 *      @retval u3dStsNoErr if the values were successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx or  values is null
 *      @retval u3dStsBadArgErr if count, stride or actualBits is 0 or 
 *              actualBits > 32
 */
U3D_API(U3dStatus, u3dAddArrayU32,(
    U3dEncoder*     pCtx, 
    U32*            values, 
    U32             count,
    U32             stride,
    U8              actualBits))

/*----------------------------------------------------------------------------*/
/* Encoder functions for Compressed context                                   */
/*----------------------------------------------------------------------------*/

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
U3D_API(U3dStatus, u3dEncoderCreateCompCtx,(    
    U3dEncoder*     pCtx, 
    U3DCompCtxID*   compCtxID
    ))

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
U3D_API(U3dStatus, u3dEncoderReleaseCompCtx,(    
    U3dEncoder*     pCtx, 
    U3DCompCtxID    compCtxID
    ))

/**
 * u3dAddStaticCompressedU32 @brief U3D Bitstream encoder function to add U32 
 * compressed value to bitstream by using static compressed context 
 * 
 * @b Purpose \n
 *      Add an U32 data to bitstream by using static compressed context 
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be used to add U32 data using compressed context
 *  @param range (in) the range of static compressed context 
 *  @param value (in) the value that will be added to bitstream 
 * @return
 *      Status of adding compressed value to bitstream operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *      @retval u3dStsBadArgErr if range is equal to 0
 */
U3D_API(U3dStatus, u3dAddStaticCompressedU32,(    
    U3dEncoder*     pCtx, 
    U32			    range,
    U32             value))

 /**
 * u3dAddStaticCompressedU16 @brief U3D Bitstream encoder function to add U16 
 * compressed value to bitstream by using static compressed context 
 * 
 * @b Purpose \n
 *      Add an U16 data to bitstream by using static compressed context 
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be used to add U16 data using compressed context
 *  @param range (in) the range of static compressed context 
 *  @param value (in) the value that will be added to bitstream 
 * @return
 *      Status of adding compressed value to bitstream operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsBadArgErr if range is equal to 0
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dAddStaticCompressedU16,(    
    U3dEncoder*     pCtx, 
    U16			    range,
    U16             value))

/**
 * u3dAddStaticCompressedU8 @brief U3D Bitstream encoder function to add U8
 * compressed value to bitstream by using static compressed context
 * 
 * @b Purpose \n
 *      Add an U8 data to bitstream by using static compressed context 
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be used to add U8 data using compressed context
 *  @param range (in) the range of static compressed context 
 *  @param value (in) the value that will be added to bitstream 
 * @return
 *      Status of adding compressed value to bitstream operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsBadArgErr if range is equal to 0
 *      @retval u3dStsNullPtrErr if pCtx is null
 */
U3D_API(U3dStatus, u3dAddStaticCompressedU8 ,(    
    U3dEncoder*     pCtx, 
    U16				range,
    U8              value))

/**
 * u3dAddDynamicCompressedU32 @brief U3D Bitstream encoder function to add U32
 * compressed value to bitstream by using dynamic context
 * 
 * @b Purpose \n
 *      Add an U32 data to bitstream by using dynamic compresed context 
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be used to add U32 data using compressed context
 *  @param compCtxID (in) the ID of dynamic compressed context 
 *  @param value (in) the value that will be added to bitstream 
 * @return
 *      Status of adding compressed value to bitstream operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *		@retval u3dStsNotSupportedErr if compressed context isn't available for
 *              defined encoder context 
 *      @retval u3dStsBadArgErr if specified compCtxId doesn't associated with 
 *              defined encoder context 
 */
U3D_API(U3dStatus, u3dAddDynamicCompressedU32,(    
    U3dEncoder*     pCtx, 
    U3DCompCtxID    compCtxID,
    U32             value))

/**
 * u3dAddDynamicCompressedU16 @brief U3D Bitstream encoder function to add U16
 * compressed value to bitstream by using dynamic context
 * 
 * @b Purpose \n
 *      Add an U16 data to bitstream by using dynamic compresed context 
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be used to add U16 data using compressed context
 *  @param compCtxID (in) the ID of dynamic compressed context 
 *  @param value (in) the value that will be added to bitstream 
 * @return
 *      Status of adding compressed value to bitstream operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *		@retval u3dStsNotSupportedErr if compressed context isn't available for
 *              defined encoder context 
 *      @retval u3dStsBadArgErr if specified compCtxId doesn't associated with 
 *              defined encoder context 
 */
U3D_API(U3dStatus, u3dAddDynamicCompressedU16,(    
    U3dEncoder*     pCtx, 
    U3DCompCtxID    compCtxID,
    U16             value))

/**
 * u3dAddDynamicCompressedU8 @brief U3D Bitstream encoder function to add U8
 * compressed value to bitstream by using dynamic context
 * 
 * @b Purpose \n
 *      Add an U8 data to bitstream by using dynamic compresed context 
 *  @param pCtx (in) the pointer to the encoder context of bitstream that will 
 *         be used to add U8 data using compressed context
 *  @param compCtxID (in) the ID of dynamic compressed context 
 *  @param value (in) the value that will be added to bitstream 
 * @return
 *      Status of adding compressed value to bitstream operation
 *      @retval u3dStsNoErr if the value was successfully added to bitstream.
 *      @retval u3dStsContextMatchErr if pCtx isn't valid
 *      @retval u3dStsNullPtrErr if pCtx is null
 *		@retval u3dStsNotSupportedErr if compressed context isn't available for
 *              defined encoder context 
 *      @retval u3dStsBadArgErr if specified compCtxId doesn't associated with 
 *              defined encoder context 
 */
U3D_API(U3dStatus, u3dAddDynamicCompressedU8,( 
    U3dEncoder*     pCtx, 
    U3DCompCtxID    compCtxID,
    U8	            value))

#ifdef __cplusplus
}
#endif

#endif /*__u3dbitencoder_h__*/
/*End of file u3dbitencoder.h*/
