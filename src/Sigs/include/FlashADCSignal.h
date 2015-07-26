#ifndef clas12_hits_FlashADCSignal_HH
#define clas12_hits_FlashADCSignal_HH 1

#include "TObject.h"
#include "DigitizedSignal.h"

namespace clas12 {

   namespace hits {

      class FlashADCSignal : public DigitizedSignal {

         public :
            FlashADCSignal(int ch = 0);
            virtual ~FlashADCSignal();

            virtual void Print(Option_t * opt = "") const;

            ClassDef(FlashADCSignal,1)
      };

   }

}

#endif

