#include "ScintChannelHit.h"
#include <iostream>


//______________________________________________________________________________

clas12::hits::ScintChannelHit::ScintChannelHit() :
   fChannel(0), fSteps(0), fEDep(0)
{ }
//______________________________________________________________________________

clas12::hits::ScintChannelHit::~ScintChannelHit() { }
//______________________________________________________________________________

void clas12::hits::ScintChannelHit::Print()
{
   std::cout << "fChannel : " << fChannel    << std::endl;
   std::cout << "fSteps   : " << fSteps    << std::endl;
   std::cout << "fEDep    : " << fEDep    << std::endl;
}
//______________________________________________________________________________

void clas12::hits::ScintChannelHit::Clear(Option_t* opt)
{
   fChannel = 0;
   fSteps   = 0;
   fEDep = 0.0;
}
//______________________________________________________________________________

