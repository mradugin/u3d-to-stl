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
#include <stdlib.h>

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
    char		 value[65536];
    U32          shift = 0;

    printf("Block 0x%08X: ", pBlock->type);
    switch(pBlock->type) {
    /* File structure blocks */
    case U3D_BT_FILEHEADER:
        printf("File_Header\n");
        u3dDisposeInfo0x00443355(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
#if 0
    case U3D_BT_FILEREF:
        break;
    case U3D_BT_MODIFIERCHAIN:
        u3dDisposeInfo0xFFFFFF14(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_PRIORITYUPDATE:
        u3dDisposeInfo0xFFFFFF15(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_NEWOBJECTTYPE:
        u3dDisposeInfo0xFFFFFF16(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    /* Node blocks */
    case U3D_BT_GROUPNODE:
        u3dDisposeInfo0xFFFFFF21(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_MODELNODE:
        u3dDisposeInfo0xFFFFFF22(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_LIGHTNODE:
        u3dDisposeInfo0xFFFFFF23(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_VIEWNODE:
        u3dDisposeInfo0xFFFFFF24(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    /* Geometry generator blocks */
    case U3D_BT_CLODMESHDECLARATION:
        u3dDisposeInfo0xFFFFFF31(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
#endif
    case U3D_BT_CLODMESHCONTINUATION:
        printf("CLOD_Mesh_Continuation\n");
        u3dDisposeInfo0xFFFFFF3B(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
#if 0
    case U3D_BT_CLODMESHPROGRESSIVE:
        u3dDisposeInfo0xFFFFFF3C(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_POINTDECLARATION:
        u3dDisposeInfo0xFFFFFF36(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_POINTCONTINUATION:
        u3dDisposeInfo0xFFFFFF3E(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_LINEDECLARATION:
        u3dDisposeInfo0xFFFFFF37(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_LINECONTINUATION:
        u3dDisposeInfo0xFFFFFF3F(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    /* Modifier blocks */
    case U3D_BT_2DGLYPHMODIFIER:
        u3dDisposeInfo0xFFFFFF41(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_SUBDIVMODIFIER:
        u3dDisposeInfo0xFFFFFF42(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_ANIMATIONMODIFIER:
        u3dDisposeInfo0xFFFFFF43(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_BONEWEIGHTMODIFIER:
        u3dDisposeInfo0xFFFFFF44(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_SHADINGMODIFIER:
        u3dDisposeInfo0xFFFFFF45(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_CLODMODIFIER:
        u3dDisposeInfo0xFFFFFF46(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    /* Resource blocks */
    case U3D_BT_LIGHTRESOURCE:
        u3dDisposeInfo0xFFFFFF51(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_VIEWRESOURCE:
        u3dDisposeInfo0xFFFFFF52(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_LITTEXTURESHADER:
        u3dDisposeInfo0xFFFFFF53(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_MATERIALRESOURCE:
        u3dDisposeInfo0xFFFFFF54(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_TEXTUREDECLARATION:
        u3dDisposeInfo0xFFFFFF55(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_TEXTURECONTINUATION:
        u3dDisposeInfo0xFFFFFF5C(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    case U3D_BT_MOTIONRESOURCE:
        u3dDisposeInfo0xFFFFFF56(u3dcb, position, (pBlock->data).data,
                                 (pBlock->data).size, &shift);
        break;
    default:
        /* New object blocks*/
        if(pBlock->type >= 0x00000100 &&
           pBlock->type <= 0x00FFFFFF) {
            // New_Object
        } else {
            // Error: Incorect block type number
        } /* if */
        break;
#else
    default:
        printf("Unknown, skipping\n");
        break;
#endif
    }
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
            // "value" variable contains key name
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
                        // "value" variable contains actual value of the key-value pair
                        index2 = 0;
                    } /* */
                } /* for */
                value[index2] = 0;
                // "value" variable contains actual value of the key-value pair
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
                // "value" variable contains actual value of the key-value pair
            } /* */
        } /* for */
    } /* if */

    return 1;
} /* BlockInfo */

int main( int argC, char* argV[])
{
    U3dParser   *u3dparser;
    U3dDecoder  *u3ddecoder;
    U3dMemory   memfunc = {0, myMalloc, myFree, 0};
    U3dCallBack u3dcb = { 0, 0, 0, 0, 0, 0 };
    U8          *pBlock = 0;
    U64         Size = 0;

    if(argC < 2) {
        printf("U3D to STL file converter\n");
        printf("Converts all occurences of CLOD_Mesh_Continuation (0xFFFFFF3B) blocks\n");
        printf("to STL files, saving each mesh into <u3d_filename>_<u3d_mesh_name>.stl\n");
        printf("Usage: %s <u3d_file>\n", argV[0]);
        fprintf(stderr, "WARNING: u3d file name requried!\n");
        return -1;
    } /* if */
    {
        FILE *u3dfile;
        U32   readSize = 0;

        u3dcb.filename = argV[1];
        u3dfile  = fopen(u3dcb.filename,"rb");
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

    u3dParserInit(&u3dparser, &memfunc, 0);
    u3dDecoderInit(&u3ddecoder, &memfunc, &u3dcb, myMap);

    u3dcb.u3dparser     = u3dparser;
    u3dcb.u3ddecoder    = u3ddecoder;

    u3dParserSetBlocks(u3dparser, BlockInfo);
    u3dParseMemBlock(u3dparser, pBlock, Size, &u3dcb);

    u3dParserDelete(u3dparser);
    u3dDecoderDelete(u3ddecoder);

    free(pBlock);
    return 1;

} /* main */

