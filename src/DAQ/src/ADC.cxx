#include "ADC.h"
#include <iostream>

//______________________________________________________________________________
clas12::DAQ::ADC::ADC(int ch, int ped) : ModuleChannel(ch), fValue(0), fPedestal(ped) 
{ }
//______________________________________________________________________________
clas12::DAQ::ADC::~ADC()
{ }
//______________________________________________________________________________
void clas12::DAQ::ADC::Count(int c)
{
   fValue     += c;
}
//______________________________________________________________________________
void clas12::DAQ::ADC::Clear(Option_t * )
{
   fValue     = 0.0;
}
//______________________________________________________________________________
void clas12::DAQ::ADC::Print(Option_t *) const 
{
   std::cout << " ADC (" << fChannel << ") : " << fValue << " , ped : " << fPedestal <<  "\n";
}
//______________________________________________________________________________