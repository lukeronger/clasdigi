#ifndef clas12_hits_FlashADCSignal_HH
#define clas12_hits_FlashADCSignal_HH 1

#include "TObject.h"
#include "DigitizedSignal.h"

namespace clas12 {

   namespace sigs {

      class FlashADCSignal : public DigitizedSignal {

         public :
            std::vector<int>  fBuffer;
            int               fIntegral;

         public :
            FlashADCSignal(int ch = 0);
            virtual ~FlashADCSignal();
            
            void PrintBuffer() const;
            virtual void Print(Option_t * opt = "") const;
            virtual void Clear(Option_t * opt = "");

            ClassDef(FlashADCSignal,1)
      };

   }

}

#endif

