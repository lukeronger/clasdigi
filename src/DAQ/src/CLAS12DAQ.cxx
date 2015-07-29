#include "CLAS12DAQ.h"
#include "CrateModule.h"
#include "Discriminator.h"
#include "ADC.h"
#include "FlashADC.h"
#include "TDC.h"

//______________________________________________________________________________

//clas12::DAQ::Crate * clas12::DAQ::BuildCrate(int slots = 18) 
//{
//   Crate * c = new Crate();
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

   CrateModule * m0 = new CrateModule("custom");
   m0->SetNChannels(4);

   m0->SetChannel(0, new TDC(0));
   m0->SetChannel(1, new TDC(1));
   m0->SetChannel(2, new TDC(2));
   m0->SetChannel(3, new TDC(4));

   m0->Print();
   m0->fChannels.Print();

   CrateModule * m1 = new CrateModule("customer");
   m1->SetNChannels(48);


   crate->AddModule(1, new CrateModule("TDC"));
   crate->AddModule(2, new CrateModule("TDC"));
   crate->AddModule(3, new CrateModule("TDC"));

   crate->AddModule(4, m0);
   crate->AddModule(5, m1);

   crate->AddModule(9, new CrateModule("something else really long"));
   crate->AddModule(8, new CrateModule("fADC"));


   return crate;
}
//______________________________________________________________________________

clas12::DAQ::Crate * clas12::DAQ::BuildFlashADCCrate(){

   Crate * crate = new Crate();

   return crate;
}
//______________________________________________________________________________

