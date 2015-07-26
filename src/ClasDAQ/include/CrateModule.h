#ifndef clas12_DAQ_CrateModule_HH
#define clas12_DAQ_CrateModule_HH

#include <vector>
#include "TNamed.h"
#include "TList.h"
#include "ModuleChannel.h"

namespace clas12 {

   namespace DAQ {

      class CrateModule : public TNamed {

         public:
            int    fId        = 0 ;
            int    fNChannels = 12;
            TList  fChannels;

         public:
            CrateModule(const char * n = "", const char * t = "", int         id = 0 );
            CrateModule(const char * n, int         id);
            CrateModule(int         id);
            virtual ~CrateModule();

            void SetNChannels(int nch);
            void SetChannel(int ch, ModuleChannel * c);

            ClassDef(CrateModule,1)
      };

   }

}

#endif
