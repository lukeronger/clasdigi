#ifndef clas12_sim_RunConfiguration_HH
#define clas12_sim_RunConfiguration_HH 1

#include "TNamed.h"
#include "TBrowser.h"
#include <string>
#include <iostream>

namespace clas12 {

   namespace sim {

      class RunConfiguration : public TNamed {

         public:
            int          fRunNumber    = 0;
            int          fNSimulated   = 0;
            double       fBeamEnergy   = 11.0;
            std::string  fInputFileName;
            std::string  fInputTreeName;
            std::string  fOutputFileName;
            std::string  fOutputTreeName;

         public:
            RunConfiguration(const char * n = "", const char * t = "", int run = 0);
            RunConfiguration(const char * n, int run);
            RunConfiguration(int run);
            virtual ~RunConfiguration();

            void Print(std::ostream& s) const ;
            void Print(Option_t * opt = "") const ;

            Bool_t IsFolder() const 
            {
               return kTRUE;
            }

            void Browse(TBrowser* b) 
            {
               //b->Add(&fAsymmetries, "Asymmetries");
               //b->Add(&fApparatus, "Apparatus");
               //b->Add(&fResults, "Results");
               //b->Add(&fDilution, "Dilution");
               //b->Add(&fRunFlags, "Flags");
               //b->Add(&fDetectors, "Detectors");
            }

            ClassDef(RunConfiguration,2)
      };

   }

}

#endif

