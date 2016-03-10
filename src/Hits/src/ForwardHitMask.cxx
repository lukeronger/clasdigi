#include "ForwardHitMask.h"
#include <iostream>

//______________________________________________________________________________

clas12::hits::ForwardHitMask::ForwardHitMask() :
   fRunNumber(0), fEventNumber(0)
{ } 
//______________________________________________________________________________

clas12::hits::ForwardHitMask::~ForwardHitMask()
{ } 
//______________________________________________________________________________
void clas12::hits::ForwardHitMask::Clear(Option_t * opt) 
{
   fRunNumber    = 0;
   fEventNumber  = 0;

   fHTCC         = 0;
   fEC           = 0;
   fPC           = 0;
   fDC           = 0;
}
//______________________________________________________________________________

void clas12::hits::ForwardHitMask::Print(Option_t * opt) const
{
   std::cout << "Run   " << fRunNumber << ",  ";
   std::cout << "Event " << fEventNumber << "\n";
   std::cout << "HTCC : " << fHTCC  << std::endl;
   std::cout << "EC   : " << fEC    << std::endl;
   std::cout << "PC   : " << fPC    << std::endl;
   std::cout << "DC   : " << fDC    << std::endl;
}
//______________________________________________________________________________

