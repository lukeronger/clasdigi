#ifndef clas12_DAQ_TriggerDistribution_H
#define clas12_DAQ_TriggerDistribution_H 1

#include "TObject.h"

namespace clas12 {

   namespace DAQ {

      class TriggerDistribution : public TObject {

         public: 
            TriggerDistribution();
            virtual ~TriggerDistribution();

            ClassDef(TriggerDistribution,1)
      };

   }

}

#endif

