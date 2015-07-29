#ifndef clas12_DAQ_DAQManager_HH
#define clas12_DAQ_DAQManager_HH

#include "TObject.h"
#include "TriggerSupervisor.h"
#include "Crate.h"
#include "Discriminator.h"
#include "Scaler.h"
#include "ADC.h"
#include "TDC.h"

#include <vector>
#include <string>
#include <map>

namespace clas12 {

   namespace DAQ {

      class DAQManager : public TObject {

         protected:

            std::vector<Crate*>  fCrates;

         public:
            static DAQManager * GetManager();

            int      AddCrate(Crate * c); 
            Crate *  GetCrate(int n);

            std::vector<Scaler> fScalers;

         private:
            static DAQManager * fInstance;
            DAQManager(){ }

            ClassDef(DAQManager,1)
      };

   }
}


#endif

