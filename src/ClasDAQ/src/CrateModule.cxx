#include "CrateModule.h"
#include <iostream>

//______________________________________________________________________________

clas12::DAQ::CrateModule::CrateModule(const char * n, const char * t, int id) : 
   TNamed(n,t), fId(id)
{
   fChannels.SetOwner(true);
   SetNChannels(fNChannels);
}
//______________________________________________________________________________

clas12::DAQ::CrateModule::CrateModule(const char * n, int id) : 
   TNamed(n,n), fId(id)
{
   fChannels.SetOwner(true);
   SetNChannels(fNChannels);
}
//______________________________________________________________________________

clas12::DAQ::CrateModule::CrateModule(int id) : 
   CrateModule(Form("CrateModule-%d",id),id)
{
   fChannels.SetOwner(true);
   SetNChannels(fNChannels);
}
//______________________________________________________________________________

clas12::DAQ::CrateModule::~CrateModule()
{ } 
//______________________________________________________________________________
void clas12::DAQ::CrateModule::SetNChannels(int nch)
{
   int N = fChannels.GetEntries();
   if( N < nch ) {
      for( int i = N ; i<nch; i++ ) {
         fChannels.Add( new ModuleChannel(i) ) ;
      }
   } else if( N > nch ) {
      for( int i = N ; i>=nch; i-- ) {
         ModuleChannel * achan = (ModuleChannel*) fChannels.RemoveAt(i) ;
         delete achan;
         achan = 0;
      }
   }
   fNChannels = fChannels.GetEntries();
}
//______________________________________________________________________________
void clas12::DAQ::CrateModule::SetChannel(int ch, ModuleChannel * c) {
   int N = fChannels.GetEntries();
   if(ch >= N) {
      std::cout << "Adding more channels" << std::endl;
      SetNChannels(ch+1);
   }
   ModuleChannel * achan = (ModuleChannel*) fChannels.RemoveAt(ch) ;
   delete achan;
   achan = 0;
   fChannels.AddAt(c,ch);
}
//______________________________________________________________________________

