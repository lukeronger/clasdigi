#include <iostream>
#include <random>
#include "Crate.h"
#include "CLAS12DAQ.h"
#include "CrateModule.h"
#include "ModuleChannel.h"
#include "Module.h"
#include "TDC.h"
#include "DAQManager.h"

int main( int argc, char **argv )
{
   using namespace clas12::DAQ;

   Crate * c = BuildCrate();
   Crate * c2 = BuildCrate();
   c->Print();

   DAQManager * daq_manager = DAQManager::GetManager();
   std::cout << "crate at " << daq_manager->AddCrate(c) << std::endl;
   std::cout << "crate at " << daq_manager->AddCrate(c) << std::endl;
   std::cout << "crate at " << daq_manager->AddCrate(c2) << std::endl;
   std::cout << "crate at " << daq_manager->AddCrate(c) << std::endl;

   Module<TDC> * m0 = 0;

   //c->GetCrateModule(0,m0);
   //c->GetCrateModule(1,m0);
   //std::cout << m0 << std::endl;
   //c->GetCrateModule(2,m0);
   //c->GetCrateModule(3,m0);
   //c->Print();
   m0 = c->GetCrateModule<TDC>(0);
   std::cout << m0 << std::endl;
   m0 = c->GetCrateModule<TDC>(1);
   std::cout << m0 << std::endl;
   m0 = c->GetCrateModule<TDC>(2);
   std::cout << m0 << std::endl;
   m0 = c->GetCrateModule<TDC>(3);
   std::cout << m0 << std::endl;

   c->Clear();
   Module<TDC> * m1  = c->GetCrateModule<TDC>(1);
      std::cout << m1 << std::endl;
   if(m1){
      std::cout << "derp derp" << std::endl;
      m1->GetChannel(0).Start(0.1);
      m1->GetChannel(0).Stop(4.1);
      m1->Print();
   }
   //c->Print("v");

   //CrateModule * m0 = new CrateModule("custom");
   //m0->SetNChannels(4);

   //m0->SetChannel(0, new TDC(0));
   //m0->SetChannel(1, new TDC(1));
   //m0->SetChannel(2, new TDC(2));
   //m0->SetChannel(3, new TDC(4));

   //m0->Print();
   //m0->fChannels.Print();

   //CrateModule * m1 = new CrateModule("customer");
   //m1->SetNChannels(48);

   //Module<TDC> * m2 = new Module<TDC>("Template TDC module");
   //c1.AddModule(6, m2);

   //c1.AddModule(1, new CrateModule("TDC"));
   //c1.AddModule(2, new CrateModule("TDC"));
   //c1.AddModule(3, new CrateModule("TDC"));

   //c1.AddModule(4, m0);
   //c1.AddModule(5, m1);

   //c1.AddModule(9, new CrateModule("something else really long"));
   //c1.AddModule(8, new CrateModule("fADC"));

   //c1.Print();

   return 0;
}

