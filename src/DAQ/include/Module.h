#ifndef clas12_DAQ_Module_HH
#define clas12_DAQ_Module_HH 1

#include <iostream>
#include <vector>
#include "TNamed.h"

#include "Scaler.h"
#include "TDC.h"
#include "ADC.h"
#include "Discriminator.h"
#include "FlashADC.h"

namespace clas12 {

   namespace DAQ {

      template <class T>
      class Module : public TNamed {

         public:
            int             fId        = 0 ;
            int             fNChannels = 18;
            std::vector<T>  fChannels;

         public:
            Module(const char * n = "", const char * t = "", int id = 0 )
               : TNamed(n,t), fId(id)
            {
               SetNChannels(fNChannels);
            }

            Module(const char * n, int id)
               : TNamed(n,n), fId(id)
            {
               SetNChannels(fNChannels);
            }

            Module(int id)
               : Module(Form("Module-%d",id),id)
            {
               SetNChannels(fNChannels);
            }

            virtual ~Module() { }

            void SetNChannels(int nch) {
               fChannels.resize(nch);
               for( int i = 0 ; i<nch; i++ ) {
                  fChannels[i].fChannel = i;
               }
               fNChannels = fChannels.size();
            }

            void SetChannel(int ch, const T& c) {
               if( ch < fNChannels) {
                  fChannels[ch] = c;
               } else {
               std::cout << "Error : " << ch << " is larger than the number of channesl " << fNChannels << std::endl;
               }
            }

            T&  GetChannel(int i) {
               if(i < fNChannels) {
                  return fChannels[i];
               }
               std::cout << "Error : " << i << " is larger than the number of channesl " << fNChannels << std::endl;
               return fChannels[fNChannels-1];
            }

            void Print(Option_t * opt = "") {
               std::cout << " Module ("  
                  << fNChannels << ") : " 
                  << GetName() << "\n";
               //std::cout << " compare " << strcmp(opt,"v") << "\n";
               if( !strcmp(opt,"v") ){
                  for( auto ch : fChannels ) {
                     ch.Print();
                  }
               }
            }

            ClassDef(Module,1)
      };

   }

}

#endif
