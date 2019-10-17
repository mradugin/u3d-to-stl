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

U3dStatus u3dDisposeInfo0xFFFFFF24(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData)
{
	xmlNodePtr		curnode = u3dcb->curnode;
	xmlNodePtr		node;
	xmlNodePtr		node1;
	U3dMatrix4x4f   transform;
	U32         	shift = 0;
	U16				stringlen;
	U32				index;
	U32				index1;
	U32				parentcout;
	U32				attributes;
	F32				nearclip;
	F32				farclip;
	F32				width;
	F32				height;
	F32				horizontal;
	F32				vertical;
	U32				backdropcount;
	U32				overlaycount;
	char			value[65536];

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

	// Parent Nodes data
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, &parentcout);
	for(index = 0; index < parentcout; index++) {
		xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
		node  = xmlNewChild(curnode, 0, "Parent", 0);
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
		xmlNodeAddContent(node1, indent[u3dcb->callLevel + 4]);
		xmlNodeAddContent(node, indent[u3dcb->callLevel + 3]);

	} /* for */
	xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
	node  = xmlNewChild(curnode, 0, "Resources", 0);
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
	u3dGetU32(u3dcb->u3ddecoder, &attributes);
	sprintf(value, "0x%X", attributes);
	xmlNewProp(curnode, "attributes", value);

	xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
	node  = xmlNewChild(curnode, 0, "Clipping", 0);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&nearclip);
	sprintf(value, "%E", nearclip);
	xmlNewProp(node, "nearclip", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&farclip);
	sprintf(value, "%E", farclip);
	xmlNewProp(node, "farclip", value);
	if(attributes < 2) {
		F32	projection;
		xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
		node  = xmlNewChild(curnode, 0, "Projection", 0);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&projection);
		sprintf(value, "%f", projection);
		xmlNewProp(node, "projection", value);
	} else if (attributes < 4) {
		F32	orthographic;
		xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
		node  = xmlNewChild(curnode, 0, "Orthographic", 0);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&orthographic);
		sprintf(value, "%f", orthographic);
		xmlNewProp(node, "orthographic", value);
	} else {
		U3dVector3f	projectionvector;
		xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
		node  = xmlNewChild(curnode, 0, "Projection_Vector", 0);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&projectionvector.p[1]);
		sprintf(value, "%f", projectionvector.p[1]);
		xmlNewProp(node, "x", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&projectionvector.p[2]);
		sprintf(value, "%f", projectionvector.p[2]);
		xmlNewProp(node, "y", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&projectionvector.p[3]);
		sprintf(value, "%f", projectionvector.p[3]);
		xmlNewProp(node, "x", value);
	} /* if */
	xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
	node  = xmlNewChild(curnode, 0, "View_Port", 0);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&width);
	sprintf(value, "%f", width);
	xmlNewProp(node, "width", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&height);
	sprintf(value, "%f", height);
	xmlNewProp(node, "height", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&horizontal);
	sprintf(value, "%f", horizontal);
	xmlNewProp(node, "horizontal", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&vertical);
	sprintf(value, "%f", vertical);
	xmlNewProp(node, "vertical", value);

	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, &backdropcount);
	for(index = 0; index < backdropcount; index++) {
        F32	blend;
		F32	rotation;
		F32	locationx;
		F32 locationy;
		F32	registrationx;
		F32 registrationy;
		F32	scalex;
		F32 scaley;

		xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
		node  = xmlNewChild(curnode, 0, "Backdrop", 0);
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
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&blend);
		sprintf(value, "%f", blend);
		xmlNewProp(node, "blend", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&rotation);
		sprintf(value, "%f", rotation);
		xmlNewProp(node, "rotation", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&locationx);
		sprintf(value, "%f", locationx);
		xmlNewProp(node, "locationx", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&locationy);
		sprintf(value, "%f", locationy);
		xmlNewProp(node, "locationy", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&registrationx);
		sprintf(value, "%d", registrationx);
		xmlNewProp(node, "registrationx", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&registrationy);
		sprintf(value, "%d", locationy);
		xmlNewProp(node, "registrationy", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&scalex);
		sprintf(value, "%f", scalex);
		xmlNewProp(node, "scalex", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&scaley);
		sprintf(value, "%f", scaley);
		xmlNewProp(node, "scaley", value);
	} /* for */

	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, (U32*)&overlaycount);
	for(index = 0; index < overlaycount; index++) {
		F32	blend;
		F32	rotation;
		F32	locationx;
		F32 locationy;
		I32	registrationx;
		I32 registrationy;
		F32	scalex;
		F32 scaley;

		xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
		node  = xmlNewChild(curnode, 0, "Overlay", 0);
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
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&blend);
		sprintf(value, "%f", blend);
		xmlNewProp(node, "blend", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&rotation);
		sprintf(value, "%f", rotation);
		xmlNewProp(node, "rotation", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&locationx);
		sprintf(value, "%f", locationx);
		xmlNewProp(node, "locationx", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&locationy);
		sprintf(value, "%f", locationy);
		xmlNewProp(node, "locationy", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&registrationx);
		sprintf(value, "%d", registrationx);
		xmlNewProp(node, "registrationx", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&registrationy);
		sprintf(value, "%d", locationy);
		xmlNewProp(node, "registrationy", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&scalex);
		sprintf(value, "%f", scalex);
		xmlNewProp(node, "scalex", value);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&scaley);
		sprintf(value, "%f", scaley);
		xmlNewProp(node, "scaley", value);
	} /* for */

	return u3dStsNoErr;
} /* u3dDisposeInfo0xFFFFFF24 */

