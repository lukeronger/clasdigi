#include "DriftChamberIonPairHit.h"
#include <iostream>

double clas12::hits::P_j_ion_pair(double y, int j, double k) {
   return 2.0*k*TMath::Exp(-2.0*k*y);
}

//______________________________________________________________________________

clas12::hits::DriftChamberIonPairHit::DriftChamberIonPairHit() : StepLength(0.0), PDGCode(0) { }
//______________________________________________________________________________

clas12::hits::DriftChamberIonPairHit::~DriftChamberIonPairHit() { }
//______________________________________________________________________________

void clas12::hits::DriftChamberIonPairHit::Print() {
   std::cout << " Step Length : " << StepLength << std::endl;
   std::cout << " PDG code    : " << PDGCode    << std::endl;
}
//______________________________________________________________________________

