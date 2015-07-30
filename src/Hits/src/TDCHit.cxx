#include "TDCHit.h"
#include <iostream>


clas12::hits::TDCHit::TDCHit(int ch, int v, double t) :
   fChannel(ch), fValue(v), fTime(t)
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



