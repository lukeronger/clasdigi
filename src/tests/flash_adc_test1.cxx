#include <iostream>
#include <random>
#include "FlashADC.h"
#include "Discriminator.h"
#include "TDC.h"

int main( int argc, char **argv )
{
   using namespace clas12::DAQ;

   FlashADC  fADC(0);

   fADC.Count(0.1);
   fADC.Count(40.0);
   fADC.Count(80.0);

   fADC.Print();
   fADC.PrintBufferHist();
   fADC.Reset(0.0);


   fADC.Count(15.0);
   fADC.Count(200.0);
   fADC.Print();
   fADC.PrintBufferHist();
   fADC.Reset(0.0);

   fADC.Count(55.0);
   fADC.Print();
   fADC.PrintBufferHist();
   fADC.Reset(0.0);

   std::cout << "derp\n";

   return 0;
}

