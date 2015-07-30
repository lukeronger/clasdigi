#ifndef clas12_DAQ_Module_HH
#define clas12_DAQ_Module_HH 1

#include <iostream>
#include <vector>
#include <memory>

#include "CrateModule.h"
#include "Scaler.h"
#include "TDC.h"
#include "ADC.h"
#include "Discriminator.h"
#include "FlashADC.h"

namespace clas12 {

   namespace DAQ {

      template <class T>
      class Module : public CrateModule {

         public:
            std::vector<std::shared_ptr<T> >  fChannels;

         public:
            Module(const char * n = "", const char * t = "", int nch = 0 )
               : CrateModule(n,t,nch)
            {
               SetNChannels(fNChannels);
            }

            Module(const char * n, int nch)
               : CrateModule(n,nch)
            {
               SetNChannels(fNChannels);
            }

            Module(int nch) : CrateModule(nch)
            {
               SetNChannels(fNChannels);
            }

            virtual ~Module() { }

            virtual void Reset(Option_t * opt = "") override
            {
               for( auto ch : fChannels ) {
                  ch->Reset(opt);
               }
            }

            virtual void Clear(Option_t * opt = "") override 
            {
               //std::cout << "clearing Module\n";
               for( auto ch : fChannels ) {
                  ch->Clear(opt);
               }
            }


            void SetNChannels(int nch) {
               //fChannels.resize(nch);
               int n0 = fChannels.size();
               for( int i = n0 ; i<nch; i++ ) {
                  //std::shared_ptr<T>  achan = std::make_shared<T>(i);
                  fChannels.push_back( std::make_shared<T>( i ));
                  //fChannels[i]->fChannel = i;
               }
               fNChannels = fChannels.size();
            }

            void SetChannel(int ch, const T& c) {
               if( ch < fNChannels) {
                  fChannels[ch] = std::make_shared(c) ;
               } else {
               std::cout << "Error : " << ch << " is larger than the number of channels " << fNChannels << std::endl;
               }
            }

            T&  GetChannel(int i) {
               if(i < fNChannels) {
                  return *(fChannels[i]);
               }
               std::cout << "Error : " << i << " is larger than the number of channels " << fNChannels << std::endl;
               return *(fChannels[fNChannels-1]);
            }

            void Print(Option_t * opt = "") const  override
            {
               std::cout << " Module ("  
                  << fNChannels << ") : " 
                  << GetName() << "\n";
               std::cout << " compare " << strcmp(opt,"v") << "\n";
               if( !strcmp(opt,"v") ){
                  for( auto ch : fChannels ) {
                     //ch.Dump();
                     ch->Print();
                  }
               }
            }

            ClassDef(Module,1)
      };

   }

}

#endif
