#include "DigitizedDriftChamberHit.h"
#include <iostream>
#include "TMath.h"


double clas12::DriftChamber::P_j_ion_pair(double y, int j, double k) {
   return 2.0*k*TMath::Exp(-2.0*k*y);
}

//______________________________________________________________________________

clas12::DigitizedDriftChamberHit::DigitizedDriftChamberHit() : StepLength(0.0), PDGCode(0) { }
//______________________________________________________________________________

clas12::DigitizedDriftChamberHit::~DigitizedDriftChamberHit() { }
//______________________________________________________________________________

void clas12::DigitizedDriftChamberHit::Print() {
   std::cout << " Step Length : " << StepLength << std::endl;
   std::cout << " PDG code    : " << PDGCode    << std::endl;
}
//______________________________________________________________________________

