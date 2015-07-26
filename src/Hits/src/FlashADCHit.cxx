#include "FlashADCHit.h"
#include <iostream>


clas12::hits::FlashADCHit::FlashADCHit() : fChannel(0), fValue(0), fTime(0.0)
{ } 
//______________________________________________________________________________

clas12::hits::FlashADCHit::~FlashADCHit()
{ } 
//______________________________________________________________________________

void clas12::hits::FlashADCHit::Print(Option_t * opt) const
{
   std::cout << " FlashADCHit (" << fChannel << ") : " << fValue << "\n";
} 
//______________________________________________________________________________



