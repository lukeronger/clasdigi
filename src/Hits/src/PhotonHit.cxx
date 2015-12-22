#include "PhotonHit.h"
#include <iostream>


//______________________________________________________________________________

clas12::hits::PhotonHit::PhotonHit() :
   fChannel(0), fTime(0), fLambda(0)
{ }
//______________________________________________________________________________

clas12::hits::PhotonHit::~PhotonHit() { }
//______________________________________________________________________________

void clas12::hits::PhotonHit::Print()
{
   std::cout << "fChannel : " << fChannel    << std::endl;
   std::cout << "fTime    : " << fTime    << std::endl;
}
//______________________________________________________________________________

