#ifndef clas12_sigs_ADCSignal_HH
#define clas12_sigs_ADCSignal_HH 1

#include "TObject.h"

namespace clas12 {

   namespace sigs {

      class ADCSignal : public TObject {

         public :
            int  fChannel;
            int  fValue;

            ADCSignal(int ch = 0, int v = 0);
            virtual ~ADCSignal();

            ClassDef(ADCSignal,1)
      };

   }

}

#endif

