#ifndef clas12_DAQ_TDCC_HH
#define clas12_DAQ_TDCC_HH 1

#include "TObject.h"

namespace clas12 {

   namespace DAQ {

      class TDC : public TObject {

         protected :
            int    fOffset;    // Offset of TDC peak (kind of like pedestal)
            double fRefTime;   // Reference time (eg, trigger)

         public : 
            int    fChannel;   // Channel Number
            int    fValue;     // TDC value

            TDC();
            virtual ~TDC();

            int  Offset() const   { return fOffset; } 
            void SetOffset(int p) { fOffset = p; } 

            void Print(Option_t * opt = "") const;
            void Clear(Option_t * opt = "");

            ClassDef(TDC,1)
      };

   }
}

#endif

