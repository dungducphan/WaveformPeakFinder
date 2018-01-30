#include "TROOT.h"
#include "TSystem.h"
#include "../PeakFinder.cpp"

void FindAPeak() {
    gSystem->Load("../libPeakFinder.so");

    double waveform[40];
    for (unsigned int i = 0; i < 40; i++) {
        waveform[i] = 0.;
    }
    for (unsigned int i = 4; i < 7; i++) {
        waveform[i] = -2 * double(i - 3);
    }
    for (unsigned int i = 7; i < 13; i++) {
        waveform[i] = -double(12 - i) / 2;
    }

    std::vector<unsigned int> RisingEdge;

    PeakFinder* myPeakFinder = new PeakFinder(40, 0.5);
    myPeakFinder->SetNegativePolarity();
    myPeakFinder->FindAll(waveform, RisingEdge);

    for (unsigned int i = 0; i < RisingEdge.size(); i++) {
        std::cout << Form("Peak #%i is at ADC #%i", i, RisingEdge.at(i)) << std::endl;
    }
}