#include "TDCSignal.h"
#include <iostream>


clas12::sigs::TDCSignal::TDCSignal(int ch, int v) : fChannel(ch), fValue(v)
{ } 
//______________________________________________________________________________

clas12::sigs::TDCSignal::~TDCSignal()
{ } 
//______________________________________________________________________________

void clas12::sigs::TDCSignal::Print(Option_t * opt) const
{
   std::cout << " TDCSignal (" << fChannel << ") : " << fValue << "\n";
} 
//______________________________________________________________________________



