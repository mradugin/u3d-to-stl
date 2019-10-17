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

/**
 *      @file u3dparsefile.h  @brief U3D parser API definition
*/

#ifndef __u3dparsefile_h__
#define __u3dparsefile_h__

#include <stdio.h>
#include "u3dparser.h"
#include "u3dbitdecoder.h"
#include "libxml/tree.h"

#ifdef __cplusplus
extern "C" {
#endif

extern char *indent[];

typedef struct {
	xmlDocPtr	 xmldoc;
	xmlNodePtr	 curnode;
    U3dParser*   u3dparser;
    U3dDecoder*  u3ddecoder;
    U8*          data;
    U64          size;
    U32          callLevel;
	U32			 iscompressed;
} U3dCallBack;

U64 myMap(U3dStream_cbCtx* pCtx, U8** pData, U64 size);

U3dStatus u3dDisposeInfo0x00443355(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF12(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF14(U3dCallBack *u3dcb,  U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF15(U3dCallBack *u3dcb,  U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF16(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);

U3dStatus u3dDisposeInfo0xFFFFFF21(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF22(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF23(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF24(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);

U3dStatus u3dDisposeInfo0xFFFFFF31(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF36(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF37(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF3B(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF3C(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF3E(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF3F(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);

U3dStatus u3dDisposeInfo0xFFFFFF41(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF42(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF43(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF44(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF45(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF46(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);

U3dStatus u3dDisposeInfo0xFFFFFF51(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF52(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF53(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF54(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF55(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF56(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);
U3dStatus u3dDisposeInfo0xFFFFFF5C(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData);

#ifdef __cplusplus
}
#endif

#endif /*__u3dparsefile_h__*/
/*End of file u3dparsefile.h*/


