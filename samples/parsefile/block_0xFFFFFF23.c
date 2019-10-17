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

U3dStatus u3dDisposeInfo0xFFFFFF23(U3dCallBack *u3dcb, U32 position,
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

	return u3dStsNoErr;
} /* u3dDisposeInfo0xFFFFFF23 */


