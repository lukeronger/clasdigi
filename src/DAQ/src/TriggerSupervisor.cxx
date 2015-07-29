#include "TriggerSupervisor.h"

namespace clas12 {

   namespace DAQ {

      void TriggerSupervisor::Print(Option_t *) const {
         for(auto trig : fTriggers) trig.Print();
      }

   }

}

