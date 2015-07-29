#ifndef clas12_DAQ_TriggerInterface_H
#define clas12_DAQ_TriggerInterface_H 1

#include "TObject.h"
#include "Crate.h"

namespace clas12 {

   namespace DAQ {

      class TriggerInterface : public TObject {

         public:
            Crate    fCrate;


         public: 
            TriggerInterface();
            virtual ~TriggerInterface();



            ClassDef(TriggerInterface,1)
      };

   }

}

#endif

