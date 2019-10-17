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

extern U32	cReadCount[];
extern U32	cFastNotMask[];
extern U32	cHalfMask;
extern U32	cNotHalfMask;
extern U32	cQuarterMask;
extern U32	cNotThreeQuarterMask;
extern U8   cSwap8Dec[];

extern const U32 c32De[];

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
U3D_METHOD(U3dStatus, u3dGetDynamicCompressedU32,(
    U3dDecoder*     pCtx, 
    U3DCompCtxID    compCtxID,
    U32             *value))
{
	U3dStatus   status = u3dStsNoErr;
    U32         codeCumFreq = 1;
    U3dStatus   rez;
    U32			valueToRead     = 0;
    U32			escape          = 0;
    U32			totalSymbolFreq = 1;
    U32			cumSymbolFreq   = 0;
    U32			symbolFreq      = 1;
    U32			range           = 0;
    U32			code            = 0;
    U32			bitCount		= 0;
    U32			underflowCount	= 0;
	U64			readNumber		= 1;
    U32			maskedState;
    U32			savedBits;
    U32			state;
    U32			high;
    U32			low;

    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DDECODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */
    if(pCtx->compCtx == 0) {
        return u3dStsNotSupportedErr;
    } /* if */
    if(compCtxID > pCtx->compCtxLast || compCtxID == 0) {
        return u3dStsBadArgErr;
    } /* if */
    if(pCtx->compCtx[compCtxID].inuse == 0 || 
	   pCtx->compCtx[compCtxID].histogram == 0) {
        return u3dStsBadArgErr;
    } /* if */
    if(pCtx->bitstreamposition == pCtx->bitstreamlastposition) {
        U64		  rez = 1;
        rez = GetStreamData(pCtx);
        if(rez == 0) {
            return u3dStsStreamOpErr;
        } /* if */
    } /* if */

    high            = pCtx->high;
    low             = pCtx->low;
    range           = high + 1 - low;

    // read code from bitstream
    {
        U8*  stream      = pCtx->bitstreamposition;
        U8   bitshift    = pCtx->bitshift;
	    U32  temp;

        // read 1 bit
		temp    = (((*stream) >> bitshift)&0x01) << 15;
        if(pCtx->underflowCount != 0) {
            // skipp underflow
            bitshift    += (U8)(pCtx->underflowCount);
            stream      += (bitshift>> 3);
            bitshift    &= 0x7;
        } /* if */
		// read 15 bits
        READ_8BITS_FROM_STREAM(stream, *(((U8*)&code) + c32De[0]), bitshift);
        READ_8BITS_FROM_STREAM(stream, *(((U8*)&code) + c32De[1]), bitshift);
		code &= 0xFFFE;
		// swap
		code = (cSwap8Dec[(code >> 12) & 0xf] ) |
			   ((cSwap8Dec[(code >> 8) & 0xf ] << 4 )) |
			   ((cSwap8Dec[(code >> 4) & 0xf] << 8)) |
			   ((cSwap8Dec[code & 0xf])<< 12 );
		code |= temp;
    }
    
    // Dynamic Compresion Context
    
    rez = u3dGetTotalSymbolFreq(pCtx->compCtx[compCtxID].histogram, 
                                &totalSymbolFreq);
    if(rez) {
        return rez;
    } /* if */

    codeCumFreq   = (totalSymbolFreq * (1 + code - low) - 1) / range;
    rez = u3dGetSymbolFromFreq(pCtx->compCtx[compCtxID].histogram, 
                                codeCumFreq, &valueToRead);
    if(rez) {
        return rez;
    } /* if */
    rez = u3dGetSymbolFreq(pCtx->compCtx[compCtxID].histogram, 
                            valueToRead, &symbolFreq);
    if(rez) {
        return rez;
    } /* if */
    rez = u3dGetCumSymbolFreq(pCtx->compCtx[compCtxID].histogram, 
                                valueToRead, &cumSymbolFreq);
    if(rez) {
        return rez;
    } /* if */
    rez = u3dHistogramDynamicAddSymbol(pCtx->compCtx[compCtxID].histogram, 
                                        valueToRead);
    if(rez) {
        return rez;
    } /* if */

	high    = low - 1 + range * (cumSymbolFreq + symbolFreq) / totalSymbolFreq;
    low     = low + range * cumSymbolFreq / totalSymbolFreq;
	state	= (low << 16) | high;

	// Fast count the first 4 bits
	bitCount	= cReadCount[(((low >> 12) ^ (high >> 12)) & 0xF)];
	state		&= cFastNotMask[bitCount];
	state		<<= bitCount;
	state		|= ((1 << bitCount) - 1);

    // Regular count the rest
	maskedState	= cHalfMask & state;
	while(0 == maskedState || cHalfMask == maskedState) {
		state		= ((cNotHalfMask & state) << 1) | 1;
		maskedState	= cHalfMask & state;
		bitCount++;
	} /* while */
    // Count underflow
	savedBits	= maskedState;
	if(bitCount > 0) {
		bitCount	+= pCtx->underflowCount;
		pCtx->underflowCount	= 0;
	} /* if */
	maskedState	= cQuarterMask & state;
	while(0x40000000 == maskedState) {
		state	&= cNotThreeQuarterMask;
		state	<<= 1;
		state	|= 1;
		maskedState	= cQuarterMask & state;
		underflowCount++;
	} /* while */
    // store the current state
	state				 |= savedBits;
    pCtx->high           = state & 0x0000FFFF;
    pCtx->low            = state >> 16;
    pCtx->underflowCount += underflowCount;
	// shift in bitstream
	SHIFT_NBITS_IN_STREAM(pCtx, (U8)bitCount, readNumber);

    if(valueToRead == 0) {
        // escape symbol
		U3dStatus status = u3dStsNoErr;
		U8*		  value_t = (U8*)value;

		status = u3dHistogramDynamicAddSymbol(
					pCtx->compCtx[compCtxID].histogram,
					(*value) + 1);
	    if(status == u3dStsDataOverflowErr) {
			status = u3dStsNoErr;
        } /* if */		
		status = intGetU8(pCtx, value_t + c32De[0]);
		if(status != u3dStsNoErr) {
			return status;
		}
		status = intGetU8(pCtx, value_t + c32De[1]);
		if(status != u3dStsNoErr) {
			return status;
		}
		status = intGetU8(pCtx, value_t + c32De[2]);
		if(status != u3dStsNoErr) {
			return status;
		}
		status = intGetU8(pCtx, value_t + c32De[3]);
		if(status != u3dStsNoErr) {
			return status;
		}

	} else {
	    *value  = (U32)(valueToRead - 1);
	}/* if */

#ifdef U3D_LOGDECODER
	// dynamic context
	// type, context, value
	fprintf(pCtx->logFile, "%d, %lu, %lu\n", 1, range, *value);
#endif

    return status;
} /* u3dGetDynamicCompressedU32 */
