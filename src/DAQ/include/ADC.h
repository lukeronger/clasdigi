#ifndef clas12_DAQ_ADCC_HH
#define clas12_DAQ_ADCC_HH 1

#include "TObject.h"
#include "ModuleChannel.h"

namespace clas12 {

   namespace DAQ {

      class ADC : public ModuleChannel {


         public : 
            int       fValue;       // ADC value
            int       fPedestal;    // ADC pedestal location

            ADC(int ch = 0, int ped = 100);
            virtual ~ADC();

            void Count(int c = 1);

            int    Readout() { return( fPedestal + fValue ); }

            virtual void Reset(Option_t * o = "")  { Clear(o); }
            virtual void Clear(Option_t * opt = "") ;
            virtual void Print(Option_t * opt = "") const ;

            int  Pedestal() const   { return fPedestal; } 
            void SetPedestal(int p) { fPedestal = p; } 

            ClassDef(ADC,1)
      };

   }
}

#endif

