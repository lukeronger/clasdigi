#ifndef clas12_sigs_TDCSignal_HH
#define clas12_sigs_TDCSignal_HH 1

#include "TObject.h"

namespace clas12 {

   namespace sigs {

      class TDCSignal : public TObject {

         public :
            int     fChannel;
            int     fValue;

            TDCSignal(int ch = 0, int v = 0);
            virtual ~TDCSignal();

            virtual void Print(Option_t * opt = "") const;

            ClassDef(TDCSignal,1)
      };

   }

}

#endif

