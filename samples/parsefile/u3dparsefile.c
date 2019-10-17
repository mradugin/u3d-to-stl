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

char *indent[] = {	"\n",
					"\n ",
					"\n  ",
					"\n   ",
					"\n    ",
					"\n     ",
					"\n      ",
					"\n       ",
					"\n        ",
					"\n         ",
					"\n          "
				};

void* myMalloc(void* memCtx, U32 size)
{
    void*  res;

    res = malloc(size);
    return res;
} /* myMalloc */

void myFree(void* memCtx, void* buf)
{
    free(buf);
    return;
} /* myFree */

U64 myMap(U3dStream_cbCtx* pCtx, U8** pData, U64 size)
{
    U3dCallBack*  u3dcb = (U3dCallBack*)pCtx;
    U64           readByte = u3dcb->size;

    *pData      = u3dcb->data;
    u3dcb->size = 0;
    return readByte;
} /* myMap */


int BlockInfo(void* blockCtx, const U3dBlock *pBlock, const U32 position)
{
    U3dCallBack *u3dcb = blockCtx;
	xmlNodePtr	 curnode = u3dcb->curnode;
	xmlNodePtr	 node;
	xmlNodePtr	 node1;
	xmlNodePtr	 node2;
	xmlNodePtr	 node3;
	char		 value[65536];
    U32          shift = 0;

	if(curnode == 0) {
		curnode = xmlDocGetRootElement(u3dcb->xmldoc);
		if(curnode == 0) {
			return 0;
		} /* if */
	} /* if */

	xmlNodeAddContent(curnode, indent[u3dcb->callLevel]);
	node = xmlNewChild(curnode, 0, "Block", 0);
	sprintf(value, "0x%X", pBlock->type);
    xmlNewProp(node, "Type", value);
	sprintf(value, "0x%X", position);
    xmlNewProp(node, "pos_hex", value);
	sprintf(value, "%lu", position);
	xmlNewProp(node, "pos", value);
	xmlNodeAddContent(node, indent[u3dcb->callLevel + 1]);

	node1 = xmlNewChild(node, 0, "Data", 0);
	sprintf(value, "%lu", pBlock->data.size);
	xmlNewProp(node1, "size", value);
	sprintf(value, "%lu", pBlock->data.padding);
	xmlNewProp(node1, "padding_size", value);
	xmlNodeAddContent(node1, indent[u3dcb->callLevel + 2]);

	switch(pBlock->type) {
    /* File structure blocks */
    case U3D_BT_FILEHEADER:
		node2 = xmlNewChild(node1, 0, "File_Header", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0x00443355(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_FILEREF:
		node2 = xmlNewChild(node1, 0, "File_Reference", 0);
        break;
    case U3D_BT_MODIFIERCHAIN:
		node2 = xmlNewChild(node1, 0, "Modifier_Chain", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF14(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_PRIORITYUPDATE:
		node2 = xmlNewChild(node1, 0, "Priority_Update", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF15(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_NEWOBJECTTYPE:
		node2 = xmlNewChild(node1, 0, "New_Object_Type", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF16(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    /* Node blocks */
    case U3D_BT_GROUPNODE:
		node2 = xmlNewChild(node1, 0, "Group_Node", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF21(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_MODELNODE:
		node2 = xmlNewChild(node1, 0, "Model_Node", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF22(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_LIGHTNODE:
		node2 = xmlNewChild(node1, 0, "Light_Node", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF23(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_VIEWNODE:
		node2 = xmlNewChild(node1, 0, "View_Node", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF24(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    /* Geometry generator blocks */
    case U3D_BT_CLODMESHDECLARATION:
		node2 = xmlNewChild(node1, 0, "CLOD_Mesh_Declaration", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF31(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_CLODMESHCONTINUATION:
		node2 = xmlNewChild(node1, 0, "CLOD_Mesh_Continuation", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF3B(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_CLODMESHPROGRESSIVE:
		node2 = xmlNewChild(node1, 0, "CLOD_Mesh_Progressive", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF3C(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_POINTDECLARATION:
		node2 = xmlNewChild(node1, 0, "Point_Declaration", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF36(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_POINTCONTINUATION:
		node2 = xmlNewChild(node1, 0, "Point_Continuation", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF3E(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_LINEDECLARATION:
		node2 = xmlNewChild(node1, 0, "Line_Declaration", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF37(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_LINECONTINUATION:
		node2 = xmlNewChild(node1, 0, "Line_Continuation", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF3F(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    /* Modifier blocks */
    case U3D_BT_2DGLYPHMODIFIER:
		node2 = xmlNewChild(node1, 0, "Glyph_Modifier_2D", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF41(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_SUBDIVMODIFIER:
		node2 = xmlNewChild(node1, 0, "Subdivision_Modifier", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF42(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_ANIMATIONMODIFIER:
		node2 = xmlNewChild(node1, 0, "Animation_Modifier", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF43(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_BONEWEIGHTMODIFIER:
		node2 = xmlNewChild(node1, 0, "Bone_Weight_Modifier", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF44(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_SHADINGMODIFIER:
		node2 = xmlNewChild(node1, 0, "Shading_Modifier", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF45(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_CLODMODIFIER:
		node2 = xmlNewChild(node1, 0, "CLOD_Modifier", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF46(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    /* Resource blocks */
    case U3D_BT_LIGHTRESOURCE:
		node2 = xmlNewChild(node1, 0, "Light_Resource", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF51(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_VIEWRESOURCE:
		node2 = xmlNewChild(node1, 0, "View_Resource", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF52(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_LITTEXTURESHADER:
		node2 = xmlNewChild(node1, 0, "Lit_Texture_Shader", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF53(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_MATERIALRESOURCE:
		node2 = xmlNewChild(node1, 0, "Material_Resource", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF54(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_TEXTUREDECLARATION:
		node2 = xmlNewChild(node1, 0, "Texture_Declaration", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF55(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_TEXTURECONTINUATION:
		node2 = xmlNewChild(node1, 0, "Texture_Continuation", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF5C(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    case U3D_BT_MOTIONRESOURCE:
		node2 = xmlNewChild(node1, 0, "Motion_Resource", 0);
		u3dcb->curnode		= node2;
		u3dDisposeInfo0xFFFFFF56(u3dcb, position, (pBlock->data).data, 
								 (pBlock->data).size, &shift);
		u3dcb->curnode		= curnode;
        break;
    default:
        /* New object blocks*/
		if(pBlock->type >= 0x00000100 &&
		   pBlock->type <= 0x00FFFFFF) {
			node2 = xmlNewChild(node1, 0, "New_Object", 0);
		} else {
			sprintf(value, "Incorect block type number %lu", pBlock->type);
			xmlNodeAddContent(node1, value);
		} /* if */
		break;
    }
	xmlNodeAddContent(node2, indent[u3dcb->callLevel + 2]);
	xmlNodeAddContent(node1, indent[u3dcb->callLevel + 1]);
	xmlNodeAddContent(node, indent[u3dcb->callLevel + 1]);
	node1 = xmlNewChild(node, 0, "Metadata", 0);
	sprintf(value, "%lu", pBlock->metaData.size);
	xmlNewProp(node1, "size", value);
	sprintf(value, "%lu", pBlock->metaData.padding);
	xmlNewProp(node1, "padding_size", value);
	if(pBlock->metaData.size) {
		U32		size	= pBlock->metaData.size;
		U32 	count 	= 0;
		U32 	index 	= 0;
		U32 	index1 	= 0;
		U32		attributes;
		U16		stringlen;
		U8	    letter;
        
		u3dcb->data = pBlock->metaData.data;
		u3dcb->size = size;
		u3dDecoderReset(u3dcb->u3ddecoder, u3dcb, myMap);
		if(size < sizeof(U32)) {
			return 0;
		} /* if */
		size -= sizeof(U32);
		u3dGetU32(u3dcb->u3ddecoder, &count);
		for(index = 0; index < count; index++) {
			if(size < sizeof(U32)) {
				return 0;
			} /* if */
			size -= sizeof(U32);
			u3dGetU32(u3dcb->u3ddecoder, &attributes);
			xmlNodeAddContent(node1, indent[u3dcb->callLevel + 2]);
			node2 = xmlNewChild(node1, 0, "Key_Value", 0);
			sprintf(value, "0x%X", attributes);
			xmlNewProp(node2, "attributes", value);
			if(size < sizeof(U16)) {
				return 0;
			} /* if */
			size -= sizeof(U16);
			u3dGetU16(u3dcb->u3ddecoder, &stringlen);
			if(size < stringlen) {
				return 0;
			} /* if */
			for(index1 = 0; index1 < stringlen; index1++) {
				u3dGetU8(u3dcb->u3ddecoder, &value[index1]);
			} /* for */
			value[index1] = 0;
			xmlNewProp(node2, "key", value);
			if(attributes&0x1) {
				U32	datasize = 0;
				U32 index2	 = 0;
				// Binary value
				if(size < sizeof(U32)) {
					return 0;
				} /* if */
				size -= sizeof(U32);
				u3dGetU32(u3dcb->u3ddecoder, &datasize);
				if(size < stringlen) {
					return 0;
				} /* if */
				for(index1 = 0; index1 < datasize; index1++) {
					u3dGetU8(u3dcb->u3ddecoder, &letter);
					sprintf(&value[index2], "#x%02X;", letter);
					index2 += 5;              
					if(index2 > 65530) {
						value[index2] = 0;
						xmlNodeAddContent(node2, value);
						index2 = 0;
					} /* */
				} /* for */
				value[index2] = 0;
				xmlNodeAddContent(node2, value);
			} else {
				if(size < sizeof(U16)) {
					return 0;
				} /* if */
				size -= sizeof(U16);
				u3dGetU16(u3dcb->u3ddecoder, &stringlen);
				shift+= sizeof(U16);
				if(size < stringlen) {
					return 0;
				} /* if */
				for(index1 = 0; index1 < stringlen; index1++) {
					u3dGetU8(u3dcb->u3ddecoder, &value[index1]);
				} /* for */
				value[index1] = 0;
				xmlNewProp(node2, "value", value);
			} /* */
		} /* for */

	} /* if */
	xmlNodeAddContent(node1, indent[u3dcb->callLevel + 1]);
	xmlNodeAddContent(node, indent[u3dcb->callLevel]);
 
    return 1;
} /* BlockInfo */

int main( int argC, char* argV[])
{
    U3dParser   *u3dparser;
    U3dDecoder  *u3ddecoder;
    U3dMemory   memfunc = {0, myMalloc, myFree, 0};
    U3dCallBack u3dcb = { 0, 0, 0, 0, 0, 0, 0, 0};
	xmlDocPtr	doc = 0;
	xmlNodePtr	root_node = 0;
    U8          *pBlock = 0;
    U64         Size = 0;

    if(argC < 2) {
        fprintf(stderr, "WARNING: u3d file name requried!\n");
        return -1;
    } /* if */
	{
		xmlDtdPtr	dtd;

		doc = xmlNewDoc("1.0");
		if (doc == 0) {
			fprintf(stderr, "WARNING: can't create XML doc\n");
			return -1;
		} /* if */
		root_node = xmlNewNode(0, "Parse_File");
		if(root_node == 0) {
			fprintf(stderr, "WARNING: can't create XML root block\n");
			return -1;
		}
		xmlNodeAddContent(root_node, indent[1]);
		xmlNodeAddContent(root_node, argV[1]);
		xmlDocSetRootElement(doc, root_node);
		dtd = xmlCreateIntSubset(doc, "Parse_File", 0, "u3d.dtd");
		if(dtd == 0) {
			fprintf(stderr, "WARNING: can't create XML dtd block\n");
			return -1;
		}
	} /* create XML doc */
    {
        FILE *u3dfile;
        U32   readSize = 0;

        u3dfile  = fopen(argV[1],"rb");
        if(u3dfile == 0) {
            fprintf(stderr, "ERROR: Not correct file name!\n");
            return -1;
        } /* if */

        fseek(u3dfile, 0, SEEK_END);
        Size     = ftell(u3dfile);
        fseek(u3dfile, 0, SEEK_SET);
        if(Size == 0) {
            fprintf(stderr, "ERROR: File is empty!\n");
            return -1;
        } /* if */
        pBlock   = (U8*) malloc(Size * sizeof(U8));
        if(pBlock == 0) {
            fprintf(stderr, "ERROR: Not enough memory!\n");
            return -1;
        } /* if */
        readSize = fread(pBlock, sizeof(U8), Size, u3dfile);
        fclose(u3dfile);
    } /* read file */
/*
	fprintf(stdout,"<!DOCTYPE Parse_File SYSTEM \"u3d.dtd\">\n");
    fprintf(stdout,"<Parse_File>\n %s\n", argV[1]);
*/
    u3dParserInit(&u3dparser, &memfunc, 0);
    u3dDecoderInit(&u3ddecoder, &memfunc, &u3dcb, myMap);

    u3dcb.u3dparser     = u3dparser;
    u3dcb.u3ddecoder    = u3ddecoder;
	u3dcb.xmldoc		= doc;
	u3dcb.curnode		= root_node;
	u3dcb.callLevel		= 1;

	u3dParserSetBlocks(u3dparser, BlockInfo);
    u3dParseMemBlock(u3dparser, pBlock, Size, &u3dcb);
/*
    fprintf(stdout,"</Parse_File>\n");
*/
    u3dParserDelete(u3dparser);
    u3dDecoderDelete(u3ddecoder);

	xmlNodeAddContent(root_node, indent[0]);
    xmlInitGlobals();
    xmlKeepBlanksDefault(0);
    xmlSaveFormatFile("-", doc, 1);
	xmlFreeDoc(doc);
	xmlCleanupParser();

    free(pBlock);
    return 1;

} /* main */

