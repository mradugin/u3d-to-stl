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

#ifndef __u3dblocktypes_h__
#define __u3dblocktypes_h__

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
/* /////////////////////////////////////////////////////////////////////////////
//    File structure blocks
//        File Header (blocktype: 0x00443355)
//        File Reference (blocktype: 0xFFFFFF12)
//        Modifier Chain (blocktype: 0xFFFFFF14)
//        Priority Update (blocktype: 0xFFFFFF15)
//        New Object Type(blocktype: 0xFFFFFF16)
//
*/
    U3D_BT_FILEHEADER           = 0x00443355,
    U3D_BT_FILEREF              = 0xFFFFFF12,
    U3D_BT_MODIFIERCHAIN        = 0xFFFFFF14,
    U3D_BT_PRIORITYUPDATE       = 0xFFFFFF15,
    U3D_BT_NEWOBJECTTYPE        = 0xFFFFFF16,

/* /////////////////////////////////////////////////////////////////////////////
//    Node blocks
//        Group Node (blocktype: 0xFFFFFF21)
//        Model Node (blocktype: 0xFFFFFF22)
//        Light Node (blocktype: 0xFFFFFF23)
//        View Node (blocktype: 0xFFFFFF24)
*/
    U3D_BT_GROUPNODE            = 0xFFFFFF21,
    U3D_BT_MODELNODE            = 0xFFFFFF22,
    U3D_BT_LIGHTNODE            = 0xFFFFFF23,
    U3D_BT_VIEWNODE             = 0xFFFFFF24,

/* /////////////////////////////////////////////////////////////////////////////
//    Geometry generator blocks
//        CLOD Mesh Generator (blocktypes: 0xFFFFFF31; 0xFFFFFF3B; 0xFFFFFF3C)
//        Point Set (blocktypes: 0xFFFFFF36; 0xFFFFFF3E)
//        Line Set (blocktypes: 0xFFFFFF37; 0xFFFFFF3F)
*/
    U3D_BT_CLODMESHDECLARATION  = 0xFFFFFF31,
    U3D_BT_CLODMESHCONTINUATION = 0xFFFFFF3B,
    U3D_BT_CLODMESHPROGRESSIVE  = 0xFFFFFF3C,
    U3D_BT_POINTDECLARATION     = 0xFFFFFF36,
    U3D_BT_POINTCONTINUATION    = 0xFFFFFF3E,
    U3D_BT_LINEDECLARATION      = 0xFFFFFF37,
    U3D_BT_LINECONTINUATION     = 0xFFFFFF3F,

/* /////////////////////////////////////////////////////////////////////////////
//    Modifier blocks
//        2D Glyph Modifier (blocktype: 0xFFFFFF41)
//        Subdivision Modifier (blocktype: 0xFFFFFF42)
//        Animation Modifier (blocktype: 0xFFFFFF43)
//        Bone Weight Modifier (blocktype: 0xFFFFFF44)
//        Shading Modifier (blocktype: 0xFFFFFF45)
//        CLOD Modifier (blocktype: 0xFFFFFF46)
*/
    U3D_BT_2DGLYPHMODIFIER      = 0xFFFFFF41,
    U3D_BT_SUBDIVMODIFIER       = 0xFFFFFF42,
    U3D_BT_ANIMATIONMODIFIER    = 0xFFFFFF43,
    U3D_BT_BONEWEIGHTMODIFIER   = 0xFFFFFF44,
    U3D_BT_SHADINGMODIFIER      = 0xFFFFFF45,
    U3D_BT_CLODMODIFIER         = 0xFFFFFF46,

/* /////////////////////////////////////////////////////////////////////////////
//    Resource blocks
//        Light Resource (blocktype: 0xFFFFFF51)
//        View Resource (blocktype: 0xFFFFFF52)
//        Lit Texture Shader (blocktype: 0xFFFFFF53)
//        Material Resource (blocktype: 0xFFFFFF54)
//        Texture Resource (blocktypes: 0xFFFFFF55; 0xFFFFFF5C)
//        Motion Resource (blocktype: 0xFFFFFF56)
*/
    U3D_BT_LIGHTRESOURCE        = 0xFFFFFF51,
    U3D_BT_VIEWRESOURCE         = 0xFFFFFF52,
    U3D_BT_LITTEXTURESHADER     = 0xFFFFFF53,
    U3D_BT_MATERIALRESOURCE     = 0xFFFFFF54,
    U3D_BT_TEXTUREDECLARATION   = 0xFFFFFF55,
    U3D_BT_TEXTURECONTINUATION  = 0xFFFFFF5C,
    U3D_BT_MOTIONRESOURCE       = 0xFFFFFF56
} U3dBlockType;

#ifdef __cplusplus
}
#endif

#endif /*__u3dblocktypes_h__*/
/*End of file u3dblocktypes.h*/
