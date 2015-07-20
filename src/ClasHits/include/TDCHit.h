#ifndef clas12_hits_TDCHit_HH
#define clas12_hits_TDCHit_HH 1

#include "TObject.h"

namespace clas12 {

   namespace hits {

      class TDCHit : public TObject {

         public :
            int     fChannel;
            int     fValue;
            double  fTime;

            TDCHit();
            virtual ~TDCHit();

            virtual void Print(Option_t * opt = "") const;

            ClassDef(TDCHit,1)
      };

   }

}

#endif

