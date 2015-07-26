#include "SimpleDriftChamberHit.h"
#include <iostream>

//______________________________________________________________________________

clas12::SimpleDriftChamberHit::SimpleDriftChamberHit() : StepLength(0.0), PDGCode(0) { }
//______________________________________________________________________________

clas12::SimpleDriftChamberHit::~SimpleDriftChamberHit() { }
//______________________________________________________________________________

void clas12::SimpleDriftChamberHit::Print() {
   std::cout << " Step Length : " << StepLength << std::endl;
   std::cout << " PDG code    : " << PDGCode    << std::endl;
}
//______________________________________________________________________________

