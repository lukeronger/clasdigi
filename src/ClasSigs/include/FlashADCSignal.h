#ifndef clas12_hits_FlashADCSignal_HH
#define clas12_hits_FlashADCSignal_HH 1

#include "TObject.h"

namespace clas12 {

   namespace hits {

      class FlashADCSignal : public TObject {

         public :
            unsigned int  fTag = 0;
            unsigned int  fNum = 0;

            unsigned int  fCrate   = 0;
            unsigned int  fSlot    = 0;
            unsigned int  fChannel = 0;

            int     fValue;

            FlashADCSignal(int ch = 0, int v = 0);
            virtual ~FlashADCSignal();

            virtual void Print(Option_t * opt = "") const;

            ClassDef(FlashADCSignal,1)
      };

   }

}

#endif

