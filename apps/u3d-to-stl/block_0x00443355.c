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

#include "u3dparsefile.h"

U3dStatus u3dDisposeInfo0x00443355(U3dCallBack *u3dcb, U32 position,
                                   U8* pData, U32 size, U32* readData)
{
    U32         shift = 0;
    U16			majorVersion;
    U16			minorVersion;
    U32			profileID;
    U32			declSize;
    U64			fileSize;
    U32			encoding;
    F64			scaling;
    char		value[256];

    u3dcb->data = pData;
    u3dcb->size = size;
    u3dDecoderReset(u3dcb->u3ddecoder, u3dcb, myMap);
    if(size < sizeof(U16)) {
        return u3dStsBadArgErr;
    } /* if */
    size -= sizeof(U16);
    u3dGetU16(u3dcb->u3ddecoder, &majorVersion);
    printf("\tmajorVersion: %d\n", majorVersion);
    pData += sizeof(U16);
    shift += sizeof(U16);

    if(size < sizeof(U16)) {
        return u3dStsBadArgErr;
    } /* if */
    size -= sizeof(U16);
    u3dGetU16(u3dcb->u3ddecoder, &minorVersion);
    printf("\tmajorVersion: %d\n", minorVersion);
    pData += sizeof(U16);
    shift += sizeof(U16);

    if(size < sizeof(U32)) {
        return u3dStsBadArgErr;
    } /* if */
    u3dGetU32(u3dcb->u3ddecoder, &profileID);
    size -= sizeof(U32);
    printf("\tprofileID: 0x%X\n", profileID);
    pData += sizeof(U32);
    shift += sizeof(U32);
    if(!(profileID & 0x4)) {
        u3dcb->iscompressed	= 1;
    } /* if */
    if(size < sizeof(U32)) {
        return u3dStsBadArgErr;
    } /* if */
    size -= sizeof(U32);
    u3dGetU32(u3dcb->u3ddecoder, &declSize);
    printf("\tdeclSize: %u\n", declSize);
    pData += sizeof(U32);
    shift += sizeof(U32);

    if(size < sizeof(U64)) {
        return u3dStsBadArgErr;
    } /* if */
    size -= sizeof(U64);
    u3dGetU64(u3dcb->u3ddecoder, &fileSize);
    printf("\tfileSize: %llu\n", fileSize);
    pData += sizeof(U64);
    shift += sizeof(U64);
    if(size < sizeof(U32)) {
        return u3dStsBadArgErr;
    } /* if */
    size -= sizeof(U32);
    u3dGetU32(u3dcb->u3ddecoder, &encoding);
    printf("\tencoding: %u\n", encoding);
    pData += sizeof(U32);
    shift += sizeof(U32);
    if(profileID & 0x8) {
        if(size < sizeof(U64)) {
            return u3dStsBadArgErr;
        } /* if */
        size -= sizeof(U64);
        u3dGetU64(u3dcb->u3ddecoder, (U64*)&scaling);
        pData += sizeof(U64);
        shift += sizeof(U64);
        printf("\tscaling: %lf\n", scaling);
    } /* if */

    return u3dStsNoErr;
} /* u3dDisposeInfo0x00443355 */

