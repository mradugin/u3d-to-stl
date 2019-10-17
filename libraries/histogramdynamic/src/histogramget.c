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

/*
 * Symbol / Frequency conversion methods
 */
extern const U32 cTableLevel[][4];

/*
 * U3D Histogram function u3dGetSymbolFreq
 * Purpose
 *      Returns the approximate occurence count of this symbol
 *  Parameters
 *  (in)pHistogram - the pointer to the dynamic histogram context
 *  (in)symbol - the symbol for what occurence count will be defined 
 *  (out)freq - the approximate occurence count of this symbol
 *  Return
 *      u3dStsNoErr if approximate occurence count of this symbol was defined
 *      u3dStsNullPtrErr if pHistogram is null.
 *      u3dStsContextMatchErr if pCtx isn't valid
 *      u3dStsBadArgErr if value exceed the maxim value size that was specified
 *      by "type" in u3dHistogramDynamicInit function
 */
U3D_METHOD (U3dStatus, u3dGetSymbolFreq, (
            U3dHistogramDynamic* pHistogram,
            U32 symbol, U32 *freq))
{
    *freq   = 0;
    if(pHistogram == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pHistogram->id != U3DHIST_ID) {
        return u3dStsContextMatchErr;
    } /* if */
    if(symbol > pHistogram->maxValue) {
        return u3dStsDataOverflowErr;
    } /* if */
    
    *freq   = pHistogram->pSymbolFreq[symbol];
    
    return u3dStsNoErr;
} /* u3dGetSymbolFreq */

/*
 * U3D Histogram function u3dGetCumSymbolFreq
 * Purpose
 *      Returns the approximate sum of all symbol freqs for symbols less than 
 *      the given symbol
 *  Parameters
 *  (in)pHistogram - the pointer to the dynamic histogram context
 *  (in)symbol - the symbol for what cumulative freq will be defined 
 *  (out)cumFreq - the approximate cumulative freq for symbols less than 
 *      the given symbol
 *  Return
 *      u3dStsNoErr if approximate occurence count of this symbol was defined
 *      u3dStsNullPtrErr if pHistogram is null.
 *      u3dStsContextMatchErr if pCtx isn't valid
 *      u3dStsBadArgErr if value exceed the maxim value size that was specified
 *      by "type" in u3dHistogramDynamicInit function
 */
U3D_METHOD (U3dStatus, u3dGetCumSymbolFreq, (
            U3dHistogramDynamic* pHistogram,
            U32 symbol, U32 *cumFreq))
{
    *cumFreq = 0;
    if(pHistogram == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pHistogram->id != U3DHIST_ID) {
        return u3dStsContextMatchErr;
    } /* if */
    if(symbol > pHistogram->maxValue) {
        return u3dStsBadArgErr;
    } /* if */
    
    if(symbol > pHistogram->maxAddedValue) {
        *cumFreq = pHistogram->totalSymbols;
    } else if (symbol == 0) {
        *cumFreq = 0;
    } else if (symbol == pHistogram->maxAddedValue) {
        *cumFreq = pHistogram->totalSymbols - pHistogram->pSymbolFreq[symbol];
    } else {
        U32	index;
        U32	cumFreqDef = 0;
		U32	*symbolFreq = pHistogram->pSymbolFreq;			
        
        // start get
        for(index = 0; index < symbol; index++) {
			cumFreqDef	+= symbolFreq[index];
        } /* for */
		*cumFreq = cumFreqDef;
        // end get 
    } /* if */
    
    return u3dStsNoErr;
} /* u3dGetCumSymbolFreq */

/*
 * U3D Histogram function u3dGetCumSymbolFreq
 * Purpose
 *      Returns the approximate occurence count of all symbols
 *  Parameters
 *  (in)pHistogram - the pointer to the dynamic histogram context
 *  (out)total - the approximate occurence count of all symbols
 *  Return
 *      u3dStsNoErr if approximate occurence count of this symbol was defined
 *      u3dStsNullPtrErr if pHistogram is null.
 *      u3dStsContextMatchErr if pCtx isn't valid
 */
U3D_METHOD (U3dStatus, u3dGetTotalSymbolFreq, (
            U3dHistogramDynamic* pHistogram,
            U32 *total))
{
    *total  = 0;
    if(pHistogram == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pHistogram->id != U3DHIST_ID) {
        return u3dStsContextMatchErr;
    } /* if */

    *total  = pHistogram->totalSymbols;
    
    return u3dStsNoErr;
} /* u3dGetTotalSymbolFreq */

/*
 * U3D Histogram function u3dGetSymbolFromFreq
 * Purpose
 *      Return the symbol that corresponds to the given cumulative frequency
 *  Parameters
 *  (in)pHistogram - the pointer to the dynamic histogram context
 *  (in)freq - cumulative frequency
 *  (out)symbol - the symbol that corresponds to the given cumulative frequency
 *  Return
 *      u3dStsNoErr if athe symbol that corresponds to the given cumulative 
 *      frequenc was defined
 *      u3dStsNullPtrErr if pHistogram is null.
 *      u3dStsBadArgErr if freq exceed the total number of symbols that were
 *      added to histogram
 *      u3dStsContextMatchErr if pCtx isn't valid
 */
U3D_METHOD (U3dStatus, u3dGetSymbolFromFreq, (
            U3dHistogramDynamic* pHistogram,
            U32 freq, U32 *symbol))
{
    if(pHistogram == 0) {
        return u3dStsNullPtrErr;
    } /* if */
    if(pHistogram->id != U3DHIST_ID) {
        return u3dStsContextMatchErr;
    } /* if */
    if(freq >= pHistogram->totalSymbols) {
        *symbol = pHistogram->maxAddedValue;
	} else if (pHistogram->maxAddedValue == 0) {
		*symbol = 0;
	} else {
        // define symbol !!!!
        U32	indexEnd = pHistogram->maxAddedValue;
        U32	freq_sum = 0;
        U32	value = 0;
        U32	valuePrev = 0;
		U32	*symbolFreq = pHistogram->pSymbolFreq;			

		for(value = 0; value <= indexEnd; value++) {
			freq_sum	+= symbolFreq[value];
			if(freq_sum > freq) {
				break;
			} /* if */
        } /* for */
        *symbol = value; 
    } /* if */
    
    return u3dStsNoErr;
} /* u3dGetSymbolFromFreq */

int get_U16(unsigned int value, 
            unsigned long* pHist, unsigned long* pCum, unsigned long* pCumShift,
            unsigned long *freq, unsigned long *cumFreq)
{
    unsigned int     maxLevel;
    unsigned int     mask;
    unsigned int     shift;
    unsigned int     invertShift;
    unsigned int     index;
    unsigned int     index1;
    unsigned int     value1;
    unsigned int     level;
    unsigned long    cum;

    // start get
    shift       = 14;
    invertShift = 16;
    mask        = 0xFFFF;
    level       = 0;
    maxLevel    = 7;
//    numIterationI++;
    cum = pCum[value];
    for(index = 0; index < maxLevel; index++) {
             value1 = (value & mask) >> shift;
             for(index1 = 0; index1 < value1; index1++) {
                        cum += pCumShift[level + index1];
//                        numIterationI++;
             } /* for */
             level += (1 + value1) << (invertShift - shift);
             shift -= 2;
             mask >>= 2;
//             numIterationI++;
    } /* for */
    // end get 
    *cumFreq   = cum;
    *freq      = pHist[value];
    return 1;
} /* get_U16 */

int get_U8(unsigned char value, 
            unsigned long* pHist, unsigned long* pCum, unsigned long* pCumShift,
            unsigned long *freq, unsigned long *cumFreq)
{
    unsigned long    cum;
    unsigned long    level;
    unsigned int     value1;
    unsigned int     mask;
    unsigned int     shift;
    unsigned int     index;
    unsigned int     index1;
    
    // start get
    cum = pCum[value];
    shift = 6;
    mask = 0xFF;
    level = 0;
//    numIterationI++;
    for(index = 0; index < 3; index++) {
             value1 = (value & mask) >> shift;
             for(index1 = 0; index1 < value1; index1++) {
                        cum += pCumShift[level + index1];
//                        numIterationI++;
             } /* for */
             level += (1 + value1) << (8 - shift);
             shift -= 2;
             mask >>= 2;
//             numIterationI++;
    } /* for */
    // end get 
    *cumFreq   = cum;
    *freq      = pHist[value];
    return 1;
} /* get_U8 */

/* End of file histogramget.c */
