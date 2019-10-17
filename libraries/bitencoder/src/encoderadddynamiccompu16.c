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
U3D_METHOD(U3dStatus, u3dAddDynamicCompressedU16,(    
    U3dEncoder*     pCtx, 
    U3DCompCtxID    compCtxID,
    U16             value))
{
    U32			valueToAdd      = (U32)value + 1;
    U32			escape          = 0;
    U32			totalSymbolFreq = 1;
    U32			cumSymbolFreq   = 0;
    U32			symbolFreq      = 1;
    U32			range           = 0;
    U32			high;
    U32			low;
    U32			underflowCount;
    U3dStatus	rez;

    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DENCODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */
    if(pCtx->compCtx == 0) {
        return u3dStsNotSupportedErr;
    } /* if */
    if(compCtxID > pCtx->compCtxLast || compCtxID == 0) {
        return u3dStsBadArgErr;
    } /* if */
    if(pCtx->compCtx[compCtxID].inuse == 0) {
        return u3dStsBadArgErr;
    } /* if */
#ifdef U3D_LOGENCODER
	// dynamic context
	// type, context, value
	fprintf(pCtx->logFile, "%d, %lu, %lu\n", 1, range, value);
#endif
    high            = pCtx->high;
    low             = pCtx->low;
    underflowCount  = pCtx->underflowCount;

    // Dynamic Compresion Context
    rez = u3dGetSymbolFreq(pCtx->compCtx[compCtxID].histogram, valueToAdd,
                            &symbolFreq);
    if(rez != u3dStsNoErr && rez != u3dStsDataOverflowErr) {
        return rez;
    } /* if */

    if(symbolFreq == 0) {
        // escape Symbol will be added
        escape      = 1;
        valueToAdd  = 0;
		cumSymbolFreq	 = 0;
        rez = u3dGetSymbolFreq(pCtx->compCtx[compCtxID].histogram, 
                                valueToAdd, &symbolFreq);
        if(rez) {
            return rez;
        } /* if */
    } else {
        rez = u3dGetCumSymbolFreq(pCtx->compCtx[compCtxID].histogram, 
                                    valueToAdd, &cumSymbolFreq);
        if(rez) {
            return rez;
        } /* if */
    } /* if */

    rez = u3dGetTotalSymbolFreq(pCtx->compCtx[compCtxID].histogram, 
                                &totalSymbolFreq);
    if(rez) {
        return rez;
    } /* if */
    rez = u3dHistogramDynamicAddSymbol(pCtx->compCtx[compCtxID].histogram, 
                                        valueToAdd);
    if(rez != u3dStsNoErr && rez != u3dStsDataOverflowErr) {
        return rez;
    } /* if */
    if(escape) {
        U32 valueT = value + 1;
        rez=u3dHistogramDynamicAddSymbol(pCtx->compCtx[compCtxID].histogram, 
                                            valueT);
		if(rez != u3dStsNoErr && rez != u3dStsDataOverflowErr) {
			return rez;
		} /* if */
    } /* if */
    if(totalSymbolFreq == 0) {
        return u3dStsErr;
    } /* if */

    range   = high + 1 - low;
    high    = low - 1 + range * (cumSymbolFreq + symbolFreq) / totalSymbolFreq;
    low     = low + range * cumSymbolFreq / totalSymbolFreq;

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
        intAddU16(pCtx, value);
    } /* if */

    return u3dStsNoErr;
} /* u3dAddDynamicCompressedU16 */

