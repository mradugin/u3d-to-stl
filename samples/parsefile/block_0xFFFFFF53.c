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

U3dStatus u3dDisposeInfo0xFFFFFF53(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData)
{
	xmlNodePtr	curnode = u3dcb->curnode;
	xmlNodePtr	node;
	xmlNodePtr	node1;
	U32         shift = 0;
	U16			stringlen;
	U32			index;
	U32			attributes;
	F32			testreference;
	U32			testfunctions;
	U32			blendfunctions;
	U32			renderpass;
	U32			shaderchanels;
	U32			texturechanels;
	U32			texturecount = 0;
	char		value[65536];

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
	u3dGetU16(u3dcb->u3ddecoder, &stringlen);
	if(size < stringlen) {
		return u3dStsBadArgErr;
	} /* if */
	for(index = 0; index < stringlen; index++) {
		u3dGetU8(u3dcb->u3ddecoder, &value[index]);
	} /* for */
	value[index] = 0;
	xmlNewProp(curnode, "name", value);

	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, &attributes);
	sprintf(value, "0x%X", attributes);
	xmlNewProp(curnode, "attributes", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&testreference);
	sprintf(value, "%lf", testreference);
	xmlNewProp(curnode, "testreference", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, &testfunctions);
	sprintf(value, "0x%X", testfunctions);
	xmlNewProp(curnode, "testfunctions", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, &blendfunctions);
	sprintf(value, "0x%X", blendfunctions);
	xmlNewProp(curnode, "blendfunctions", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, &renderpass);
	sprintf(value, "%lu", renderpass);
	xmlNewProp(curnode, "renderpass", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, &shaderchanels);
	sprintf(value, "%lu", shaderchanels);
	xmlNewProp(curnode, "shaderchanels", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, &texturechanels);
	sprintf(value, "%lu", texturechanels);
	xmlNewProp(curnode, "texturechanels", value);
	for(index = 0; index < 8; index++) {
		U32 test = 1 << index;
		if(texturechanels & test) {
			texturecount++;
		} /* if */
	} /* for */
	for(index = 0; index < texturecount; index++) {
		F32				intensity;
		U8				blendfunction;
		U8				blendsource;
		F32				blendconstant;
		U8				mode;
		U3dMatrix4x4f   transform;
		U3dMatrix4x4f   wrap;
		U8				repeat;
		U32				index1;

		xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
		node  = xmlNewChild(curnode, 0, "Texture", 0);
		if(size < sizeof(U16)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U16);
		u3dGetU16(u3dcb->u3ddecoder, &stringlen);
		if(size < stringlen) {
			return u3dStsBadArgErr;
		} /* if */
		for(index1 = 0; index1 < stringlen; index1++) {
			u3dGetU8(u3dcb->u3ddecoder, &value[index1]);
		} /* for */
		value[index1] = 0;
		xmlNewProp(node, "name", value);

		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&intensity);
		sprintf(value, "%lf", intensity);
		xmlNewProp(node, "intensity", value);
		if(size < sizeof(U8)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U8);
		u3dGetU8(u3dcb->u3ddecoder, &blendfunction);
		sprintf(value, "%lu", blendfunction);
		xmlNewProp(node, "blendfunction", value);
		if(size < sizeof(U8)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U8);
		u3dGetU8(u3dcb->u3ddecoder, &blendsource);
		sprintf(value, "%lu", blendsource);
		xmlNewProp(node, "blendsource", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&blendconstant);
		sprintf(value, "%lf", blendconstant);
		xmlNewProp(node, "blendconstant", value);
		if(size < sizeof(U8)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U8);
		u3dGetU8(u3dcb->u3ddecoder, &mode);
		sprintf(value, "0x%X", mode);
		xmlNewProp(node, "mode", value);

		// transform matrixes
		xmlNodeAddContent(node, indent[u3dcb->callLevel + 4]);
		node1  = xmlNewChild(node, 0, "Transform", 0);
		for(index1 = 0; index1 < 16; index1++) {
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&transform.p[index1]);
		} /* for */
		for(index1 = 0; index1 < 4; index1++) {
			xmlNodeAddContent(node1, indent[u3dcb->callLevel + 5]);
			sprintf(value     , "% 011f; ", transform.p[index1]);
			sprintf(&value[13], "% 011f; ", transform.p[index1 + 4]);
			sprintf(&value[26], "% 011f; ", transform.p[index1 + 8]);
			sprintf(&value[39], "% 011f; ", transform.p[index1 + 12]);
			xmlNodeAddContent(node1, value);
		} /* for */
		// wrap matrixes
		xmlNodeAddContent(node, indent[u3dcb->callLevel + 4]);
		node1  = xmlNewChild(node, 0, "Wrap", 0);
		for(index1 = 0; index1 < 16; index1++) {
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&wrap.p[index1]);
		} /* for */
		for(index1 = 0; index1 < 4; index1++) {
			xmlNodeAddContent(node1, indent[u3dcb->callLevel + 5]);
			sprintf(value     , "% 011f; ", wrap.p[index1]);
			sprintf(&value[13], "% 011f; ", wrap.p[index1 + 4]);
			sprintf(&value[26], "% 011f; ", wrap.p[index1 + 8]);
			sprintf(&value[39], "% 011f; ", wrap.p[index1 + 12]);
			xmlNodeAddContent(node1, value);
		} /* for */
		xmlNodeAddContent(node1, indent[u3dcb->callLevel + 4]);
		xmlNodeAddContent(node, indent[u3dcb->callLevel + 3]);
		if(size < sizeof(U8)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U8);
		u3dGetU8(u3dcb->u3ddecoder, &repeat);
		sprintf(value, "0x%X", repeat);
		xmlNewProp(node, "repeat", value);
	} /* for */
	return u3dStsNoErr;
} /* u3dDisposeInfo0xFFFFFF53 */


