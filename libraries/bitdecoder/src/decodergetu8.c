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

extern U8   cSwap8Dec[];

/*
 * U3D Bitstream decoder functions u3dGetU64/U32/U16/U8
 * Purpose
 *      Get an U32/U16/U8 data from bitstream.
 *  Parameters
 *  (in)pCtx - the pointer to the decoder context of bitstream that will be 
 *             used to get U64/U32/U16/U8 data
 *  (out)value - the value that should be gotten from bitstream 
 *  Return
 *      u3dStsNoErr if the value was successfully added to bitstream.
 *      u3dStsContextMatchErr if pCtx isn't valid
 *      u3dStsNullPtrErr if pCtx is null
 */
U3D_METHOD(U3dStatus, u3dGetU8 ,(U3dDecoder* pCtx, U8  *value))
{
	U3dStatus status = u3dStsNoErr;

    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DDECODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */

	status = intGetU8(pCtx, value);
#ifdef U3D_LOGDECODER
	fprintf(pCtx->logFile, "%d, %lu, %lu\n", 0, 0, *value);
#endif

	return status;
} /* u3dGetU8 */

INT_METHOD(U3dStatus, intGetU8 ,(U3dDecoder* pCtx, U8  *value))
{
	U3dStatus status = u3dStsNoErr;
    U64		  rez = 1;

    if(pCtx->bitstreamposition == pCtx->bitstreamlastposition) {
        rez = GetStreamData(pCtx);
        if(rez == 0) {
            return u3dStsStreamOpErr;
        } /* if */
    } /* if */

	if(0xFFFF == pCtx->high && 0 == pCtx->low  && 0 == pCtx->underflowCount) {
		U8*	stream = pCtx->bitstreamposition;
//		GET_NBITS_FROM_STREAM(pCtx, *value, 8, rez);
		READ_8BITS_FROM_STREAM(stream, *value, pCtx->bitshift);
		SHIFT_NBITS_IN_STREAM(pCtx, 8, rez);
	} else {
		status	= intGetCompressedU8(pCtx, 0x100, value);
		*value	= (cSwap8Dec[(*value) & 0xf] << 4) | 
				  (cSwap8Dec[(*value) >> 4]);
	} /* if */
    return status;
} /* intGetU8 */
