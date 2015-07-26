#ifndef clas12_hits_FlashADCHit_HH
#define clas12_hits_FlashADCHit_HH 1

#include "TObject.h"

namespace clas12 {

   namespace hits {

      class FlashADCHit : public TObject {

         public :
            int     fChannel;
            int     fValue;
            double  fTime;

            FlashADCHit();
            virtual ~FlashADCHit();

            virtual void Print(Option_t * opt = "") const;

            ClassDef(FlashADCHit,1)
      };

   }

}

#endif

