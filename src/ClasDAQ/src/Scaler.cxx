#include "Scaler.h"
#include <iostream>

//______________________________________________________________________________
clas12::DAQ::Scaler::Scaler(int ch, double thr) : 
   fChannel(ch), fThreshold(thr), fAccumulated(0.0), fCounted(0.0)
{ }
//______________________________________________________________________________
clas12::DAQ::Scaler::~Scaler()
{ }
//______________________________________________________________________________
void clas12::DAQ::Scaler::Clear(Option_t * )
{
   fAccumulated = 0.0;
   fCounted     = 0;
}
//______________________________________________________________________________
void clas12::DAQ::Scaler::Print(Option_t * ) const
{
   std::cout << " Scaler (chan=" << fChannel << ") : " << fThreshold << "\n";
}
//______________________________________________________________________________
