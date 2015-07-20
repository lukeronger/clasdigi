#ifndef clas12_DAQ_ADCC_HH
#define clas12_DAQ_ADCC_HH 1

#include "TObject.h"

namespace clas12 {

   namespace DAQ {

      class ADC : public TObject {

         protected :
            int       fPedestal;    // ADC pedestal location

         public : 
            int       fChannel;     // Channel Number
            int       fValue;       // ADC value

            ADC();
            virtual ~ADC();

            void Print(Option_t * opt = "") const ;
            void Clear(Option_t * opt = "");

            int  Pedestal() const   { return fPedestal; } 
            void SetPedestal(int p) { fPedestal = p; } 

            ClassDef(ADC,1)
      };

   }
}

#endif

