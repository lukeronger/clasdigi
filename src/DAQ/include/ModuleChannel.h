#ifndef clas12_DAQ_ModuleChannel_HH
#define clas12_DAQ_ModuleChannel_HH

#include "TObject.h"
#include <vector>
#include <iostream>

namespace clas12 {

   namespace DAQ {

      class ModuleChannel : public TObject {

         public:
            int fChannel        = 0 ;

         public:
            ModuleChannel(int id);
            virtual ~ModuleChannel();

            virtual void Reset(Option_t * o = ""){ Clear(o); }
            virtual void Clear(Option_t * o = "")  ;
            virtual void Print(Option_t * o = "") const   ;

            ClassDef(ModuleChannel,1)
      };

   }

}

#endif

