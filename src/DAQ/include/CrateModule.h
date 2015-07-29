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
            
            Discriminator * GetDiscriminator(int i){
               Discriminator * disc = nullptr;
               if(i < fNChannels) {
                  disc = dynamic_cast<Discriminator*>(fChannels.At(i));
               }
               return disc;
            }
            TDC * GetTDC(int i){
               TDC * atdc = nullptr;
               if(i < fNChannels) {
                  atdc = dynamic_cast<TDC*>(fChannels.At(i));
               }
               return atdc;
            }
            ADC * GetADC(int i){
               ADC * aadc = nullptr;
               if(i < fNChannels) {
                  aadc = dynamic_cast<ADC*>(fChannels.At(i));
               }
               return aadc;
            }


            ClassDef(CrateModule,1)
      };

   }

}

#endif
