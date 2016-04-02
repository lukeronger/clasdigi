#include "RecoilChamberParticleHit.h"
#include <iostream>
#include "TMath.h"


clas12::hits::RecoilChamberParticleHit::RecoilChamberParticleHit() { }
//______________________________________________________________________________

clas12::hits::RecoilChamberParticleHit::~RecoilChamberParticleHit() { }
//______________________________________________________________________________

void clas12::hits::RecoilChamberParticleHit::Print() {
   std::cout << " channel     : " << fChannel    << std::endl;
   std::cout << " PDG code    : " << fPDGCode    << std::endl;
}
//______________________________________________________________________________

