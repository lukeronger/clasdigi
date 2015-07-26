#include "FlashADCSignal.h"
#include <iostream>


clas12::hits::FlashADCSignal::FlashADCSignal(int ch, int v) : fChannel(ch), fValue(v)
{ } 
//______________________________________________________________________________

clas12::hits::FlashADCSignal::~FlashADCSignal()
{ } 
//______________________________________________________________________________

void clas12::hits::FlashADCSignal::Print(Option_t * opt) const
{
   std::cout << " FlashADCSignal (" << fChannel << ") : " << fValue << "\n";
} 
//______________________________________________________________________________



