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

#include "histogramdynamic.h"

extern const U32 cTableLevel[][4];

/*
 * U3D Histogram function u3dHistogramDynamicAddSymbol
 * Purpose
 *      Add new value in specified dynamic histogram and update requried filed 
 *      in histogram like: SymbolFreq, CumSymbolFreq, TotalSymbolFreq. 
 *      Functions automatically allocate neccessary memory if the context 
 *      wasn't allocated before. 
 *  Parameters
 *  (in)pHistogram - the pointer to the dynamic histogram context
 *  (in)symbol - value to be added to histogram 
 *  Return
 *      u3dStsNoErr if symbol was successful added to histogram.
 *      u3dStsNullPtrErr if pHistogram is null.
 *      u3dStsContextMatchErr if pCtx isn't valid
 *      u3dStsBadArgErr if value exceed the maxim value size that was specified
 *      by "type" in u3dHistogramDynamicInit function
 */
U3D_METHOD (U3dStatus, u3dHistogramDynamicAddSymbol,(
        U3dHistogramDynamic* pHistogram,
        U32 symbol))
{
	U3dStatus	status = u3dStsNoErr;

    if(pHistogram == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pHistogram->id != U3DHIST_ID) {
        return u3dStsContextMatchErr;
    } /* if */
    if(symbol > pHistogram->maxValue) {
        return u3dStsDataOverflowErr;
    } /* if */

    if(pHistogram->totalSymbols == pHistogram->totalNumberLimit) {
        U32     index;
		U32		maxAddValue	= 0;
        
		pHistogram->totalSymbols = 0;
        /* calculate new data */
        for(index = 0; index <= pHistogram->maxAddedValue; index++) {
            pHistogram->pSymbolFreq[index] >>=1;
            if(pHistogram->pSymbolFreq[index]) {
				pHistogram->totalSymbols += pHistogram->pSymbolFreq[index];
				maxAddValue	= index;
            } /* if */
        } /* for */
		pHistogram->maxAddedValue	= maxAddValue;
        pHistogram->pSymbolFreq[0]++;
	    pHistogram->totalSymbols++;
        status = u3dStsDataOverflowErr;
    } /* if */
	if(pHistogram->maxAddedValue < symbol) {
		pHistogram->maxAddedValue	= symbol;
	} /* if */
    pHistogram->totalSymbols++;
    pHistogram->pSymbolFreq[symbol]++;


    return u3dStsNoErr;
} /* u3dHistogramDynamicAddSymbol */

#if 0
int add_U16(unsigned int value, 
            unsigned long* pHist, unsigned long* pCum, unsigned long* pCumShift)
{
    unsigned int     level;
    unsigned int     maxLevel;
    unsigned int     value1;
    unsigned int     mask;
    unsigned int     shift;
    unsigned int     invertShift;
    unsigned int     index;

    // start add
    shift       = 14;
    invertShift = 16;
    mask        = 0xFFFF;
    level       = 0;
    maxLevel    = 7;
    pHist[value]++;
//    numIterationI++;
    for(index = 0; index < maxLevel; index++) {
             value1 = (value & mask) >> shift;
             pCumShift[level + value1]++;
             level += (1 + value1) << (invertShift - shift);
             shift -= 2;
             mask >>= 2;
//             numIterationI++;
    } /* for */
    value1 = (value & mask) >> shift;
    pCumShift[level + value1]++;
    value1 = value >> 2;
    value++;
    for(value1 = (value1 + 1) << 2; value < value1; value++) {
              pCum[value]++;
//              numIterationI++;
    } // for
    // end add           

    return 1;
} /* add_U16*/

int add_U8(unsigned char value, 
            unsigned long* pHist, unsigned long* pCum, unsigned long* pCumShift)
{
    unsigned long    level;
    unsigned int     value1;
    unsigned int     value2 = value;
    unsigned int     mask;
    unsigned int     shift;
    unsigned int     index;

    // start add
    shift = 6;
    mask = 0xFF;
    level = 0;
    pHist[value2]++;
//    numIterationI++;
    for(index = 0; index < 3; index++) {
             value1 = (value2 & mask) >> shift;
             pCumShift[level + value1]++;
             level += (1 + value1) << (8 - shift);
             shift -= 2;
             mask >>= 2;
//             numIterationI++;
    } /* for */
    value1 = (value2 & mask) >> shift;
    pCumShift[level + value1]++;
    value1 = value2 >> 2;
    value2++;
    for(value1 = (value1 + 1) << 2; value2 < value1; value2++) {
              pCum[value2]++;
//              numIterationI++;
    } // for
    // end add           

    return 1;
} /* add_U8 */
#endif

/* End of file histogramadd.c */
