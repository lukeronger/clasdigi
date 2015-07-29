#ifndef clas12_hits_DigitizedSignal_HH
#define clas12_hits_DigitizedSignal_HH 1

#include "TObject.h"
#include "Detectors.h"

namespace clas12 {

   namespace sigs {

      class DigitizedSignal : public TObject {

         public :
            int  fCrate   = 0;
            int  fSlot    = 0;
            int  fChannel = 0;

            int  fTag = 0;
            int  fNum = 0;


            clas12::Detector  fDetector = Detector::NONE;

            DigitizedSignal(int ch = 0);
            DigitizedSignal(int cr, int sl, int ch);
            virtual ~DigitizedSignal();

            virtual void Print(Option_t * opt = "") const;

            ClassDef(DigitizedSignal,1)
      };

   }

}

#endif

