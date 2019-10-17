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

#ifndef __decoderctx_h__
#define __decoderctx_h__

#include "u3dbitdecoder.h"
#include "u3dhistogram.h"

#ifdef U3D_LOGDECODER
#include <stdio.h>
#endif

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

#define U3DDECODERCTX_ID   0x0201

#define U3D_METHOD(type,name,arg)         EXTERNC type name arg
#define INT_METHOD(type,name,arg)         EXTERNC type name arg

#define NUM_DYNAMIC_COMPCTX     0x0010

#define Hbit                    0x00008000 /**< ‘half’ bit representing 0.5 in 
                                            * the fixed-point 16.16 format (in 
                                            * a 32-bit word this is the17th most
                                            * significant bit)                */
#define Qbit                    0x00004000 /**< ‘quarter’ bit representing 0.25 
                                            * in the fixed-point 16.16 format 
                                            * (in a 32-bit word this is the 
                                            * 18th most significant bit)      */


typedef struct {
    U32                     inuse;      /**< binary flag of usage             */
    U3dHistogramDynamic*    histogram;  /**< = 0 if mode is u3dCompessionStatic
                                         * or allocated by 
                                         * u3dHistogramDynamicInit(), reset by 
                                         * u3dHistogramDynamicReset() and free 
                                         * by u3dHistogramDynamicDelete() if 
                                         * mode is u3dCompessionDynamic       */
} U3DCompCtx;

struct U3dDecoder {
    U32                 id;
/******** OS Services ********/
    U3dMemory           memUtls;
    U3dStream_cbCtx     *pStreamCtx;
    U3dCb_Map           cbMap;
/******** Context Data ******/
    U8*                 bitstreamallocated;
    U64                 bitstreamallocatedsize; //< in bytes
    U8*                 bitstreamposition;
    U8*                 bitstreamlastposition;
    U8                  bitshift;
    U8                  bitstreamTail[8];
    U8                  tailSize;
    U3DCompCtx*         compCtx;
    U32                 compCtxLast; 
    U32                 compCtxAllocatedSize; /**< number of Comp context + 1
                                               * compCtx[0] is reserved for 
                                               * errors state and shouldn't 
                                               * be initialized               */
    U32                 high;                 /**< initialy 0x0000FFFF        */
    U32                 low;                  /**< initialy 0x00000000        */
    U32                 underflowCount;       /**< initially is 0             */
#ifdef U3D_LOGDECODER
    FILE*               logFile;
#endif
};

INT_METHOD(U64, GetStreamData, (U3dDecoder* pCtx));
INT_METHOD(U3dStatus, intGetU8 ,(U3dDecoder* pCtx, U8  *value));
INT_METHOD(U3dStatus, intGetU16 ,(U3dDecoder* pCtx, U16  *value));
INT_METHOD(U3dStatus, intGetCompressedU8 ,(    
    U3dDecoder*     pCtx, 
    U16             range,
    U8              *value));

#define SHIFT_NBITS_IN_STREAM(pCtx, size, rez)                              \
    pCtx->bitshift  += size;                                                \
    if(pCtx->bitshift > 7) {                                                \
        U8  byteshift           = (U8)(pCtx->bitshift >> 3);                \
        pCtx->bitshift          &= 0x7;                                     \
        pCtx->bitstreamposition += byteshift;                               \
        if(pCtx->bitstreamposition >= pCtx->bitstreamlastposition) {        \
            byteshift = (U8)(pCtx->bitstreamposition -                      \
                        pCtx->bitstreamlastposition);                       \
            rez = GetStreamData(pCtx);                                      \
            pCtx->bitstreamposition += byteshift;                           \
        } /* if */                                                          \
    } /* if */

#define READ_8BITS_FROM_STREAM(stream, value, bitshift)                     \
    if(bitshift == 0) {                                                     \
        value = *stream;                                                    \
        stream++;                                                           \
    } else {                                                                \
        value = (U8)((*stream) >> bitshift);                                \
        stream++;                                                           \
        value |= (U8)(*stream << (8 - bitshift));                           \
    } /* if */
    

#define GET_NBITS_FROM_STREAM(pCtx, value, size, rez)                       \
    if(pCtx->bitshift == 0) {                                               \
        value = (U8)(*(pCtx->bitstreamposition) >> (8 - size));             \
        if(size != 8)                                                       \
            pCtx->bitshift += size;                                         \
        else {                                                              \
            pCtx->bitstreamposition++;                                      \
            if(pCtx->bitstreamposition == pCtx->bitstreamlastposition) {    \
                rez = GetStreamData(pCtx);                                  \
            } /* if */                                                      \
        } /* if */                                                          \
    } else if(pCtx->bitshift + size < 8) {                                  \
        value = (U8)(*pCtx->bitstreamposition >> (8-size-pCtx->bitshift));  \
        /* use mask = ~(0xFF << size) to select requried bits */            \
        value   &= (U8)(~(0xFF << size));                                   \
        pCtx->bitshift += size;                                             \
    } else if(pCtx->bitshift == 8 - size) {                                 \
        value = (U8)(*pCtx->bitstreamposition);                             \
        /* use mask = ~(0xFF << size) to select requried bits */            \
        value   &= (U8)(~(0xFF << size));                                   \
        pCtx->bitshift = 0;                                                 \
        pCtx->bitstreamposition++;                                          \
        if(pCtx->bitstreamposition == pCtx->bitstreamlastposition) {        \
            rez = GetStreamData(pCtx);                                      \
        } /* if */                                                          \
    } else {                                                                \
        value = (U8)(*pCtx->bitstreamposition >> pCtx->bitshift);           \
        pCtx->bitshift = size - (8 - pCtx->bitshift);                       \
        pCtx->bitstreamposition++;                                          \
        if(pCtx->bitstreamposition == pCtx->bitstreamlastposition) {        \
            U8  tempShift   = pCtx->bitshift;                               \
            rez = GetStreamData(pCtx);                                      \
            pCtx->bitshift  = tempShift;                                    \
        } /* if */                                                          \
        value |= (U8)(*pCtx->bitstreamposition << (8 - pCtx->bitshift));    \
        value   &= ~(0xFF << size);                                         \
    } /* if */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /*__decoderctx_h__*/
/* End of file decoderctx.h */
