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

#include "u3dpipeline.h"

/*
 * U3D Parser function u3dDisposeModifierChainInfo
 * Purpose
 *      Dispose U3D modifier chain from memory block to structure
 *  Parameters
 *  (in) pData
 *  (in) size
 *  (out)modifierChain
 *  Return
 *      u3dStsNoErr if initialization was successful.
 *  Notes
 */
U3D_METHOD(U3dStatus, u3dDisposeModifierChainInfo,(
        U3dParser* pCtx,
        U8* pData, U32 size,  U32* readData,
        U3dModifierChain* modifierChain)
{
    U32    shift = 0;

    modifierChain->name.size    = U3D_MAKE_U16(pData);
    pData += sizeof(U16);
    shift += sizeof(U16);
    modifierChain->name.string  = pData;
    pData += modifierChain->name.size;
    shift += modifierChain->name.size;
    modifierChain->type         = U3D_MAKE_U32(pData);
    pData += sizeof(U32);
    shift += sizeof(U32);
    modifierChain->attributes   = U3D_MAKE_U32(pData);
    pData += sizeof(U32);
    shift += sizeof(U32);
    if(modifierChain->attributes & 0x01) {
        modifierChain->sphere = 0;
        pData += sizeof(F32); // X
        pData += sizeof(F32); // Y
        pData += sizeof(F32); // Z
        pData += sizeof(F32); // R
        shift += (sizeof(F32) << 2);
    } /* if */
    if(modifierChain->attributes & 0x02) {
        modifierChain->box = 0;
        pData += sizeof(F32); // Xmin
        pData += sizeof(F32); // Ymin
        pData += sizeof(F32); // Zmin
        pData += sizeof(F32); // XMax
        pData += sizeof(F32); // YMax
        pData += sizeof(F32); // ZMax
        shift += (sizeof(F32) * 6);
    } /* if */
//    modifierChain->attributes = 0;
    modifierChain->padding    = (0x04 - ((U32)pData) & 0x03) & 0x03;//???
    pData += modifierChain->padding;
    shift += modifierChain->padding;
    modifierChain->modifierCount       = U3D_MAKE_U32(pData);
    pData += sizeof(U32);
    shift += sizeof(U32);
    modifierChain->modifierDeclaration = pData;
    *readData  = shift;

    return u3dStsNoErr;

} /* u3dDisposeModifierChainInfo */

