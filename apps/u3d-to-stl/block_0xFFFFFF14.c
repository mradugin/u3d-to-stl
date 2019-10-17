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

#include "u3dparsefile.h"

U3dStatus u3dDisposeInfo0xFFFFFF14(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData) 
{
	U3dModifierChain    modifierChain;
	xmlNodePtr	 		curnode = u3dcb->curnode;
	U32                 shift = 0;
	char                letter;
    U32   				index = 0;
	char		 		value[65536];

	if(curnode == 0) {
		return u3dStsBadArgErr;
	} /* if */
	u3dcb->data = pData;
    u3dcb->size = size;
    u3dDecoderReset(u3dcb->u3ddecoder, u3dcb, myMap);
	if(size < sizeof(U16)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U16);
    u3dGetU16(u3dcb->u3ddecoder, &(modifierChain.name.size));
    pData += sizeof(U16);
    shift += sizeof(U16);
    modifierChain.name.string  = pData;

    for(index = 0; index < modifierChain.name.size; index++) {
        char    s;
		if(size < sizeof(U8)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U8);
        u3dGetU8(u3dcb->u3ddecoder, &s);
    } /* for */
    pData += modifierChain.name.size;
    shift += modifierChain.name.size;

	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
    u3dGetU32(u3dcb->u3ddecoder, &(modifierChain.type));
    pData += sizeof(U32);
    shift += sizeof(U32);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
    u3dGetU32(u3dcb->u3ddecoder, &(modifierChain.attributes));
    pData += sizeof(U32);
    shift += sizeof(U32);
    if(modifierChain.attributes & 0x01) {
        U32 X;
        modifierChain.sphere = 0;
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
        u3dGetU32(u3dcb->u3ddecoder, &X);
        pData += sizeof(F32); // X
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
        u3dGetU32(u3dcb->u3ddecoder, &X);
        pData += sizeof(F32); // Y
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
        u3dGetU32(u3dcb->u3ddecoder, &X);
        pData += sizeof(F32); // Z
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
        u3dGetU32(u3dcb->u3ddecoder, &X);
        pData += sizeof(F32); // R
        shift += (sizeof(F32) << 2);
    } /* if */
    if (modifierChain.attributes & 0x02) {
        U32 X;
        modifierChain.box = 0;
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
        u3dGetU32(u3dcb->u3ddecoder, &X);
        pData += sizeof(F32); // Xmin
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
        u3dGetU32(u3dcb->u3ddecoder, &X);
        pData += sizeof(F32); // Ymin
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
        u3dGetU32(u3dcb->u3ddecoder, &X);
        pData += sizeof(F32); // Zmin
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
        u3dGetU32(u3dcb->u3ddecoder, &X);
        pData += sizeof(F32); // XMax
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
        u3dGetU32(u3dcb->u3ddecoder, &X);
        pData += sizeof(F32); // YMax
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
        u3dGetU32(u3dcb->u3ddecoder, &X);
        pData += sizeof(F32); // ZMax
        shift += (sizeof(F32) * 6);
    } /* if */
//    modifierChain.attributes = 0;
    modifierChain.padding    = (0x04 - ((U32)pData) & 0x03) & 0x03;//???
    pData += modifierChain.padding;
    shift += modifierChain.padding;
    for(index = 0; index < modifierChain.padding; index++) {
        char    s;
		if(size < sizeof(U8)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U8);
        u3dGetU8(u3dcb->u3ddecoder, &s);
    } /* for */
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
    u3dGetU32(u3dcb->u3ddecoder, &(modifierChain.modifierCount));
    pData += sizeof(U32);
    shift += sizeof(U32);
    modifierChain.modifierDeclaration = pData;
    *readData  = shift;

	letter = modifierChain.name.string[modifierChain.name.size - 1];
	modifierChain.name.string[modifierChain.name.size - 1] = 0;
	sprintf(value, "%s%c", modifierChain.name.string, letter);
	xmlNewProp(curnode, "name", value);
	sprintf(value, "%lu", modifierChain.type);
	xmlNewProp(curnode, "type", value);
	sprintf(value, "%lu", modifierChain.attributes);
	xmlNewProp(curnode, "attribute", value);
	modifierChain.name.string[modifierChain.name.size - 1] = letter;
	u3dcb->callLevel	+= 3;
	u3dModifierChainExpose(u3dcb->u3dparser, &modifierChain, 
						   size, position, u3dcb);
	u3dcb->callLevel	-= 3;

    return u3dStsNoErr;

} /* u3dDisposeInfo0xFFFFFF14 */

