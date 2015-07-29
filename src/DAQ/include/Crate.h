#ifndef clas12_DAQ_Crate_HH
#define clas12_DAQ_Crate_HH

#include "TNamed.h"
#include "TList.h"

#include "CrateModule.h"
#include "SignalDistribution.h"
#include "Module.h"
#include <vector>
#include <string>
#include <map>

namespace clas12 {

   namespace DAQ {

      class Crate : public TNamed {

         private:
            int                 fMaxNameSize = 10;
            int                 fMaxSlots    = 18;
            std::map<int,int>   fSlotMap;          // Maps slot (key) to arb vector location

         public:
            int                      fId;
            std::vector<std::string> fModuleNames;
            TList                    fModules;
            SignalDistribution       fSD;

         public:
            Crate(const char * n = "", const char * t = "", int         id = 0 );
            Crate(const char * n, int         id);
            Crate(int         id);
            virtual ~Crate();

            void AddModule(int slot, CrateModule * m) ;
            void AddModule(int slot, Module<TDC> * m) ;

            void Print(Option_t * opt = "");

            ClassDef(Crate,1)
      };

   }

}

#endif

