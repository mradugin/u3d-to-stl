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
#include <limits.h>

#include "u3dparsefile.h"

#include "stl.h"

F32* ReadF32Array2D(U3dCallBack *u3dcb, U32 width, U32 height)
{

    F32* res = malloc(height * width * sizeof(F32));
    U32 i, j;
    U32 index = 0;
    for (i = 0; i < height; ++i)
    {
        for (j = 0; j < width; ++j)
        {
            U32 temp;
            F32* f = (F32*)&temp;
            u3dGetU32(u3dcb->u3ddecoder, &temp);
            res[index] = *f;
            index++;
        }
    }
    return res;
}

U3dStatus u3dDisposeInfo0xFFFFFF3B(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData)
{
    U32         shift = 0;
    U16			stringlen;
    U32			index;
    char		value[65536];

    U32         chain_index;
    U32         face_count;
    U32         pos_count;
    U32         normal_count;
    U32         diff_color_count;
    U32         spec_color_count;
    U32         tex_coord_count;

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
    for(index = 0; index < stringlen; index++) {
        u3dGetU8(u3dcb->u3ddecoder, &value[index]);
    } /* for */
    value[index] = 0;
    printf("\tname: %s\n", value);

    u3dGetU32(u3dcb->u3ddecoder, &chain_index);
    u3dGetU32(u3dcb->u3ddecoder, &face_count);
    u3dGetU32(u3dcb->u3ddecoder, &pos_count);
    u3dGetU32(u3dcb->u3ddecoder, &normal_count);
    u3dGetU32(u3dcb->u3ddecoder, &diff_color_count);
    u3dGetU32(u3dcb->u3ddecoder, &spec_color_count);
    u3dGetU32(u3dcb->u3ddecoder, &tex_coord_count);
    printf("\tchainIndex: %u\n", chain_index);
    printf("\tfaceCount: %u\n", face_count);
    printf("\tposCount: %u\n", pos_count);
    printf("\tnormalCount: %u\n", normal_count);
    printf("\tdiffColorCount: %u\n", diff_color_count);
    printf("\tspecColorCount: %u\n", spec_color_count);
    printf("\ttexCoordCount: %u\n", tex_coord_count);

    F32* positions = ReadF32Array2D(u3dcb, 3, pos_count);
    F32* normals = ReadF32Array2D(u3dcb, 3, normal_count);
    F32* diff_colors = ReadF32Array2D(u3dcb, 4, diff_color_count);
    F32* spec_colors = ReadF32Array2D(u3dcb, 4, spec_color_count);
    F32* tex_coords = ReadF32Array2D(u3dcb, 4, tex_coord_count);

    Face* faces = malloc(sizeof(Face) * face_count);

    U3DCompCtxID material_ctx;
    u3dDecoderCreateCompCtx(u3dcb->u3ddecoder, &material_ctx);
    for (index = 0; index < face_count; ++index)
    {
        U32 material_id;
        u3dGetDynamicCompressedU32(u3dcb->u3ddecoder, material_ctx, &material_id);
        for (int i = 0; i < 3; ++i)
        {
            U32 pos_index = 0;
            U32 normal_index = 0;
            U32 temp = 0;
            u3dGetStaticCompressedU32(u3dcb->u3ddecoder,
                                       pos_count, &pos_index);
            u3dGetStaticCompressedU32(u3dcb->u3ddecoder,
                                       normal_count, &normal_index);

            if (diff_color_count > 0)
            {
                u3dGetStaticCompressedU32(u3dcb->u3ddecoder,
                                           diff_color_count, &temp);
            }
            if (spec_color_count > 0)
            {
                u3dGetStaticCompressedU32(u3dcb->u3ddecoder,
                                           spec_color_count, &temp);
            }
            if (tex_coord_count > 0)
            {
                // TODO: number of coord count depends on material
                u3dGetStaticCompressedU32(u3dcb->u3ddecoder,
                                           tex_coord_count, &temp);
            }
            for (int j = 0; j < 3; ++j)
            {
                faces[index].corners[i].pos[j] = positions[(pos_index * 3) + j];
                faces[index].corners[i].normal[j] = normals[(normal_index * 3) + j];
            }
        }
    }
    u3dDecoderReleaseCompCtx(u3dcb->u3ddecoder, material_ctx);

    free(positions);
    free(normals);
    free(diff_colors);
    free(spec_colors);
    free(tex_coords);

    char filename[PATH_MAX] = {};

    STL_GetFilename(filename, sizeof(filename), u3dcb->filename, value);
    STL_SaveFacesToFile(faces, face_count, filename, value);

    free(faces);
    return u3dStsNoErr;
} /* u3dDisposeInfo0xFFFFFF3B */
