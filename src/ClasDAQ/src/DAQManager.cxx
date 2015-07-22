#include "DAQManager.h"

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


