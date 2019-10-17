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

#include "u3dctx.h"

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

U3D_METHOD(U3dStatus, u3dParserInit,(
    U3dParser** pCtx,
    U3dMemory *pMemUtls,
    U3dThreading *pThreadUtls))
{
    if(pCtx == 0 || pMemUtls == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pMemUtls->alloc == 0 || pMemUtls->free == 0) {
        return u3dStsBadArgErr;
    } /* if */
    *pCtx = (U3dParser*)pMemUtls->alloc(pMemUtls->pCtx, sizeof(U3dParser));
    if(pCtx == 0) {
        return u3dStsNoMemErr;
    } /* if */

    (*pCtx)->id              = U3DPCTX_ID;

    (*pCtx)->memUtls.pCtx    = pMemUtls->pCtx;
    (*pCtx)->memUtls.alloc   = pMemUtls->alloc;
    (*pCtx)->memUtls.free    = pMemUtls->free;
    (*pCtx)->memUtls.realloc = pMemUtls->realloc;

//    (*pCtx)->threadUtls = PCTX_ID;
//    (*pCtx)->streamUtls = PCTX_ID;

    (*pCtx)->pCbCtx     = 0;
    (*pCtx)->Block      = 0;
    
    return u3dStsNoErr;
} /* u3dParserInit */

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
U3D_METHOD(U3dStatus, u3dParserDelete,(U3dParser* pCtx))
{
    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id !=  U3DPCTX_ID) {
        return u3dStsBadArgErr;
    } /* if */
    pCtx->memUtls.free(pCtx->memUtls.pCtx, pCtx);

    return u3dStsNoErr;
} /* u3dParserDelete */

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
U3D_METHOD(U3dStatus, u3dParserSetBlocks,(
    U3dParser* pCtx,
    U3dCb_Block Block))
{
    if(pCtx == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id !=  U3DPCTX_ID) {
        return u3dStsBadArgErr;
    } /* if */
    pCtx->Block = Block;
 
    return u3dStsNoErr;
} /* u3dParserSetBlocks */


/* End of file u3dctx.c */
