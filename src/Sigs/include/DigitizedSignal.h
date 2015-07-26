#ifndef clas12_hits_DigitizedSignal_HH
#define clas12_hits_DigitizedSignal_HH 1

#include "TObject.h"
#include "Detectors.h"

namespace clas12 {

   namespace sigs {

      class DigitizedSignal : public TObject {

         public :
            unsigned int  fTag = 0;
            unsigned int  fNum = 0;

            unsigned int  fCrate   = 0;
            unsigned int  fSlot    = 0;
            unsigned int  fChannel = 0;

            clas12::Detector  fDetector;

            DigitizedSignal(int ch = 0);
            virtual ~DigitizedSignal();

            virtual void Print(Option_t * opt = "") const;

            ClassDef(DigitizedSignal,1)
      };

   }

}

#endif

