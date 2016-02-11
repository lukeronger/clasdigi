#include "DriftChamberParticleHit.h"
#include <iostream>
#include "TMath.h"


clas12::hits::DriftChamberParticleHit::DriftChamberParticleHit() : 
   fPDGCode(0), fTrackID(0) { }
//______________________________________________________________________________

clas12::hits::DriftChamberParticleHit::~DriftChamberParticleHit() { }
//______________________________________________________________________________

void clas12::hits::DriftChamberParticleHit::Print() {
   std::cout << " PDG code    : " << fPDGCode    << std::endl;
}
//______________________________________________________________________________

