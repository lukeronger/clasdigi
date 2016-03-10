#include "ParticleHit.h"
#include <iostream>
#include "TMath.h"


clas12::hits::ParticleHit::ParticleHit() : 
   fChannel(0),fPDGCode(0) { }
//______________________________________________________________________________

clas12::hits::ParticleHit::~ParticleHit() { }
//______________________________________________________________________________

void clas12::hits::ParticleHit::Print() {
   std::cout << " channel     : " << fChannel    << std::endl;
   std::cout << " PDG code    : " << fPDGCode    << std::endl;
}
//______________________________________________________________________________

