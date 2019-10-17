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

#ifndef __u3dctx_h__
#define __u3dctx_h__

#include "u3dparser.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#  define INLINE inline
#  define EXTERNC extern "C"
#else
#  define EXTERNC
#  if defined( __GNUC__ ) || defined( __ICC )
#    define INLINE inline
#  elif defined ( _WINDOWS )
#    define INLINE __inline
#  else
#    define INLINE static
#  endif
#endif

#define U3DPCTX_ID   0x0301

#define U3D_METHOD(type,name,arg)         EXTERNC type name arg

struct U3dParser {
    U32             id;
/******** OS Services ********/
    U3dMemory      memUtls;
    U3dThreading   threadUtls;
    U3dInputStream streamUtls;

/******** Users's callbacks ******/
    U3d_cbCtx      *pCbCtx;
    U3dCb_Block    Block;
};


#ifdef __cplusplus
} // extern "C"
#endif

#endif /*__u3dctx_h__*/
/* End of file u3dctx.h */
