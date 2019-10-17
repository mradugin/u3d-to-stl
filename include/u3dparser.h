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

#ifndef __u3dparser_h__
#define __u3dparser_h__

#include "u3ddefs.h"
#include "u3dfilestr.h"
#include "u3dthreadingdefs.h"
#include "u3dblocktypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct U3dParser U3dParser;

/*
 * U3D Parser function u3dParserInit
 * Purpose
 *      Create an instance of the U3D parser.
 *  Parameters
 *  (out)pCtx - the pointer to the variable which will be initialized with the
 *              pointer to new U3D parser
 *  (in)pMemUtls - the pointer to the user defined memory management service
 *  (in)pThreadUtls - the pointer to the user defined threading service, may be
 *              null if parser should use single-threaded model
 *  Return
 *      u3dStsNoErr if initialization was successful.
 *      u3dStsNullPtrErr if pCtx or pMemUtls are null.
 *      u3dStsBadArgErr if pMemUtls doesn't contain valid pointers to alloc and
 *          free function. See OxlMemory.
 *      u3dStsNoMemErr if system cannot allocate enough memory.
 *  Notes
 *      u3dParserInit is the only way to instantiate the U3D parser, so it must
 *      be the first function in the calling sequence.
 *      u3dParserDelete must be invoked in order to delete each object created by
 *      u3dParserInit function.
 */
U3D_API(U3dStatus, u3dParserInit,(
    U3dParser** pCtx,
    U3dMemory *pMemUtls,
    U3dThreading *pThreadUtls))

/*
 * U3D Parser function u3dParserDelete
 * Purpose
 *      Delete an instance of the U3D parser.
 *  Parameters
 *  (in)pCtx - the pointer to the parser context to be deleted
 *  Return
 *      u3dStsNoErr if the object was successfully deleted.
 *      u3dStsNullPtrErr if pCtx is null.
 */
U3D_API(U3dStatus, u3dParserDelete,(U3dParser* pCtx))

/*----------------------------------------------------------------------------*/
/* Parse functions */


/*
 * U3D Parser functions u3dParseStream
 * Purpose
 *      Parse U3D data passed as U3dInputStream.
 *  Parameters
 *  (in)pCtx - the pointer to the parser context
 *  (in)pStream - the pointer to the user defined input stream
 *  (in)pU3DCallbacksCtx - the pointer to the user defined U3D callbacks
 *             context, this pointer will be passed to each U3D callback
 *             function as a first parameter. 
 *  Return
 *      u3dStsNoErr if parsing was successful.
 *      u3dStsNullPtrErr if pCtx or pStream are null.
 *      u3dStsBadArgErr if pStream contains any invalid pointer.
 *      u3dStsNoMemErr if system cannot allocate enough memory.
 *      u3dStsStoppedByUser if parsing was stopped by user (using parser's callbacks).
 *      
 */
U3D_API(U3dStatus, u3dParseStream,(
        U3dParser* pCtx,
        U3dInputStream *pStream,
        U3d_cbCtx *pU3DCallbacksCtx))

/*
 * U3D Parser functions u3dParseMemBlock
 * Purpose
 *      Parse U3D data passed as a memory block.
 *  Parameters
 *  (in)pCtx - the pointer to the parser context
 *  (in)pBlock - the pointer to the memory block containing U3D data
 *  (in)Size - the size of the block in bytes
 *  (in)pU3DCallbacksCtx - the pointer to the user defined U3D callbacks
 *             context, this pointer will be passed to each U3D callback
 *             function as a first parameter.
 *  Return
 *      u3dStsNoErr if parsing was successful.
 *      u3dStsNullPtrErr if pCtx or pBlock are null.
 *      u3dStsBadArgErr if pStream contains any invalid pointer.
 *      u3dStsNoMemErr if system cannot allocate enough memory.
 *      u3dStsStoppedByUser if parsing was stopped by user (using parser's callbacks).
 */
U3D_API(U3dStatus, u3dParseMemBlock,(
        U3dParser* pCtx,
        const U8 *pBlock,
        U64 Size,
        U3d_cbCtx *pU3DCallbacksCtx))

/*
 * U3D Parser functions u3dModifierChainExpose
 * Purpose
 *      Parse U3D modifier chain block.
 *  Parameters
 *  (in)pCtx - the pointer to the parser context
 *  (in)pModifierChain - the pointer to the Modifier Chain block
 *  (in)Size - the size of the block in bytes
 *  (in)position - the absolut position of pModifierChain block in source of U3D data
 *  (in)pExposeCtx - the pointer to the user defined U3D callbacks
 *             context, this pointer will be passed to each U3D callback
 *             function as a first parameter.
 *  Return
 *      u3dStsNoErr if parsing was successful.
 *      u3dStsNullPtrErr if pCtx or pBlock are null.
 *      u3dStsBadArgErr if pStream contains any invalid pointer.
 *      u3dStsNoMemErr if system cannot allocate enough memory.
 *      u3dStsStoppedByUser if parsing was stopped by user (using parser's callbacks).
 */
U3D_API(U3dStatus, u3dModifierChainExpose,(
        U3dParser* pCtx,
        U3dModifierChain* pModifierChain, 
        U32 Size,
        U32 position,
        U3d_cbCtx *pExposerCtx))

/*
 * U3D Parser group of functions u3dParserSet<event callback>
 * Purpose
 *      Set callbacks for the U3D events.
 *  Parameters
 *  (in)pCtx - the pointer to the parser context
 *  (in)<event callback> - the pointer to the callback function which will be
 *             called when the corresponding event happen.
 *  Return
 *      u3dStsNoErr if operation was successful.
 *      u3dStsNullPtrErr if pCtx is null.
 *  Notes
 *      If the pointer to the callback is null then no function will be called
 *      to handle this event.
 */
U3D_API(U3dStatus, u3dParserSetBlocks,(
    U3dParser* pCtx,
    U3dCb_Block Block))

#ifdef __cplusplus
}
#endif

#endif /*__u3dparser_h__*/
/*End of file u3dparser.h*/
