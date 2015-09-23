#include "DAQManager.h"
#include <algorithm>


clas12::DAQ::DAQManager * clas12::DAQ::DAQManager::fInstance = nullptr;
//______________________________________________________________________________

clas12::DAQ::DAQManager* clas12::DAQ::DAQManager::GetManager() {
   if(!fInstance)
   {
      fInstance = new DAQManager();
   }
     //static DAQManager* daq_manager = new DAQManager();
   return (fInstance);
}
//______________________________________________________________________________

int clas12::DAQ::DAQManager::AddCrate(Crate * c)
{
   // Add crate to global list of crates.
   // Returns the crate number if it is added.
   // If the crate already exists in the list, it is not added and the
   // number of the existing crate is returned

   // First check that the crate address not already in list of crates
   auto it  = std::find(fCrates.begin(),fCrates.end(),c);
   int n    = std::distance(fCrates.begin(), it );
   if( it == fCrates.end() ) {
      fCrates.push_back(c);
   }
   return  n;
}
//______________________________________________________________________________

clas12::DAQ::Crate* clas12::DAQ::DAQManager::GetCrate(int i)
{
   if( i <  fCrates.size() ) {
      return fCrates[i];
   }
   return nullptr;
}
//______________________________________________________________________________

