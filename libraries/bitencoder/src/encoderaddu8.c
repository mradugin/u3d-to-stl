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

extern U8 cSwap8[];
/*
 * U3D Bitstream encoder functions u3dAddU32/U16/U8/String
 * Purpose
 *      Added an U32/U16/U8/String data to bitstream.
 *  Parameters
 *  (in)pCtx - the pointer to the encoder context of bitstream that will be 
 *             updated by new U32/U16/U8 data
 *  (in)value - the value that should be added to bitstream 
 *  Return
 *      u3dStsNoErr if the value was successfully added to bitstream.
 *      u3dStsContextMatchErr if pCtx isn't valid
 *      u3dStsNullPtrErr if pCtx is null
 */
U3D_METHOD(U3dStatus, u3dAddU8,(U3dEncoder* pCtx, U8 value))
{
	U3dStatus status = u3dStsNoErr;
    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DENCODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */
    if(pCtx->bitstreamposition == pCtx->bitstreamlastposition) {
        u3dEncoderFlush(pCtx);
    } /* if */
#ifdef U3D_LOGENCODER
	fprintf(pCtx->logFile, "%d, %lu, %lu\n", 0, 0, value);
#endif

    status = intAddU8(pCtx, value);

    return status;
} /* u3dAddU8 */

INT_METHOD(U3dStatus, intAddU8,(U3dEncoder* pCtx, U8 value))
{
	U3dStatus status = u3dStsNoErr;

	if(0xFFFF == pCtx->high && 0 == pCtx->low  && 0 == pCtx->underflowCount) {
		if(pCtx->bitshift == 0) {
			*(pCtx->bitstreamposition) = value;
			pCtx->bitstreamposition++;
		} else {
			ADD_NBITS_TO_STREAM(pCtx, value, 8);
		} /* if */
	} else {
		U8	value_t = value;
		value_t	= (cSwap8[(value) & 0xf] << 4) | ( cSwap8[(value) >> 4]);
		status = intAddCompressedU8(pCtx, 0x100, (U8)value_t);
	} /* if */

    return status;
} /* intAddU8 */

