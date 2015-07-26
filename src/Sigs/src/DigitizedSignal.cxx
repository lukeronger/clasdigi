#include "DigitizedSignal.h"
#include <iostream>


clas12::sigs::DigitizedSignal::DigitizedSignal(int ch) : fChannel(ch)
{ } 
//______________________________________________________________________________

clas12::sigs::DigitizedSignal::~DigitizedSignal()
{ } 
//______________________________________________________________________________

void clas12::sigs::DigitizedSignal::Print(Option_t * opt) const
{
   std::cout << " DigitizedSignal (" << fChannel << ") : " << "\n";
} 
//______________________________________________________________________________



