#ifndef PEAKFINDER_H
#define PEAKFINDER_H

#include <iostream>
#include <vector>

class PeakFinder {
public:
    PeakFinder();
    PeakFinder(unsigned int nOfSamples, double peakSlopeThreshold);
    virtual ~PeakFinder();

    void SetNumberOfSample(unsigned int n);
    void SetPeakSlopeThreshold(double threshold);
    void SetNegativePolarity();

    bool Find(double *waveformArray, unsigned int &risingEdge, unsigned int &decayTail, unsigned int startIdx = 0);
    bool FindAll(double *waveformArray, std::vector<unsigned int> &risingEdges);

private:
    unsigned int kNumberOfSamples = 0;
    double       kSlopeThreshold;
    bool         kSlopeThresholdRegistered;
    bool         kPositivePolarity;

    double* kTempSampleArray;

    double LocalDerivative(unsigned int index); // Using 5-point stencil method
    void CopyOver(double *waveformArray);
};

#endif