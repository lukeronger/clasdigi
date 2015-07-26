#include <iostream>
#include <random>
#include "Crate.h"
#include "CrateModule.h"
#include "ModuleChannel.h"
#include "TDC.h"

int main( int argc, char **argv )
{
   using namespace clas12::DAQ;

   Crate c1("crateA");


   CrateModule * m0 = new CrateModule("custom");
   m0->SetNChannels(9);

   CrateModule * m1 = new CrateModule("customer");
   m1->SetNChannels(48);

   c1.AddModule(1, new CrateModule("TDC"));
   c1.AddModule(2, new CrateModule("TDC"));
   c1.AddModule(3, new CrateModule("TDC"));

   c1.AddModule(4, m0);
   c1.AddModule(5, m1);

   c1.AddModule(9, new CrateModule("something else really long"));
   c1.AddModule(8, new CrateModule("fADC"));


   c1.Print();

   return 0;
}

