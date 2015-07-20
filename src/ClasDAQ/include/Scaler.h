#ifndef clas12_DAQ_Scaler_HH
#define clas12_DAQ_Scaler_HH 1

#include "TObject.h"

namespace clas12 {

   namespace DAQ {

      class Scaler : public TObject {

         public : 
            int          fChannel;      // Channel Number
            double       fThreshold;    // Scaler value

            double       fAccumulated;  // An accumlated quantity
            int          fCounted;      // A counted quantity (eg photons)

            Scaler(int ch = 0, double thr = 1.0);
            virtual ~Scaler();

            virtual void Clear(Option_t * o = "");
            virtual void Print(Option_t * o = "") const ;

            ClassDef(Scaler,1)
      };

   }
}

#endif

