#include "Scaler.h"
#include <iostream>

//______________________________________________________________________________

clas12::DAQ::Scaler::Scaler(int ch) : 
   ModuleChannel(ch),  fCounted(0)
{ }
//______________________________________________________________________________

clas12::DAQ::Scaler::~Scaler()
{ }
//______________________________________________________________________________

void clas12::DAQ::Scaler::Reset(Option_t * )
{
   fCounted     = 0;
}
//______________________________________________________________________________

void clas12::DAQ::Scaler::Clear(Option_t * )
{ }
//______________________________________________________________________________

void clas12::DAQ::Scaler::Print(Option_t * ) const
{
   std::cout << " Scaler (chan=" << fChannel << ") : " << fCounted << "\n";
}
//______________________________________________________________________________

void clas12::DAQ::Scaler::Count()
{
   //std::cout << "callback\n"; 
   //Print();
   fCounted++;
}
//______________________________________________________________________________

clas12::DAQ::Scaler& clas12::DAQ::Scaler::operator<<(Discriminator& rhs)
{
   rhs.fCallbacks.push_back( [this](){ this->Count(); } );
   return (*this);
}
//______________________________________________________________________________

