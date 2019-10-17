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

extern U8 c64En[];
/*
 * U3D Bitstream encoder functions u3dAddU64/U32/U16/U8/String
 * Purpose
 *      Added an U32/U16/U8/String data to bitstream.
 *  Parameters
 *  (in)pCtx - the pointer to the encoder context of bitstream that will be 
 *             updated by new U64/U32/U16/U8 data
 *  (in)value - the value that should be added to bitstream 
 *  Return
 *      u3dStsNoErr if the value was successfully added to bitstream.
 *      u3dStsContextMatchErr if pCtx isn't valid
 *      u3dStsNullPtrErr if pCtx is null
 */
U3D_METHOD(U3dStatus, u3dAddU64,(U3dEncoder* pCtx, U64 value))
{
	U3dStatus status = u3dStsNoErr;
	U8*		  value_t = (U8*)&value;
    
	if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DENCODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */
    if(pCtx->bitstreamposition == pCtx->bitstreamlastposition) {
        intEncoderFlush(pCtx);
    } /* if */
#ifdef U3D_LOGENCODER
	fprintf(pCtx->logFile, "%d, %lu, %lu\n", 3, 0, value);
#endif

	status = intAddU8(pCtx, *(value_t + c64En[0]));
	if(status != u3dStsNoErr) {
		return status;
	}
	status = intAddU8(pCtx, *(value_t + c64En[1]));
	if(status != u3dStsNoErr) {
		return status;
	}
	status = intAddU8(pCtx, *(value_t + c64En[2]));
	if(status != u3dStsNoErr) {
		return status;
	}
	status = intAddU8(pCtx, *(value_t + c64En[3]));
	if(status != u3dStsNoErr) {
		return status;
	}
	status = intAddU8(pCtx, *(value_t + c64En[4]));
	if(status != u3dStsNoErr) {
		return status;
	}
	status = intAddU8(pCtx, *(value_t + c64En[5]));
	if(status != u3dStsNoErr) {
		return status;
	}
	status = intAddU8(pCtx, *(value_t + c64En[6]));
	if(status != u3dStsNoErr) {
		return status;
	}
	status = intAddU8(pCtx, *(value_t + c64En[7]));
	
	return status;
} /* u3dAddU64 */

