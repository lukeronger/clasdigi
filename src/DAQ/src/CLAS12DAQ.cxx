#include "CLAS12DAQ.h"
#include "CrateModule.h"
#include "Discriminator.h"
#include "ADC.h"
#include "FlashADC.h"
#include "TDC.h"
#include "Crate.h"

//______________________________________________________________________________


//clas12::DAQ::Crate * clas12::DAQ::BuildCrate(int slots = 18) 
//{
//   Crate * c = new Crate();
//   c->
//}
//______________________________________________________________________________

clas12::DAQ::CrateModule * clas12::DAQ::BuildADCModule(int nchan) {
   CrateModule * m0 = new CrateModule("ADC Module");
   m0->SetNChannels(nchan);
   for(int i = 0; i< nchan; i++) {
      m0->SetChannel(i, new ADC(i));
   }
   return m0;
}
//______________________________________________________________________________

clas12::DAQ::CrateModule * clas12::DAQ::BuildFlashADCModule(int nchan) {
   CrateModule * m0 = new CrateModule("fADC Module");
   m0->SetNChannels(nchan);
   for(int i = 0; i< nchan; i++) {
      m0->SetChannel(i, new FlashADC(i));
   }
   return m0;
}
//______________________________________________________________________________

clas12::DAQ::CrateModule * clas12::DAQ::BuildTDCModule(int nchan) {
   CrateModule * m0 = new CrateModule("TDC Module");
   m0->SetNChannels(nchan);
   for(int i = 0; i< nchan; i++) {
      m0->SetChannel(i, new TDC(i));
   }
   return m0;
}
//______________________________________________________________________________

clas12::DAQ::CrateModule * clas12::DAQ::BuildDiscriminatorModule(int nchan) {
   CrateModule * m0 = new CrateModule("Disc. Module");
   m0->SetNChannels(nchan);
   for(int i = 0; i< nchan; i++) {
      m0->SetChannel(i, new Discriminator(i));
   }
   return m0;
}
//______________________________________________________________________________

clas12::DAQ::Crate * clas12::DAQ::BuildCrate() {

   Crate * crate    = new Crate();
   int slot = 0;

   Module<TDC>           * tdc_module       = 0;
   Module<Discriminator> * disc_module      = 0;
   Module<Discriminator> * trig_disc_module = 0;

   crate->AddCrateModule( slot = 0, disc_module = new Module<Discriminator>("Disc. Module",50) );
   crate->AddCrateModule( slot = 1, tdc_module = new Module<TDC>("TDC Module",50));
   crate->AddCrateModule( slot = 2, new Module<Scaler>("Scaler Module",50));
   crate->AddCrateModule( slot = 3, new Module<ADC>("ADC Module",50));
   crate->AddCrateModule( slot = 4, new Module<FlashADC>("fADC Module",50));
   crate->AddCrateModule( slot = 8, trig_disc_module = new Module<Discriminator>("Triggger Disc. Module",10) );

   Discriminator& trig_disc = trig_disc_module->GetChannel(0);

   for(int i = 0; i<50; i++) {

      Discriminator& disc = disc_module->GetChannel(i);
      TDC&           tdc  = tdc_module->GetChannel(i);

      disc >> tdc << trig_disc;

   }

   return crate;
}
//______________________________________________________________________________

clas12::DAQ::Crate * clas12::DAQ::BuildFlashADCCrate(){

   Crate * crate = new Crate();

   return crate;
}
//______________________________________________________________________________

