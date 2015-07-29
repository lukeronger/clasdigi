#ifndef clas12_DAQ_SignalDistribution_H
#define clas12_DAQ_SignalDistribution_H 1

#include "TObject.h"

namespace clas12 {

   namespace DAQ {

      class SignalDistribution : public TObject {

         public: 
            SignalDistribution();
            virtual ~SignalDistribution();

            ClassDef(SignalDistribution,1)
      };

   }

}

#endif

