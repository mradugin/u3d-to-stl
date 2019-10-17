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

#include "u3dpipeline.h"

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
U3D_METHOD(U3dStatus, u3dParseStream,(
        U3dParser* pCtx,
        U3dInputStream *pStream,
        U3d_cbCtx *pU3DCallbacksCtx)) 
{
    return u3dStsNoErr;
} /* u3dParseStream */

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
U3D_METHOD(U3dStatus, u3dParseMemBlock,(
        U3dParser* pCtx,
        const U8 *pBlock,
        U64 Size,
        U3d_cbCtx *pU3DCallbacksCtx))
{
    U3dBlock block;
    U64      index;
    U32      position;

    if(pCtx == 0 || pBlock == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id !=  U3DPCTX_ID) {
        return u3dStsBadArgErr;
    } /* if */

    for(index = 0; index < Size;) {
        position               = index;
        block.type             = U3D_MAKE_U32((&(pBlock[index])));
        index                  += sizeof(U32);
        block.data.size        = U3D_MAKE_U32((&(pBlock[index])));
        index                  += sizeof(U32);
        block.metaData.size    = U3D_MAKE_U32((&(pBlock[index])));
        block.data.padding     = (0x04 - block.data.size & 0x03) & 0x03;
        block.metaData.padding = (0x04 - block.metaData.size & 0x03) & 0x03;
        index                  += sizeof(U32);
        block.data.data        = (U8*)&pBlock[index];
        index                  += block.data.size + block.data.padding;
        if(block.metaData.size) {
     	    block.metaData.data    = (U8*)&pBlock[index];
            index                  += block.metaData.size + block.metaData.padding;
        } else {
            block.metaData.data    = 0;
        } /* if */

        pCtx->pCbCtx = pU3DCallbacksCtx;
        if(pCtx->Block) {
            pCtx->Block(pCtx->pCbCtx, &block, position);
        } /* if */
    } /* for */
    return u3dStsNoErr;
} /* u3dParseMemBlock */

/*
 * U3D Parser functions u3dModifierChainExpose
 * Purpose
 *      Parse U3D modifier chain block.
 *  Parameters
 *  (in)pCtx - the pointer to the parser context
 *  (in)pModifierChain - the pointer to the Modifier Chain block
 *  (in)Size - the size of the block in bytes
 *  (in)pExposerCtx - the pointer to the user defined U3D callbacks
 *             context, this pointer will be passed to each U3D callback
 *             function as a first parameter.
 *  Return
 *      u3dStsNoErr if parsing was successful.
 *      u3dStsNullPtrErr if pCtx or pBlock are null.
 *      u3dStsBadArgErr if pStream contains any invalid pointer.
 *      u3dStsNoMemErr if system cannot allocate enough memory.
 *      u3dStsStoppedByUser if parsing was stopped by user (using parser's callbacks).
 */
U3D_METHOD(U3dStatus, u3dModifierChainExpose,(
    U3dParser* pCtx,
    U3dModifierChain* pModifierChain, 
    U32 Size,
    U32 position,
    U3d_cbCtx* pExposerCtx))
{
    U3dBlock block;
    U32      index;
    U32      indexM;
    U32      count;
    U8      *pBlock;

    if(pCtx == 0 || pModifierChain == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pCtx->id !=  U3DPCTX_ID) {
        return u3dStsBadArgErr;
    } /* if */

    pBlock   = pModifierChain->modifierDeclaration;
    count    = pModifierChain->modifierCount;
    index    = 0;
    position += sizeof(U3dModifierChain) - sizeof(U8);

    for(indexM = 0; indexM < count; indexM++) {
        position               += index;
        block.type             = U3D_MAKE_U32((&(pBlock[index])));
        index                  += sizeof(U32);
        block.data.size        = U3D_MAKE_U32((&(pBlock[index])));
        index                  += sizeof(U32);
        block.metaData.size    = U3D_MAKE_U32((&(pBlock[index])));
        block.data.padding     = (0x04 - block.data.size & 0x03) & 0x03;
        block.metaData.padding = (0x04 - block.metaData.size & 0x03) & 0x03;
        index                  += sizeof(U32);
        block.data.data        = (U8*)&pBlock[index];
        index                  += block.data.size + block.data.padding;
        if(block.metaData.size) {
     	    block.metaData.data    = (U8*)&pBlock[index];
            index                  += block.metaData.size + block.metaData.padding;
        } else {
            block.metaData.data    = 0;
        } /* if */

        if(pCtx->Block) {
            pCtx->Block(pExposerCtx, &block, position);
        } /* if */
    } /* for */

    return u3dStsNoErr;
} /* u3dModifierChainExpose */

/* End of file u3dpipeline.c */
