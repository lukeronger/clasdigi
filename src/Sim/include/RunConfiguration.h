#ifndef clas12_sim_RunConfiguration_HH
#define clas12_sim_RunConfiguration_HH 1

#include "TObject.h"

namespace clas12 {

   namespace sim {

      class RunConfiguration : public TObject {

         public :
            int  fChannel;
            int  fValue;

            RunConfiguration(int ch = 0, int v = 0);
            virtual ~RunConfiguration();

            ClassDef(RunConfiguration,1)
      };

   }

}

#endif

