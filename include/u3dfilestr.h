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

#ifndef __u3dfilestr_h__
#define __u3dfilestr_h__

#include "u3ddefs.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct U3dFileHeader {
   U32              version;
   U32              profileId;
   U32              declSize;
   U64              fileSize;
   U32              charEncoding;
   F64              scalingFactor;
} U3dFileHeader;

typedef struct U3dFileReference {
   U3dString         name;
   U32               attributes;
   U3dBoundSphere*   sphere;
   U3dBoundBox*      box;
   U32               urlCount;
   U3dString*        urlInfo;
   U32               filterCount;
   U8                filterType;
   U3dString*        nameFilter;
   U32*              typeFilter;
   U8                collisionPolicy;
   U3dString         aliasName;
} U3dFileReference;

typedef struct U3dModifierChain {
   U3dString         name;
   U32               type;
   U32               attributes;
   U3dBoundSphere*   sphere;
   U3dBoundBox*      box;
   U3dPadding        padding;
   U32               modifierCount;
   U8*               modifierDeclaration;
} U3dModifierChain;

typedef struct U3dPriorityUpdate {
   U32               priority;
} U3dPriorityUpdate;

typedef struct U3dNewObjectType {
   U3dString         name;
   U32               type;
   U32               extensionIDA;
   U16               extensionIDB;
   U16               extensionIDC;
   U8                extensionIDD0;
   U8                extensionIDD1;
   U8                extensionIDD2;
   U8                extensionIDD3;
   U8                extensionIDD4;
   U8                extensionIDD5;
   U8                extensionIDD6;
   U8                extensionIDD7;
   U32               declarationType;
   U32               continuationCount;
   U32*              continuationType;
   U3dString         vendorName;
   U32               urlCount;
   U3dString*        urlInfo;
   U3dString         information;
} U3dNewObjectType;

typedef struct U3dNewObject {
    U3dString        name;
    U32              chainIndex;
    U8*              data;
} U3dNewObject;

#ifdef __cplusplus
}
#endif

#endif /*__u3dfilestr_h__*/
/*End of file u3dfilestr.h*/

