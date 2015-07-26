#include "TDCHit.h"
#include <iostream>


clas12::hits::TDCHit::TDCHit() : fChannel(0), fValue(0), fTime(0.0)
{ } 
//______________________________________________________________________________

clas12::hits::TDCHit::~TDCHit()
{ } 
//______________________________________________________________________________

void clas12::hits::TDCHit::Print(Option_t * opt) const
{
   std::cout << " TDCHit (" << fChannel << ") : " << fValue << "\n";
} 
//______________________________________________________________________________



