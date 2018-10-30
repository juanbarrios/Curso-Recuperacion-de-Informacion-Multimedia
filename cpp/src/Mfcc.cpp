/*
 * Ver https://github.com/tlacael/MFCC
 * Modificado para usar std::vector en vez de array
 */

/*
 * =====================================================================================
 *
 *       Filename:  Mfcc.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/14/2014 15:56:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tlacael Esparza, 
 *           Note:  Code adapted to C++ from libMFCC. see below
 *   Organization:  
 *
 * =====================================================================================
 */

/*
 * libmfcc.c - Code implementation for libMFCC
 * Copyright (c) 2010 Jeremy Sawruk
 *
 * This code is released under the MIT License. 
 * For conditions of distribution and use, see the license in LICENSE
 */

#include "Mfcc.hpp"

#include <algorithm>
#include <cmath>

#define PI 3.14159265358979323846264338327

Mfcc::Mfcc():
    samplingRate(0),
    numFilters(0),
    binSize(0),
    numCoeffs(0){
}

Mfcc::~Mfcc() {
}

void Mfcc::init(int SamplingRate,
                 int NumFilters,
                 int BinSize,
                 int NumCoeffs) {
    samplingRate = SamplingRate;
    numFilters = NumFilters;
    binSize = BinSize;
    numCoeffs = NumCoeffs;

    filterParams.resize(numFilters);
    for (int l=0;l<numFilters;l++){
        filterParams[l].resize(binSize);
    }
    normFactors.resize(numCoeffs);
    innerSum.resize(numFilters);

    // 0 <= m < L
    if(numCoeffs >= numFilters) {
        numCoeffs = numFilters - 1; // force m to good case
    }

   
    for (int i=0; i<numCoeffs; i++) {
        normFactors[i] = _normalizationFactor(i);
    }

    // get filter paramters
    for (int l=0; l < numFilters; l++) {
        for (int k=0; k<binSize-1; k++) {
            filterParams[l][k] = _getFilterParameter(k,l+1);
        }
    }


}


// Returns the first m MFCCs
void Mfcc::getCoefficients(const std::vector<double> &spectralData, std::vector<double> &mfccs) {
	mfccs.resize(numCoeffs);
	std::fill(mfccs.begin(), mfccs.end(), 0);

    for (int l=0;l<numFilters;l++) {
        innerSum[l] = 0.0;
        for (int k=0;k<binSize-1;k++) {
            innerSum[l] += std::fabs(spectralData[k]) * filterParams[l][k];
        }
        for (int m=0;m<numCoeffs;m++) {
            mfccs[m] += innerSum[l] * std::cos(((m*PI) / numFilters)* (l+1-0.5));
            
        }
    }
    for (int m=0;m<numCoeffs;m++) {
        mfccs[m] *= normFactors[m];
    }
}

// Compute the normalization 
double Mfcc::_normalizationFactor(int m) {
    double normalizationFactor = 0.0;
    if(m == 0) {
        normalizationFactor = std::sqrt(1.0 / numFilters);
    }
    else {
        normalizationFactor = std::sqrt(2.0 / numFilters);
    }

    return normalizationFactor;
}

// Compute the filter parameter for the specified frequency and filter bands
double Mfcc::_getFilterParameter(int frequencyBand,
                                int filterBand)    {
    double filterParameter = 0.0;

    double boundary = (frequencyBand * samplingRate) / binSize;// k * Fs / N
    double prevCenterFrequency = _getCenterFrequency(filterBand - 1);// fc(l - 1) etc.
    double thisCenterFrequency = _getCenterFrequency(filterBand);
    double nextCenterFrequency = _getCenterFrequency(filterBand + 1);

    if(boundary >= 0 && boundary < prevCenterFrequency) {
        filterParameter = 0.0;
    }
    else if(boundary >= prevCenterFrequency && boundary < thisCenterFrequency) {
        filterParameter = (boundary - prevCenterFrequency) / 
                        (thisCenterFrequency - prevCenterFrequency);
        filterParameter *= _getMagnitudeFactor(filterBand);
    }
    else if(boundary >= thisCenterFrequency && boundary < nextCenterFrequency) {
        filterParameter = (boundary - nextCenterFrequency) / 
                          (thisCenterFrequency - nextCenterFrequency);
        filterParameter *= _getMagnitudeFactor(filterBand);
    }
    else if(boundary >= nextCenterFrequency && boundary < samplingRate) {
        filterParameter = 0.0;
    }

    return filterParameter;
}
// Compute the band-dependent magnitude factor for the given filter band
double Mfcc::_getMagnitudeFactor(int filterBand) {
    double magnitudeFactor = 0.0;

    if(filterBand >= 1 && filterBand <= 14) {
        magnitudeFactor = 0.015;
    }
    else if(filterBand >= 15 && filterBand <= 48) {
        magnitudeFactor = 2.0 / (_getCenterFrequency(filterBand + 1) - \
                _getCenterFrequency(filterBand -1));
    }

    return magnitudeFactor;
}
// Compute the center frequency (fc) of the specified filter band (l)
double Mfcc::_getCenterFrequency(int filterBand) {
    double centerFrequency = 0.0;
    double exponent;

    if(filterBand == 0){
        centerFrequency = 0;
    }
    else if(filterBand >= 1 && filterBand <= 14){
        centerFrequency = (200.0 * filterBand) / 3.0;
    }
    else {
        exponent = filterBand - 14.0;
        centerFrequency = std::pow(1.0711703, exponent);
        centerFrequency *= 1073.4;
    }
    return centerFrequency;
}


