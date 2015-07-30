#include "FlashADCSignal.h"
#include <iostream>
#include <iomanip>


//______________________________________________________________________________

clas12::sigs::FlashADCSignal::FlashADCSignal(int ch) : 
   DigitizedSignal(ch), fIntegral(0.0)
{
} 
//______________________________________________________________________________

clas12::sigs::FlashADCSignal::~FlashADCSignal()
{ } 
//______________________________________________________________________________

void clas12::sigs::FlashADCSignal::Clear(Option_t * opt)
{
   fIntegral = 0.0;
   fBuffer.clear();
} 
//______________________________________________________________________________

void clas12::sigs::FlashADCSignal::PrintBuffer() const
{
   int i = 0;
   for(auto val : fBuffer ) {
      std::cout << std::setw(8) << std::right << val << " ";
      i++;
      if(i%8==0) std::cout << std::endl;
   }
   std::cout << std::endl;
}
//______________________________________________________________________________
void clas12::sigs::FlashADCSignal::Print(Option_t * opt) const
{
   DigitizedSignal::Print(opt);
} 
//______________________________________________________________________________



