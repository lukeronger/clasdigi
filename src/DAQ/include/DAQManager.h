#ifndef clas12_DAQ_DAQManager_HH
#define clas12_DAQ_DAQManager_HH

#include "TriggerSupervisor.h"
#include "Discriminator.h"
#include "Scaler.h"
#include "ADC.h"
#include "TDC.h"
#include <vector>
#include "TObject.h"
namespace clas12 {

   namespace DAQ {

      class DAQManager : public TObject {
         //DAQManager(DAQManager&) = delete;
         //void operator=(DAQManager&) = delete;

         public:
            static DAQManager * GetManager();

            std::vector<Scaler> fScalers;

         private:
            static DAQManager * fInstance;
            DAQManager(){ }

            ClassDef(DAQManager,1)
      };

   }
}


#endif

