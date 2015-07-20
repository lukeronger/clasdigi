#ifndef CLAS12_TriggerSupervisor_HH
#define CLAS12_TriggerSupervisor_HH

#include "TObject.h"

#include <iostream>
#include <vector>

namespace clas12 {

   namespace DAQ {

      /**
       *
       */
      class Trigger : public TObject {

         private:
            unsigned int fPreScale;
            unsigned int fRecorded;
            unsigned int fCounted;
            bool         fTriggered;

         public:
            double  fRefTime;

         public:

            Trigger() : fPreScale(1), fRecorded(0), fCounted(0), fTriggered(false), fRefTime(0.0) { } 

            virtual ~Trigger() { }

            bool IsTriggered() const { return fTriggered; }

            ClassDef(Trigger,1)
      };

      /**
       *
       */
      class TriggerSupervisor : public TObject {

         public:

            TriggerSupervisor() { }
            virtual ~TriggerSupervisor() { }

            std::vector<Trigger>  fTriggers;

            ClassDef(TriggerSupervisor,1)
      };

   }
}

#endif

