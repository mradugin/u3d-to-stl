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

#ifndef __u3dpipeline_h__
#define __u3dpipeline_h__

#include "u3dctx.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef U3D_BIGENDIEN
#define U3D_MAKE_U64(pData) (U64)((pData[0]<<56)|(pData[1]<<48)|\
                                  (pData[2]<<40)|(pData[3]<<32)|\
                                  (pData[4]<<24)|(pData[5]<<16)|\
                                  (pData[6]<<8)|(pData[7]))
#define U3D_MAKE_U32(pData) (U32)((pData[0]<<24)|(pData[1]<<16)|\
                                  (pData[2]<<8)|(pData[3]))
#define U3D_MAKE_U16(pData) (U16)((pData[0]<<8)|(pData[1]))
#define U3D_MAKE_F32(pData) (F32)((pData[0]<<24)|(pData[1]<<16)|\
                                  (pData[2]<<8)|(pData[3]))
#else

#define U3D_MAKE_U64(pData) (U64)((pData[7]<<56)|(pData[6]<<48)|\
                                  (pData[5]<<40)|(pData[4]<<32)|\
                                  (pData[3]<<24)|(pData[2]<<16)|\
                                  (pData[1]<<8)|(pData[0]))
#define U3D_MAKE_U32(pData) (U32)((pData[3]<<24)|(pData[2]<<16)|\
                                  (pData[1]<<8)|(pData[0]))
#define U3D_MAKE_U16(pData) (U16)((pData[1]<<8)|(pData[0]))
#define U3D_MAKE_F32(pData) (F32)((pData[3]<<24)|(pData[2]<<16)|\
                                  (pData[1]<<8)|(pData[0]))
#endif 

#define U3D_InverseQuant(P, S, QPD, IQF) \
                         P + (1 - 2 * S) * QPD * IQF

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*__u3dpipeline_h__*/
/* End of file u3dpipeline.h */
