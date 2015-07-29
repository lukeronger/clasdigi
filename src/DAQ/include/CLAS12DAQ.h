#ifndef clas12_DAQ_CLAS12DAQ_HH
#define clas12_DAQ_CLAS12DAQ_HH

#include "Crate.h"

namespace clas12 {

   namespace DAQ {

      //Crate *   BuildCrate(int slots = 18);

      //Module<TDC>             BuildModule_TDC(int nchan = 16);
      //Module<ADC>             BuildModule_ADC(int nchan = 16);
      //Module<FlashADC>        BuildModule_FlashADC(int nchan = 16);
      //Module<Discriminator>   BuildModule_Discriminator(int nchan = 16);
      
      CrateModule * BuildTDCModule(int nchan = 16);
      CrateModule * BuildADCModule(int nchan = 16);
      CrateModule * BuildFlashADCModule(int nchan = 16);
      CrateModule * BuildDiscriminatorModule(int nchan = 16);

      Crate * BuildCrate();
      Crate * BuildFlashADCCrate();

   }

}

#endif

