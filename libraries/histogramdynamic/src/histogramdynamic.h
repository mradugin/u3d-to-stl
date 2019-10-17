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

#ifndef __histogramdynamic_h__
#define __histogramdynamic_h__

#include "u3dhistogram.h"

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

#define U3DHIST_ID   0x0101

#define U3D_METHOD(type,name,arg)         EXTERNC type name arg

struct U3dHistogramDynamic {
    U32             id;
/******** OS Services ********/
    U3dMemory       memUtls;

/******** Context Data ******/
    U32             maxValue;               /* 0xFF or 0xFFFF */
    U32*            pSymbolFreq;            /* 0xFF or 0xFFFF */
    U32*            pCumSymbolFreq;         /* 0xFF or 0xFFFF */
    U32*            pCumSymbolFreqShift;    /* (0x55) 85 or (0x5555)21845
                                             * 85 = 4^1 + 4 ^ 2 + 4 ^3 + 1
                                             * 21845 = 4^1 + ... + 4^7 + 1
                                             */
    U32             totalSymbols;           /* 0 */
    U32             maxAddedValue;          /* the maxim value that was added to
                                             * to histogram 
                                             */
    U32             totalNumberLimit;       /* 0xFFFFFFFF
                                             * limit for totalSymbols, 
                                             * when totalSymbols exceed this 
                                             * value histogram will be split 
                                             * by 2
                                             */
/******** Context Functions' data ******/
    // addValue
    // u3dGetCumSymbolFreq
    U16             maxLevel;
    U16             mask;
    U16             shift;
    U16             invertShift;
};


#ifdef __cplusplus
} // extern "C"
#endif

#endif /*__histogramdynamic_h__*/
/* End of file histogramdynamic.h */

