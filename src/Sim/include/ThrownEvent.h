#ifndef clas12_hits_ThrownEvent_HH
#define clas12_hits_ThrownEvent_HH 1

#include "TObject.h"
#include "Detectors.h"

namespace clas12 {

   namespace sim {

      class ThrownEvent : public TObject {

         public :
            int  fCrate   = 0;
            int  fSlot    = 0;
            int  fChannel = 0;

            int  fTag = 0;
            int  fNum = 0;


            clas12::Detector  fDetector = Detector::NONE;

            ThrownEvent(int ch = 0);
            ThrownEvent(int cr, int sl, int ch);
            virtual ~ThrownEvent();

            virtual void Print(Option_t * opt = "") const;

            ClassDef(ThrownEvent,1)
      };

   }

}

#endif

