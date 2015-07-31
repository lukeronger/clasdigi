#ifndef clas12_sim_RunConfiguration_HH
#define clas12_sim_RunConfiguration_HH 1

#include "TNamed.h"

namespace clas12 {

   namespace sim {

      class RunConfiguration : public TNamed {

         public :
            int  fRunNumber;

            RunConfiguration(const char * t = "", const char * n = "", int run = 0);
            RunConfiguration(const char * n, int run);
            RunConfiguration(int run);
            virtual ~RunConfiguration();

            ClassDef(RunConfiguration,1)
      };

   }

}

#endif

