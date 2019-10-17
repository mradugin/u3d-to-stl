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
U3D_METHOD(U3dStatus, u3dAddStaticCompressedU8 ,(    
    U3dEncoder*     pCtx, 
    U16				range,
    U8              value))
{

    U3dStatus status;

    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */

	if(range == 0) {
        return u3dStsBadArgErr;
    } /* if */

    if(pCtx->id != U3DENCODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */
#ifdef U3D_LOGENCODER
	// static context
	fprintf(pCtx->logFile, "%d, %lu, %lu\n", 0, range ^ 0x80000000, value);

#endif
	if(range > 0x3FFF) {
		U3dStatus status = u3dStsNoErr;
		status = intAddU8(pCtx, value);
		return status;
	} /* if */

	status = intAddCompressedU8(pCtx, range,  value);
    return status;
} /* u3dAddStaticCompressedU8 */

INT_METHOD(U3dStatus, intAddCompressedU8 ,(    
    U3dEncoder*     pCtx, 
    U16				range,
    U8              value))
{
    U32     valueToAdd      = (U32)value + 1;
    U32     escape          = 0;
    U32     cumSymbolFreq   = 0;
    U32     symbolFreq      = 1;
    U32     rangeProb       = 0;
	U32     rangeI			= range;
    U32     high;
    U32     low;
    U32     underflowCount;

    high            = pCtx->high;
    low             = pCtx->low;
    underflowCount  = pCtx->underflowCount;

    // Static Compresion Context 
    if(valueToAdd > range) {
        // escape Symbol will be added
        escape          = 1;
        valueToAdd      = 0;
        cumSymbolFreq   = 0;
    } else {
        cumSymbolFreq   = value;
    } /* if */
    symbolFreq      = 1;

    rangeProb	= high + 1 - low;
    high		= low - 1 + rangeProb * (cumSymbolFreq + symbolFreq) / rangeI;
    low			= low + rangeProb * cumSymbolFreq /rangeI;

    // write data to bitstream
    while((high & Hbit) == (low & Hbit)) {
        U32 bit = (low >> 15);

        high    &= ~Hbit;
        high    <<= 1;
        high    |= 1;
        low     &= ~Hbit;
        low     <<= 1;
        ADD_NBITS_TO_STREAM(pCtx, bit, 1);
        while(underflowCount > 0) {
            underflowCount--;
            ADD_NBITS_TO_STREAM(pCtx, ~bit, 1);
        } /* while */
    } /* while */

    // define underflow value
    while((0 == (high & Qbit)) && (Qbit == (low & Qbit))) {
        high    &= ~Hbit;
        high    <<= 1;
        high    |= Hbit;
        high    |= 1;
        low     <<= 1;
        low     &= ~Hbit;
        underflowCount++;
    } /* while */

    // store the current stage
    pCtx->high           = high;
    pCtx->low            = low;
    pCtx->underflowCount = underflowCount;
    if(escape) {
        intAddU8(pCtx, value);
    } /* if */

    return u3dStsNoErr;
} /* intAddCompressedU8 */
