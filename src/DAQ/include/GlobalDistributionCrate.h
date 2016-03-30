#ifndef clas12_DAQ_GloabalDistributionCrate_HH
#define clas12_DAQ_GloabalDistributionCrate_HH

#include "Crate.h"
#include "TList.h"
#include "GloabalDistributionCrateModule.h"
#include <vector>
#include <string>
#include <map>

namespace clas12 {

   namespace DAQ {

      class GloabalDistributionCrate : public Crate {

         private:


         public:
            GloabalDistributionCrate(const char * n = "", const char * t = "", int         id = 0 );
            GloabalDistributionCrate(const char * n, int         id);
            GloabalDistributionCrate(int         id);
            virtual ~GloabalDistributionCrate();

            void AddModule(int slot, GloabalDistributionCrateModule * m) ;

            void Print(Option_t * opt = "") const  ;

            ClassDef(GloabalDistributionCrate,1)
      };

   }

}

#endif
