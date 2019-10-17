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
 *      u3dStsNullPtrErr if pCtx is null.
 *      u3dStsBadArgErr if pCtx is not valid context
 */
U3D_METHOD(U3dStatus, u3dAddString ,(U3dEncoder* pCtx, U3dString  value))
{
	U3dStatus	status	= u3dStsNoErr;
	U8*			string	= (U8*)value.string;
	U32			size	= value.size;
	U32			index;

	if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id != U3DENCODERCTX_ID) {
        return u3dStsContextMatchErr;
    } /* if */
	
	status = intAddU16(pCtx, size);
	if(status != u3dStsNoErr) {
		return status;
	} /* if */
#ifdef U3D_LOGENCODER
	fprintf(pCtx->logFile, "%d, %lu, %lu\n", 1, 0, size);
#endif	

	for(index = 0; index < size; index++) {
		status = intAddU8(pCtx, string[index]);
		if(status != u3dStsNoErr) {
			return status;
		} /* if */
#ifdef U3D_LOGENCODER
	fprintf(pCtx->logFile, "%d, %lu, %lu\n", 0, 0, string[index]);
#endif
	} /* for */
    
	return u3dStsNoErr;
} /* u3dAddString */

