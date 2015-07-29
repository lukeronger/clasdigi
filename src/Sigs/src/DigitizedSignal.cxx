#include "DigitizedSignal.h"
#include <iostream>
#include <iomanip>


clas12::sigs::DigitizedSignal::DigitizedSignal(int ch) : fChannel(ch)
{ } 
//______________________________________________________________________________

clas12::sigs::DigitizedSignal::DigitizedSignal(int cr, int sl, int ch) : 
   fCrate(cr), fSlot(sl), fChannel(ch)
{ } 
//______________________________________________________________________________

clas12::sigs::DigitizedSignal::~DigitizedSignal()
{ } 
//______________________________________________________________________________

void clas12::sigs::DigitizedSignal::Print(Option_t * opt) const
{
   std::cout 
      << "DigitizedSignal"
      << "(ch=" << std::setw(4) << std::left << fChannel 
      << ",sl=" << std::setw(4) << std::left << fSlot
      << ",cr=" << std::setw(4) << std::left << fCrate
      << ") = (" 
      << "tag=" << std::setw(4) << std::left << fTag
      << ",num=" << std::setw(4) << std::left << fNum
      << ", " << clas12::ToString(fDetector)
      << ")"
      << "\n";
} 
//______________________________________________________________________________



