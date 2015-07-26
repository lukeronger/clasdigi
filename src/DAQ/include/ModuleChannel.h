#ifndef clas12_DAQ_ModuleChannel_HH
#define clas12_DAQ_ModuleChannel_HH

#include "TObject.h"
#include <vector>

namespace clas12 {

   namespace DAQ {

      class ModuleChannel : public TObject {

         public:
            int fChannel        = 0 ;

         public:
            ModuleChannel(int id);
            virtual ~ModuleChannel();

            ClassDef(ModuleChannel,1)
      };

   }

}

#endif

