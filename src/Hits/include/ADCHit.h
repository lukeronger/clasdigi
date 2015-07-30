#ifndef clas12_hits_ADCHit_HH
#define clas12_hits_ADCHit_HH 1

#include "TObject.h"

namespace clas12 {

   namespace hits {

      class ADCHit : public TObject {

         public :
            int  fChannel;
            int  fValue;

            ADCHit(int ch=0, int v=0);
            virtual ~ADCHit();

            ClassDef(ADCHit,1)
      };

   }

}

#endif

