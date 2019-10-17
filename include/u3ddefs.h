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
 *         @file u3ddefs.h @brief Common types, macros, constants definition
 */

#ifndef __u3ddefs_h__
#define __u3ddefs_h__

#ifdef __cplusplus
extern "C" {
#endif

/* Try to define operating system and hardware platform */
#if defined( _WINDOWS ) || defined( _WIN32 )
  #define U3D_WINDOWS
  #if defined( _PPF ) || defined( _M_IX86 )
    #define U3D_WINDOWS_PPF
    #define U3D_PROCESSOR_PPF
  #elif defined( _EM64T ) || defined( _M_AMD64 )
    #define U3D_WINDOWS_EM64T
    #define U3D_PROCESSOR_EM64T
  #elif defined( _IPF ) || defined( _M_IA64 )
    #define U3D_WINDOWS_IPF
    #define U3D_PROCESSOR_IPF
  #elif defined( _REF)
    #define U3D_WINDOWS_REF
    #define U3D_PROCESSOR_REF
  #else
    #error Hardware platform is not recognized
  #endif
#elif defined( _LINUX ) || defined( __linux__ )
  #define U3D_LINUX
  #if defined( _PPF ) || defined( __i386__ )
    #define U3D_LINUX_PPF
    #define U3D_PROCESSOR_PPF
  #elif defined( _EM64T ) || defined( __x86_64__ )
    #define U3D_LINUX_EM64T
    #define U3D_PROCESSOR_EM64T
  #elif defined( _IPF ) || defined( __ia64__ )
    #define U3D_LINUX_IPF
    #define U3D_PROCESSOR_IPF
  #elif defined( _REF)
    #define U3D_WINDOWS_REF
    #define U3D_PROCESSOR_REF
  #else
    #error Hardware platform is not recognized
  #endif
#else
  #error Operating system is not recognized
#endif

#if defined( U3D_WINDOWS )
  #define U3D_STDCALL  __stdcall
  #define U3D_CDECL    __cdecl
#else
  #define U3D_STDCALL
  #define U3D_CDECL
#endif

#if !defined( U3D_API )
  #define U3D_API( type,name,arg )        extern type U3D_CDECL name arg;
#endif

#if !defined( U3D_VAR )
  #if defined( U3D_WINDOWS )
    #if defined( _MSC_VER ) || defined( __ICL )
      #define U3D_VAR( declaration )  extern __declspec(dllimport) declaration;
    #else
      #define U3D_VAR( declaration )  extern declaration;
    #endif
  #else
    #define   U3D_VAR( declaration )  extern declaration;
  #endif
#endif

#ifndef NULL
  #ifdef __cplusplus
    #define NULL 0
  #else
    #define NULL ((void*)0)
  #endif
#endif

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE (!FALSE)
#endif

#if defined( U3D_WINDOWS )
	#define U3D_INT64    __int64
	#define U3D_UINT64   unsigned __int64
#else
	#define U3D_INT64    long long
	#define U3D_UINT64   unsigned long long
#endif

#define U3D_UNDEF (U32)-1

/**
 * U3dLibraryVersion - @brief todo
 */
typedef struct {
    int  major;             /**< @param Major version (e.g. 1)                */
    int  minor;             /**< Minor version (e.g. 2)                       */
    int  majorBuild;        /**< Major build version (e.g. 3)                 */
    int  build;             /**< Minor build version (e.g. 10,                *
                             *  always >= majorBuild)                         */
    char targetCpu[4];      /**< Corresponding to Intel(R) processor          */
    const char* Name;       /**< Library name (e.g. "u3di32")                 */
    const char* Version;    /**< Library version (e.g. "v1.0 Beta")           */
    const char* BuildDate;  /**< Build data (e.g. "Jan 20 2005")              */
} U3dLibraryVersion;

#ifndef IFXDataTypes_h
typedef unsigned char U8;   /**< @brief 8-bits unsigned integer               */
typedef unsigned int U32;  /**< @brief 32-bits unsigned integer              */
typedef U3D_UINT64 U64;     /**< @brief 64-bits unsigned integer              */
typedef short I16;          /**< @brief 16-bits signed integer                */
typedef int I32;           /**< @brief 32-bits signed integer                */
typedef U3D_INT64 I64;      /**< @brief 64-bits signed integer                */
typedef float F32;          /**< @brief 32-bits float pointer value           */
#endif
typedef unsigned short U16; /**< @brief 16-bits unsigned integer              */
typedef double F64;         /**< @brief 64-bits float pointer value           */

/** 
 *        U3dStatus enumerator defines a status of U3D operations
 *                     negative value means error
*/
typedef enum {
   /* errors */
   u3dStsCpuNotSupportedErr    = -9998, /**< The target cpu is not supported  */
   u3dStsLengthErr             = -127,  /**< Wrong value of length            */

   u3dStsIllegalOpErr          = -12,   /**< Illegal operation                */
   u3dStsBufferOverflowErr     = -11,   /**< Buffer overflow                  */
   u3dStsDataOverflowErr       = -10,   /**< Data overflow                    */
   u3dStsStreamOpenErr         = -9,    /**< Stream opening error             */
   u3dStsNotSupportedErr       = -8,    /**< Requested feature is not         *
                                         * supported                          */
   u3dStsContextMatchErr       = -7,    /**< Context parameter doesn't match  *
                                         * the operation                      */
   u3dStsStreamOpErr           = -6,    /**< Error in the stream's callback   */
   u3dStsNullPtrErr            = -5,    /**< Null pointer error               */
   u3dStsSizeErr               = -4,    /**< Wrong value of data size         */
   u3dStsBadArgErr             = -3,    /**< Function arg/param is bad        */
   u3dStsNoMemErr              = -2,    /**< Not enough memory                */
   u3dStsErr                   = -1,    /**< Unknown/unspecified error        */

   /* no errors */
   u3dStsNoErr                 =  0,    /**< No error, it's OK                */

   /* warnings */
   u3dStsStoppedByUser         =  1,    /**< process was stopped by user      */
   u3dStsReserved1             =  2,
} U3dStatus;

/**
 */

/**
 * @par Memory management callbacks interface
 * @brief context for user defined memory manager
 */
typedef void U3dMem_cbCtx;

/**
 * U3dCb_Alloc @brief callback functions pointers.
 * 
 * @b Purpose \n
 *      Dynamically allocate memory blocks.
 *  @param pCtx (in) pointer to user defined data for a memory manager. This 
 *              is the pointer which is passed to the parser in the 
 *              U3dMemory structure.
 *  @param Size (in) amount of memory in bytes for allocation or reallocation
 * @return
 *      Pointer to allocated memory block.
 *      @retval nonzero if a memory block was successfully allocated.
 *      @retval zero if the function failed to allocate a memory block.
 */
typedef void* (U3D_CDECL *U3dCb_Alloc)(U3dMem_cbCtx *pCtx, U32 Size);

/**
 * U3dCb_Free @brief callback functions pointers.
 * 
 * @b Purpose \n
 *      Free dynamically allocated memory blocks.
 *  @param pCtx (in) pointer to user defined data for a memory manager. This 
 *              is the pointer which is passed to the parser in the 
 *              U3dMemory structure.
 *  @param pBlock (in) pointer to a memory block to be freed or reallocated.
 * @return
 *      U3dCb_Free returns nothing.
 */
typedef void  (U3D_CDECL *U3dCb_Free)(U3dMem_cbCtx *pCtx, void *pBlock);

/**
 * U3dCb_Realloc @brief callback functions pointers.
 * 
 * @b Purpose \n
 *      Dynamically reallocate memory blocks.
 *  @param pCtx (in) pointer to user defined data for a memory manager. This 
 *              is the pointer which is passed to the parser in the 
 *              U3dMemory structure.
 *  @param pBlock (in) pointer to a memory block to be freed or reallocated.
 *  @param Size (in) amount of memory in bytes for allocation or reallocation
 * @return
 *      Pointer to reallocated memory block.
 *      @retval nonzero if a memory block was successfully reallocated.
 *      @retval zero if the function failed to reallocate a memory block.
 */
typedef void* (U3D_CDECL *U3dCb_Realloc)(U3dMem_cbCtx *pCtx, void *pBlock,
                                         U32 Size);

/**
 * U3dMemory @brief memory public structure.
 * 
 * @b Purpose \n
 *      This structure used to pass a user defined memory manager
 *      to the parsers.
 */
typedef struct
{
    U3dMem_cbCtx *pCtx;     /**<Pointer to user defined data. This pointer is 
                               passed as the first parameter in all           
                               U3dMemory callback functions                   */
    U3dCb_Alloc alloc;      /**<Callback function pointer. Must not be NULL   */
    U3dCb_Free  free;       /**<Callback function pointer. Must not be NULL   */
    U3dCb_Realloc realloc;  /**<Callback function pointer. This pointer is    
                               allowed to be NULL. In this case the parsers   
                               use sequential free and alloc calls.           */
} U3dMemory;


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
/**
 * @brief context for user defined stream manager
 */
typedef void U3dStream_cbCtx;

/**
 * U3dCb_Open @brief callback function pointer.
 * 
 * @b Purpose \n
 *      Opens a user defined stream. Will be called once before any other
 *      functions call.
 *  @param pCtx (in) pointer to user defined data for a stream. This is the 
 *              pointer which is passed to the parser in the U3dInputStream 
 *              structures.
 * @return
 *      Result of Open operation
 *      @retval zero if a stream was successfully opened.
 *      @retval nonzero if the function failed to open a stream.
 */
typedef int (U3D_CDECL *U3dCb_Open)(U3dStream_cbCtx *pCtx);

/**
 * U3dCb_Close @brief callback function pointer.
 * 
 * @b Purpose \n
 *      Close a user defined stream. Will be called once after any other
 *      functions call.
 *  @param pCtx (in) pointer to user defined data for a stream. This is the 
 *          pointer which is passed to the parser in the U3dInputStream 
 *          structures.
 * @return
 *      Result of Open operation
 *      @retval zero if a stream was successfully closed.
 *      @retval nonzero if the function failed to close a stream.
 */
typedef int (U3D_CDECL *U3dCb_Close)(U3dStream_cbCtx *pCtx);

/**
 * U3dCb_Write @brief callback function pointer.
 * 
 * @b Purpose \n
 *      The function writes certain amount of data from a memory buffer to
 *      a user defined stream.
 *  @param pCtx (in) pointer to user defined data for a stream. 
 *  @param pData (in) pointer to data that should be written. 
 *  @param size (in) requested amount of data to be written in bytes.
 * @return
 *      Actual size of written data in bytes. If some error happened, return 0.
 * @note
 *      The returned value may be less than or equal to the size value.
 */
typedef U64 (U3D_CDECL *U3dCb_Write)(
    U3dStream_cbCtx *pCtx,
    U8* const pData,
    U64 size);

/**
 * U3dCb_Map @brief callback function pointer.
 * 
 * @b Purpose \n
 *      The function maps certain amount of data from a user defined stream to a
 *      memory buffer and returns pointer to this buffer.
 *  @param pCtx (in) pointer to user defined data for a stream. This is the 
 *         pointer which is passed to the parser in the U3dInputStream 
 *         structure.
 *  @param pMappedData (out) pointer to a variable which must be initialized 
 *         with a mapped data pointer. The mapped data pointer is a property of 
 *         the input stream and must be valid between sequential U3dCb_Map 
 *         calls.
 *  @param size (in) requested amount of bytes to be mapped to @e pMappedData 
 *         array
 * @return
 *      Actual size of mapped data in bytes. If the end of stream was reached,
 *      or some error happened, return value should be 0.
 * @note
 *      It is assumed that the parser should continue to parse the input stream
 *      while the function returns nonzero values.
 *      The amount of mapped data must be less than or equal to @e size bytes 
 *      otherwise all bytes after @e size will be skipped from bitstream 
 *      proccessing
 */
typedef U64 (U3D_CDECL *U3dCb_Map)(
    U3dStream_cbCtx *pCtx,
    U8*             *pMappedData,
    U64             size);

/**
 * U3dCb_Rewind @brief callback function pointer.
 * 
 * @b Purpose \n
 *      This function moves the stream pointer to the location corresponding to
 *      its beginning. The next operation on the stream takes place at the new
 *      location.
 *  @param pCtx (in) pointer to user defined data for a stream. This is the 
 *      pointer which is passed to the parser in the U3dInputStream structure.
 * @return
 *      Status of Rewind operations
 *      @retval zero if rewinding was successfully done.
 *      @retval nonzero if some error happened.
 */
typedef int (U3D_CDECL *U3dCb_Rewind)(U3dStream_cbCtx *pCtx);

/**
 * U3dCb_GetSize @brief callback function pointer.
 * 
 * @b Purpose \n
 *      This function returns the stream size.
 *  @param pCtx (in) pointer to user defined data for a stream. This is the 
 *      pointer which is passed to the parser in the U3dInputStream structure.
 *  @param pSize (out) pointer to the variable representing the stream size.
 * @return
 *      Status of GetSize operations
 *      @retval 0 if operation was successful
 *      @retval nonzero if some error has happened
 */
typedef int (U3D_CDECL *U3dCb_GetSize)(U3dStream_cbCtx *pCtx, U64 *pSize );

/**
 * U3dInputStream @brief stream public structure.
 * 
 * @b Purpose \n
 *      This structure used to pass a user defined input stream to the parsers.
 */
typedef struct U3dInputStream
{
    U3dStream_cbCtx *pCtx;  /**< Pointer to user defined data. This pointer is
                             * passed as the first parameter in all           
                             * U3dInputStream callback functions              */
    U3dCb_Open  open;       /**< Callback function pointer. Must not be NULL  */
    U3dCb_Close close;      /**< Callback function pointer. Must not be NULL  */
    U3dCb_Map   map;        /**< Callback function pointer. Must not be NULL  */
    U3dCb_Rewind rewind;    /**< Callback function pointer. If the stream     
                             * doesn't support rewinding, it must be NULL     */
    U3dCb_GetSize getSize;  /**< Callback function pointer. If the stream size
                             * cannot be obtained, it should be NULL          */
} U3dInputStream;

typedef enum {
    U3D_0   = 0, /**< */
    U3D_1   = 1, /**< */
    U3D_2   = 2, /**< */
    U3D_3   = 3  /**< */
} U3dPadding;

typedef struct U3dString {
    U16               size;
    char*            string;
} U3dString;

typedef struct U3dVector2f {
    F32              p[2];
} U3dVector2f;

typedef struct U3dVector3f {
    F32              p[3];
} U3dVector3f;

typedef struct U3dVector4f {
    F32              p[4];
} U3dVector4f;

typedef struct U3dMatrix4x4f {
    F32              p[16];
} U3dMatrix4x4f;

typedef struct U3dBoundingSphere {
    F32              X;
    F32              Y;
    F32              Z;
    F32              R;
} U3dBoundSphere;

typedef struct U3dBoundBox {
    F32              minX;
    F32              minY;
    F32              minZ;
    F32              maxX;
    F32              maxY;
    F32              maxZ;
} U3dBoundBox;

typedef struct U3dData
{
    U32              size;
    U8*              data;
    U3dPadding       padding;
} U3dData;

typedef struct U3dBlock
{
    U32              type;
    U3dData          data;
    U3dData          metaData;
} U3dBlock;

/**
 *   U3DCompCtxID @brief definition of U3D dynamic compression context ID
*/
typedef U32 U3DCompCtxID;

/******************************************************************************/
/* U3D callbacks                                                              */
/******************************************************************************/

typedef void U3d_cbCtx;

/*----------------------------------------------------------------------------*/
/* Content handler */

/*
 *  U3D callback pointer type - U3dCb_Block
 *  Corresponds to the U3D Block definition
 *  Purpose
 *      Receive notification of block info.
 *  Parameters
 *  (in)pCtx - pointer to user defined data for U3D callback functions. This is
 *             the pointer which is passed to the parser in the functions
 *             u3dParseXXXX.
 *  (in)pChars - the pointer to the characters from the XML document
 *  (in)Length - the number of characters to read from the array
 *  Return
 *      In order to continue parsing, the function must return 0. If parsing
 *      should be stopped the function must return any nonzero value.
 *  Notes
 *      The application must not attempt to read from the array outside of the
 *      specified range.
 */
typedef int (U3D_CDECL *U3dCb_Block)(
	U3d_cbCtx *pCtx,
	const U3dBlock *pBlock,
	const U32 position);

#ifdef __cplusplus
}
#endif

#endif /*__u3ddefs_h__*/
/*End of file u3ddefs.h*/
