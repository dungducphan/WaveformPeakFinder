#include "PeakFinder.h"

PeakFinder::PeakFinder() {
    std::cout << "Please set sample size and peak threshold (the rising edge slope threshold)!" << std::endl;
    std::cout << "No default values are assumed." << std::endl;
    kSlopeThresholdRegistered = false;
    kPositivePolarity = true;
}

PeakFinder::PeakFinder(unsigned int nOfSamples, double peakSlopeThreshold) {
    kNumberOfSamples = nOfSamples;
    kTempSampleArray = new double[kNumberOfSamples];
    kSlopeThreshold = peakSlopeThreshold;
    kSlopeThresholdRegistered = true;
    kPositivePolarity = true;
}

PeakFinder::~PeakFinder() = default;

void PeakFinder::SetNumberOfSample(unsigned int n) {
    kNumberOfSamples = n;
    kTempSampleArray = new double[kNumberOfSamples];
}

void PeakFinder::SetPeakSlopeThreshold(double threshold) {
    kSlopeThreshold = threshold;
    kSlopeThresholdRegistered = true;
}

bool PeakFinder::Find(double *waveformArray, unsigned int &risingEdge, unsigned int &decayTail, unsigned int startIdx) {
    bool foundAPeak = false;
    CopyOver(waveformArray);

    for (unsigned int idx = startIdx; idx < kNumberOfSamples; idx++) {
        double firstDerivative = LocalDerivative(idx);
        if (firstDerivative >= kSlopeThreshold) {
            risingEdge = idx;
            foundAPeak = true;
            idx += kNumberOfSamples;
        }
    }

    double amplitudeThresholdTemp = kTempSampleArray[risingEdge];
    for (unsigned int idx = risingEdge; idx < kNumberOfSamples; idx++) {
        if (kTempSampleArray[idx] <= amplitudeThresholdTemp) {
            decayTail = idx;
        }
    }

    if (!foundAPeak) {
        risingEdge = kNumberOfSamples;
        decayTail  = kNumberOfSamples;
    }

    return foundAPeak;
}

double PeakFinder::LocalDerivative(unsigned int idx) {
    if (idx < 2 || idx > kNumberOfSamples - 3) {
        return 0;
    }
    return (8*(kTempSampleArray[idx+1]-kTempSampleArray[idx-1])+kTempSampleArray[idx-2]-kTempSampleArray[idx+2])/12;
}

void PeakFinder::CopyOver(double *waveformArray) {
    double polarityFactor = 1;
    if (!kPositivePolarity) {
        polarityFactor = -1;
    }
    for (unsigned int i = 0; i < kNumberOfSamples; i++) {
        kTempSampleArray[i] = polarityFactor * waveformArray[i];
    }
}

bool PeakFinder::FindAll(double *waveformArray, std::vector<unsigned int> &risingEdges) {
    risingEdges.clear();
    bool findAtLeastOnePeak = false;

    unsigned int risingEdge;
    unsigned int decayTail;
    for (unsigned int idx = 0; idx < kNumberOfSamples; idx++) {
        if (Find(waveformArray, risingEdge, decayTail, idx)) {
            idx = decayTail;
            risingEdges.push_back(risingEdge);
        }
    }

    return findAtLeastOnePeak;
}

void PeakFinder::SetNegativePolarity() {
    kPositivePolarity = false;
}

