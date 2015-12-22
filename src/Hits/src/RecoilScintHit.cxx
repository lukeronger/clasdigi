#include "RecoilScintHit.h"
#include <iostream>


//______________________________________________________________________________

clas12::hits::RecoilScintHit::RecoilScintHit() :
   fChannel(0), fTime(0), fLambda(0), fPDGCode(0)
{ }
//______________________________________________________________________________

clas12::hits::RecoilScintHit::~RecoilScintHit() { }
//______________________________________________________________________________

void clas12::hits::RecoilScintHit::Print()
{
   std::cout << "fChannel : " << fChannel    << std::endl;
   std::cout << "fTime    : " << fTime    << std::endl;
   std::cout << "fPDGCode : " << fPDGCode    << std::endl;
}
//______________________________________________________________________________

