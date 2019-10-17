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

#ifndef __encoderctx_h__
#define __encoderctx_h__

#include "u3dbitencoder.h"
#include "u3dhistogram.h"

#ifdef U3D_LOGENCODER
#include <stdio.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
#  define INLINE inline
#  define EXTERNC extern "C"
#  define INTERNC extern "C"
#else
#  define EXTERNC
#  define INTERNC
#  if defined( __GNUC__ ) || defined( __ICC )
#    define INLINE inline
#  elif defined ( _WINDOWS )
#    define INLINE __inline
#  else
#    define INLINE static
#  endif
#endif

#define U3DENCODERCTX_ID   0x0202

#define U3D_METHOD(type,name,arg)         EXTERNC type name arg
#define INT_METHOD(type,name,arg)         INTERNC type name arg

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

struct U3dEncoder {
    U32                 id;
/******** OS Services ********/
    U3dMemory           memUtls;
    U3dStream_cbCtx     *pStreamCtx;
    U3dCb_Write         cbWrite;
/******** Context Data ******/
    U8*                 bitstreamallocated;
    U32                 bitstreamallocatedsize; // in bytes
    U64                 limitSize;
    U8*                 bitstreamposition;
    U8*                 bitstreamlastposition;
    U8                  bitshift;
    U3DCompCtx*         compCtx;
    U32                 compCtxLast; 
    U32                 compCtxAllocatedSize; /**< number of Comp context + 1
                                               * compCtx[0] is reserved for 
                                               * errors state and shouldn't 
                                               * be initialized               */
    U32                 high;                 /**< initialy 0x0000FFFF        */
    U32                 low;                  /**< initialy 0x00000000        */
    U32                 underflowCount;       /**< initially is 0             */
#ifdef U3D_LOGENCODER
	FILE*				logFile;
#endif
};

INT_METHOD(U3dStatus, intEncoderFlush,(U3dEncoder* pCtx));
INT_METHOD(U3dStatus, intAddU8,(U3dEncoder* pCtx, U8 value));
INT_METHOD(U3dStatus, intAddU16,(U3dEncoder* pCtx, U16 value));
INT_METHOD(U3dStatus, intAddCompressedU8 ,(    
    U3dEncoder*     pCtx, 
    U16				range,
    U8              value));


#define ADD_NBITS_TO_STREAM(pCtx, value, size)                              \
    if(pCtx->bitshift == 0) {                                               \
		U8	value_t	= (U8)(value & ~(0xFF<<size));							\
        *pCtx->bitstreamposition = value_t;						            \
        pCtx->bitshift = size;                                              \
        if(pCtx->bitshift == 8) {                                           \
            pCtx->bitshift = 0;                                             \
            if(pCtx->bitstreamposition == pCtx->bitstreamlastposition) {    \
                intEncoderFlush(pCtx);                                      \
			} else {														\
	            pCtx->bitstreamposition++;                                  \
			} /* if */                                                      \
        } /* if */                                                          \
    } else if(pCtx->bitshift + size < 8) {                                  \
		U8	value_t	= (U8)(value & ~(0xFF<<size));							\
        *pCtx->bitstreamposition |= (U8)(value_t << pCtx->bitshift);		\
        pCtx->bitshift           += size;                                   \
    } else if (pCtx->bitshift + size == 8) {                                \
		U8	value_t	= (U8)(value & ~(0xFF<<size));							\
        *pCtx->bitstreamposition |= (U8)(value_t << pCtx->bitshift);		\
        pCtx->bitshift           = 0;                                       \
        if(pCtx->bitstreamposition == pCtx->bitstreamlastposition) {        \
            intEncoderFlush(pCtx);                                          \
		} else {															\
	        pCtx->bitstreamposition++;                                      \
		} /* if */                                                          \
    } else {                                                                \
		U8	value_t	= (U8)(value & ~(0xFF<<size));							\
        *pCtx->bitstreamposition |= (value_t << pCtx->bitshift);	        \
		value_t >>= (8 - pCtx->bitshift);									\
        pCtx->bitshift  = size + pCtx->bitshift - 8;                        \
        if(pCtx->bitstreamposition == pCtx->bitstreamlastposition) {        \
            U8  tempShift   = pCtx->bitshift;                               \
            pCtx->bitshift  = 0;                                            \
            intEncoderFlush(pCtx);                                          \
            pCtx->bitshift  = tempShift;                                    \
        }  else {															\
	        pCtx->bitstreamposition++;                                      \
		} /* if */                                                          \
        *pCtx->bitstreamposition = value_t;									\
    } /* if */


#ifdef __cplusplus
} // extern "C"
#endif

#endif /*__encoderctx_h__*/
/* End of file encoderctx.h */

