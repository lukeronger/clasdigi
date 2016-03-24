#include "PhotonCounterHit.h"
#include <iostream>


//______________________________________________________________________________

clas12::hits::PhotonCounterHit::PhotonCounterHit() :
   fChannel(0), fCount(0), fTime(0.0), fLambda(0.0),fEnergy(0.0)
{ }
//______________________________________________________________________________

clas12::hits::PhotonCounterHit::~PhotonCounterHit() { }
//______________________________________________________________________________

void clas12::hits::PhotonCounterHit::Print(Option_t *opt)
{
   std::cout << "fChannel : " << fChannel    << std::endl;
   std::cout << "fTime    : " << fTime    << std::endl;
}
//______________________________________________________________________________

