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
#include <stdio.h>
//#define DO_TRACE

extern const U32 c32De[];
extern const U32 c24De[];
extern const U32 c16De[];

/*
 * U3D Bitstream decoder functions u3dGetArrayU32
 * Purpose
 *      Get an array of U32 data from bitstream.
 *  Parameters
 *  (in)pCtx - the pointer to the decoder context of bitstream that will be 
 *             used to get U32 data array
 *  (in)values - the array of values that should be gotten from bitstream
 *  (in)count - number of values in array
 *  (in)stride - shift in array between values in elements
 *  (in)actualBits - the size in bits of each values in values array
 *  Return
 *      u3dStsNoErr if the values were successfully gotten to bitstream.
 *      u3dStsContextMatchErr if pCtx isn't valid
 *      u3dStsNullPtrErr if pCtx or  values is null
 *      u3dStsBadArgErr if count, stride or actualBits is 0 or actualBits > 32
 */
U3D_METHOD(U3dStatus, u3dGetArrayU32,(
    U3dDecoder*     pCtx, 
    U32*            values, 
    U32             count,
    U32             stride,
    U8              actualBits))
{
	U3dStatus	status = u3dStsNoErr;
    U32			index;
    U8			*value;
	U16			range = 1;
    U64			rez = 1;
    
    if(pCtx == 0 || values == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DDECODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */
    if(count == 0 || stride == 0 || actualBits == 0 || actualBits > 32) {
        return u3dStsBadArgErr;
    } /* if */
#ifdef DO_TRACE
    fprintf(stdout, "actual bitsize %d\n", actualBits);
    fprintf(stdout, "position %lu shift %lu\n", 
            pCtx->bitstreamposition - pCtx->bitstreamallocated,
            pCtx->bitshift);
#endif   
    
	if(0xFFFF == pCtx->high && 0 == pCtx->low  && 0 == pCtx->underflowCount) {
		if(actualBits > 24) {
			actualBits -= 24;
			range	= 1 << actualBits;
			for(index = 0; index < count; index++) {
				*values = 0;
				value   = (U8*)values;
				GET_NBITS_FROM_STREAM(pCtx, value[c32De[0]], 8, rez);
				if(rez == 0) {
					return u3dStsStreamOpErr;
				} /* if */
				GET_NBITS_FROM_STREAM(pCtx, value[c32De[1]], 8, rez);
				if(rez == 0) {
					return u3dStsStreamOpErr;
				} /* if */
				GET_NBITS_FROM_STREAM(pCtx, value[c32De[2]], 8, rez);
				if(rez == 0) {
					return u3dStsStreamOpErr;
				} /* if */
				GET_NBITS_FROM_STREAM(pCtx, value[c32De[3]], actualBits, rez);
				if(rez == 0) {
					return u3dStsStreamOpErr;
				} /* if */
				values += stride;
			} /* for */
		} else if (actualBits > 16) {
			actualBits -= 16;
			range	= 1 << actualBits;
			for(index = 0; index < count; index++) {
				*values = 0;
				value   = (U8*)values;
				GET_NBITS_FROM_STREAM(pCtx, value[c24De[0]], 8, rez);
				if(rez == 0) {
					return u3dStsStreamOpErr;
				} /* if */
				GET_NBITS_FROM_STREAM(pCtx, value[c24De[1]], 8, rez);
				if(rez == 0) {
					return u3dStsStreamOpErr;
				} /* if */
				GET_NBITS_FROM_STREAM(pCtx, value[c24De[2]], actualBits, rez);
				if(rez == 0) {
					return u3dStsStreamOpErr;
				} /* if */
				values += stride;
			} /* for */
		} else if (actualBits > 8) {
			actualBits -= 8;
			range	= 1 << actualBits;
			for(index = 0; index < count; index++) {
				*values = 0;
				value   = (U8*)values;
				GET_NBITS_FROM_STREAM(pCtx, value[c16De[0]], 8, rez);
				if(rez == 0) {
					return u3dStsStreamOpErr;
				} /* if */
				GET_NBITS_FROM_STREAM(pCtx, value[c16De[1]], actualBits, rez);
				if(rez == 0) {
					return u3dStsStreamOpErr;
				} /* if */
				values += stride;
			} /* for */
		} else {
			range	= 1 << actualBits;
			for(index = 0; index < count; index++) {
				*values = 0;
				value   = (U8*)values;
				GET_NBITS_FROM_STREAM(pCtx, value[0], actualBits, rez);
				if(rez == 0) {
					return u3dStsStreamOpErr;
				} /* if */
				values += stride;
			} /* for */
		} /* if */
	} else {
		if(actualBits > 24) {
			actualBits -= 24;
			range	= 1 << actualBits;
			for(index = 0; index < count; index++) {
				*values = 0;
				value   = (U8*)values;
				status = intGetCompressedU8(pCtx, 256, value + c32De[0]);
				if(status != u3dStsNoErr) {
					return status;
				}
				status = intGetCompressedU8(pCtx, 256, value + c32De[1]);
				if(status != u3dStsNoErr) {
					return status;
				}
				status = intGetCompressedU8(pCtx, 256, value + c32De[2]);
				if(status != u3dStsNoErr) {
					return status;
				}
				status = intGetCompressedU8(pCtx, range, value + c32De[3]);
				if(status != u3dStsNoErr) {
					return status;
				}
				values += stride;
			} /* for */
		} else if (actualBits > 16) {
			actualBits -= 16;
			range	= 1 << actualBits;
			for(index = 0; index < count; index++) {
				*values = 0;
				value   = (U8*)values;
				status = intGetCompressedU8(pCtx, 256, value + c24De[0]);
				if(status != u3dStsNoErr) {
					return status;
				}
				status = intGetCompressedU8(pCtx, 256, value + c24De[1]);
				if(status != u3dStsNoErr) {
					return status;
				}
				status = intGetCompressedU8(pCtx, range, value + c24De[2]);
				if(status != u3dStsNoErr) {
					return status;
				}
				values += stride;
			} /* for */
		} else if (actualBits > 8) {
			actualBits -= 8;
			range	= 1 << actualBits;
			for(index = 0; index < count; index++) {
				*values = 0;
				value   = (U8*)values;
				status = intGetCompressedU8(pCtx, 256, value + c16De[0]);
				if(status != u3dStsNoErr) {
					return status;
				}
				status = intGetCompressedU8(pCtx, range, value + c16De[1]);
				if(status != u3dStsNoErr) {
					return status;
				}
				values += stride;
			} /* for */
		} else {
			range	= 1 << actualBits;
			for(index = 0; index < count; index++) {
				*values = 0;
				value   = (U8*)values;
				status = intGetCompressedU8(pCtx, range, value);
				if(status != u3dStsNoErr) {
					return status;
				}
				values += stride;
			} /* for */
		} /* if */
	} /* if */
#ifdef DO_TRACE
        fprintf(stdout, "position %lu shift %lu\n", 
                pCtx->bitstreamposition - pCtx->bitstreamallocated,
                pCtx->bitshift);
#endif        
    
    return u3dStsNoErr;
} /* u3dAddArrayU32 */
