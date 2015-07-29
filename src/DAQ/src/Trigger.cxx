#include "Trigger.h"

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

      void Trigger::Fire(double t) {
         fCounted++;
         if(fCounted%fPreScale == 0)
         {
            fRefTime   = t;
            fTriggered = true;
            fRecorded++;
            std::cout << "Trigger FIRED" << std::endl;
         } 
         for(auto ts : fTSCallbacks) {
            ts(t);
         }
      }

   }

}

