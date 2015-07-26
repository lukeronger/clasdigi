#ifndef clas12_DAQ_ADCC_HH
#define clas12_DAQ_ADCC_HH 1

#include "TObject.h"

namespace clas12 {

   namespace DAQ {

      class ADC : public TObject {


         public : 
            int       fChannel;     // Channel Number
            int       fValue;       // ADC value
            int       fPedestal;    // ADC pedestal location

            ADC(int ch = 0, int ped = 100);
            virtual ~ADC();

            void Count(int c = 1);

            void Print(Option_t * opt = "") const ;
            void Clear(Option_t * opt = "");

            int  Pedestal() const   { return fPedestal; } 
            void SetPedestal(int p) { fPedestal = p; } 

            ClassDef(ADC,1)
      };

   }
}

#endif

