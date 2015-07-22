#include "TriggerSupervisor.h"

namespace clas12 {

   namespace DAQ {

      Trigger::Trigger(int ch, int ps) : 
         fChannel(ch), fPreScale(ps), 
         fRecorded(0), fCounted(0),
         fTriggered(false), fRefTime(0.0)
      { } 

      Trigger::~Trigger() { }

      void Trigger::Clear(Option_t *) {
      }

      void Trigger::Print(Option_t *) const {
         std::cout << "Trigger # " << fChannel << std::endl;
         std::cout << "   Prescale  : " << fPreScale << std::endl;
         std::cout << "   Recorded  : " << fRecorded << std::endl;
         std::cout << "   Counted   : " << fCounted << std::endl;
         std::cout << "   Triggered : " << fTriggered << std::endl;
         std::cout << "   Ref. time : " << fRefTime << std::endl;
      }

//______________________________________________________________________________

      void TriggerSupervisor::Print(Option_t *) const {
         for(auto trig : fTriggers) trig.Print();
      }

   }

}

