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

U3dStatus u3dDisposeInfo0xFFFFFF51(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData)
{
	xmlNodePtr	curnode = u3dcb->curnode;
	xmlNodePtr	node;
	U32         shift = 0;
	U16			stringlen;
	U32			index;
	U32			attributes;
	U8			type;
	F32			red;
	F32			green;
	F32			blue;
	F32			reserved;
	F32			constant;
	F32			linear;
	F32			quadtratic;
	F32			angle;
	F32			intensity;
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
	if(size < sizeof(U8)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U8);
	u3dGetU8(u3dcb->u3ddecoder, &type);
	sprintf(value, "0x%X", type);
	xmlNewProp(curnode, "type", value);


	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
	node  = xmlNewChild(curnode, 0, "Color", 0);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&red);
	sprintf(value, "%lf", red);
	xmlNewProp(node, "red", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&green);
	sprintf(value, "%lf", green);
	xmlNewProp(node, "green", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&blue);
	sprintf(value, "%lf", blue);
	xmlNewProp(node, "blue", value);
	if(size < sizeof(U8)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&reserved);
	sprintf(value, "%lf", reserved);
	xmlNewProp(node, "reserved", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */

	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
	node  = xmlNewChild(curnode, 0, "Attenuation", 0);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&constant);
	sprintf(value, "%lf", constant);
	xmlNewProp(node, "constant", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&linear);
	sprintf(value, "%lf", linear);
	xmlNewProp(node, "linear", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&quadtratic);
	sprintf(value, "%lf", quadtratic);
	xmlNewProp(node, "quadtratic", value);

	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&angle);
	sprintf(value, "%lf", angle);
	xmlNewProp(curnode, "angle", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&intensity);
	sprintf(value, "%lf", intensity);
	xmlNewProp(curnode, "intensity", value);
	return u3dStsNoErr;
} /* u3dDisposeInfo0xFFFFFF51 */


