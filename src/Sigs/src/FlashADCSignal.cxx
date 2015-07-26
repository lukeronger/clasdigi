#include "FlashADCSignal.h"
#include <iostream>
#include <iomanip>


clas12::sigs::FlashADCSignal::FlashADCSignal(int ch) : DigitizedSignal(ch)
{ } 
//______________________________________________________________________________

clas12::sigs::FlashADCSignal::~FlashADCSignal()
{ } 
//______________________________________________________________________________

void clas12::sigs::FlashADCSignal::Print(Option_t * opt) const
{
   std::cout 
      << "FlashADCSignal"
      << "(ch=" << std::setw(4) << fChannel 
      << ",sl=" << std::setw(4) << fSlot
      << ",cr=" << std::setw(4) << fCrate
      << ") = (" 
      << clas12::ToString(fDetector)
      << ")"
      << "\n";
} 
//______________________________________________________________________________



