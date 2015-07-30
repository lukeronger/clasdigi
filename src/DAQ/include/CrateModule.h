#ifndef clas12_DAQ_CrateModule_HH
#define clas12_DAQ_CrateModule_HH

#include <vector>
#include "TNamed.h"
#include "TList.h"
#include "ModuleChannel.h"
#include "Discriminator.h"
#include "ADC.h"
#include "FlashADC.h"
#include "TDC.h"

namespace clas12 {

   namespace DAQ {

      /** Transition pure virtual class adding virtual methods to be used for
       *  template class Module<T>.
       */
      class CrateModule : public TNamed {

         public:
            int             fNChannels = 18;

         public:
            CrateModule(const char * n = "", const char * t = "", int nch = 0 )
               : TNamed(n,t), fNChannels(nch)
            { }

            CrateModule(const char * n, int nch)
               : TNamed(n,n), fNChannels(nch)
            { }

            CrateModule(int nch)
               : CrateModule(Form("Module-%d",nch),nch)
            { }

            virtual ~CrateModule() { }

            virtual void Clear(Option_t * opt = "") override { }
            virtual void Reset(Option_t * opt = "") { }

            ClassDef(CrateModule,1)
      };

   }

}

#endif
