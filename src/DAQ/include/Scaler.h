#ifndef clas12_DAQ_Scaler_HH
#define clas12_DAQ_Scaler_HH 1

#include "TObject.h"
#include "ModuleChannel.h"

#include <iostream>

namespace clas12 {

   namespace DAQ {

      class Scaler : public ModuleChannel {

         public : 
            int          fCounted;      // A counted quantity (eg photons)

            Scaler(int ch = 0);
            virtual ~Scaler();

            void Count();

            virtual void Clear(Option_t * o = "");
            virtual void Print(Option_t * o = "") const ;

            ClassDef(Scaler,1)
      };

   }
}

#endif

