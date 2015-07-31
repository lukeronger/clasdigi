#ifndef clas12_sim_RunConfiguration_HH
#define clas12_sim_RunConfiguration_HH 1

#include "TNamed.h"
#include "TBrowser.h"

namespace clas12 {

   namespace sim {

      class RunConfiguration : public TNamed {

         public :
            int  fRunNumber;

            RunConfiguration(const char * t = "", const char * n = "", int run = 0);
            RunConfiguration(const char * n, int run);
            RunConfiguration(int run);
            virtual ~RunConfiguration();

            Bool_t IsFolder() const override
            {
               return kTRUE;
            }

            void Browse(TBrowser* b) override
            {
               //b->Add(&fAsymmetries, "Asymmetries");
               //b->Add(&fApparatus, "Apparatus");
               //b->Add(&fResults, "Results");
               //b->Add(&fDilution, "Dilution");
               //b->Add(&fRunFlags, "Flags");
               //b->Add(&fDetectors, "Detectors");
            }

            ClassDef(RunConfiguration,1)
      };

   }

}

#endif

