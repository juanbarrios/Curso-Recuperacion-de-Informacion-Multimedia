/*
 * Ver https://github.com/tlacael/MFCC
 * Modificado para usar std::vector en vez de array
 */

/* Header file for Mfcc.cpp. Adapted for C++ by Tlacael Esparza
 * from original libMFCC
*/

/*
 * libmfcc.h - Header for libMFCC
 * Copyright (c) 2010 Jeremy Sawruk
 *
 * This code is released under the MIT License. 
 * For conditions of distribution and use, see the license in LICENSE
 */
#pragma once

#include <vector>

class Mfcc {
    /* params     */
    int samplingRate;
    int numFilters;
    int binSize;
    int numCoeffs;
    std::vector<std::vector<double>> filterParams;
    std::vector<double> normFactors;
    std::vector<double> innerSum;
    /* functions */
    // Compute the normalization 
    double _normalizationFactor(int m);
    // Compute the filter parameter for the specified frequency and filter bands
    double _getFilterParameter(int frequencyBand,
                                int filterBand);
    // Compute the band-dependent magnitude factor for the given filter band
    double _getMagnitudeFactor(int filterBand);
    // Compute the center frequency (fc) of the specified filter band (l)
    double _getCenterFrequency(int filterBand);
public:
    Mfcc();
    ~Mfcc();
    void init(int SamplingRate,
                int NumFilters,
                int BinSize,
                int NumCoeffs);
    // Returns the first m MFCCs
    void getCoefficients(const std::vector<double> &spectralData, std::vector<double> &mfccs);
};
