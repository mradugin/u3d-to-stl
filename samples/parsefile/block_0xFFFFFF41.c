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

U3dStatus u3dDisposeInfo0xFFFFFF41(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData)
{
	xmlNodePtr		curnode = u3dcb->curnode;
	xmlNodePtr		node;
	U32         	shift = 0;
	U16				stringlen;
	U32				index;
	U32				chainindex;
	U32				attributes;
	U32				commandcount;
	U3dMatrix4x4f   transform;
	char			value[65536];

	if(curnode == 0) {
		return u3dStsBadArgErr;
	} /* if */
	u3dcb->data = pData;
	u3dcb->size = size;
	u3dDecoderReset(u3dcb->u3ddecoder, u3dcb, myMap);
	if(size < sizeof(U16)) {
		return 0;
	} /* if */
	size -= sizeof(U16);
	u3dGetU16(u3dcb->u3ddecoder, &stringlen);
	if(size < stringlen) {
		return 0;
	} /* if */
	size -= stringlen;
	for(index = 0; index < stringlen; index++) {
		u3dGetU8(u3dcb->u3ddecoder, &value[index]);
	} /* for */
	value[index] = 0;
	xmlNewProp(curnode, "name", value);
	if(size < sizeof(U32)) {
		return u3dStsBadArgErr;
	} /* if */
	size -= sizeof(U32);
	u3dGetU32(u3dcb->u3ddecoder, &chainindex);
	sprintf(value, "%lu", chainindex);
	xmlNewProp(curnode, "chainindex", value);
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
	u3dGetU32(u3dcb->u3ddecoder, &commandcount);
	for(index = 0; index < commandcount; index++) {
		U32	command;
		F32	x;
		F32	y;
		F32 control1x;
		F32	control1y;
		F32 control2x;
		F32	control2y;

		xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
		node  = xmlNewChild(curnode, 0, "Glyph", 0);
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, &command);
		sprintf(value, "0x%X", command);
		xmlNewProp(node, "command", value);
		if(command == 3) {
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&x);
			sprintf(value, "%f", x);
			xmlNewProp(node, "moveto_x", value);
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&y);
			sprintf(value, "%f", y);
			xmlNewProp(node, "moveto_y", value);
		} else if (command == 4) {
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&x);
			sprintf(value, "%f", x);
			xmlNewProp(node, "lineto_x", value);
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&y);
			sprintf(value, "%f", y);
			xmlNewProp(node, "lineto_y", value);
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
		} else if (command == 5) {
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&x);
			sprintf(value, "%f", x);
			xmlNewProp(node, "control1_x", value);
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&y);
			sprintf(value, "%f", y);
			xmlNewProp(node, "control1_y", value);
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&x);
			sprintf(value, "%f", x);
			xmlNewProp(node, "control2_x", value);
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&y);
			sprintf(value, "%f", y);
			xmlNewProp(node, "control2_y", value);
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&x);
			sprintf(value, "%f", x);
			xmlNewProp(node, "end_point_x", value);
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&y);
			sprintf(value, "%f", y);
			xmlNewProp(node, "end_point_y", value);
		} else if (command == 7) {
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&x);
			sprintf(value, "%f", x);
			xmlNewProp(node, "end_glyph_offset_x", value);
			if(size < sizeof(U32)) {
				return u3dStsBadArgErr;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, (U32*)&y);
			sprintf(value, "%f", y);
			xmlNewProp(node, "end_glyph_offset_y", value);
		} /* if */
	} /* for */
	// transform matrixes
	xmlNodeAddContent(curnode, indent[u3dcb->callLevel + 3]);
	node  = xmlNewChild(curnode, 0, "Transform", 0);
	for(index = 0; index < 16; index++) {
		if(size < sizeof(U32)) {
			return u3dStsBadArgErr;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, (U32*)&transform.p[index]);
	} /* for */
	for(index = 0; index < 4; index++) {
		xmlNodeAddContent(node, indent[u3dcb->callLevel + 4]);
		sprintf(value     , "% 011f; ", transform.p[index]);
		sprintf(&value[13], "% 011f; ", transform.p[index + 4]);
		sprintf(&value[26], "% 011f; ", transform.p[index + 8]);
		sprintf(&value[39], "% 011f; ", transform.p[index + 12]);
		xmlNodeAddContent(node, value);
	} /* for */
	xmlNodeAddContent(node, indent[u3dcb->callLevel + 3]);

	return u3dStsNoErr;
} /* u3dDisposeInfo0xFFFFFF41 */

