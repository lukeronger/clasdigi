#include "TDC.h"
#include <iostream>

//______________________________________________________________________________
clas12::DAQ::TDC::TDC(int ch, int o) : 
   ModuleChannel(ch), fOffset(o), 
   fRefTime(0.0), fTime(0.0),fValue(0) 
{ }
//______________________________________________________________________________
clas12::DAQ::TDC::~TDC()
{ }
//______________________________________________________________________________
void clas12::DAQ::TDC::Start(double t)
{
   fTime = t;
   //std::cout << "start\n";
}
//______________________________________________________________________________
void clas12::DAQ::TDC::Stop(double t)
{
   fRefTime = t;
   //std::cout << "stop\n";
}
//______________________________________________________________________________
void clas12::DAQ::TDC::AddStartSignal(Discriminator& d)
{
   // Add callback to discriminator 
   // Note that there is no way to remove these 
   // Todo: think of how to do cleanup 
   d.fTriggerCallbacks.push_back( [this](double t){ this->Start(t); } );
}
//______________________________________________________________________________
void clas12::DAQ::TDC::AddStopSignal(Discriminator& d)
{
   // Add callback to discriminator 
   // Note that there is no way to remove these 
   // Todo: think of how to do cleanup 
   d.fTriggerCallbacks.push_back( [this](double t){ this->Stop(t); } );
}
//______________________________________________________________________________
void clas12::DAQ::TDC::Clear(Option_t * )
{
   //std::cout << "Clearing tdc  \n";
   fValue     = 0.0;
   fRefTime   = 0.0;
   fTime      = 0.0;
}
//______________________________________________________________________________
void clas12::DAQ::TDC::Print(Option_t *) const 
{
   std::cout << " TDC (" << fChannel << ") : " << fValue 
      << "offset(" << fOffset <<  "), "
      << "RefTime(" << fRefTime <<  "), "
      << "Time(" << fTime <<  "), "
      << "Res(" << fResolution <<  ")\n";
}
//______________________________________________________________________________
//kjclas12::DAQ::TDC& clas12::DAQ::TDC::operator<<=(Discriminator& rhs);
//______________________________________________________________________________
