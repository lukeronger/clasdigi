#include <iostream>
#include <random>
#include "DigitizedSignal.h"
#include "FlashADCSignal.h"
#include "FlashADC.h"

int main( int argc, char **argv )
{

   using namespace clas12::DAQ;

   FlashADC  fADC(0);
   fADC.Count( 0.0);
   fADC.Count(40.0);
   fADC.Count(80.0);

   clas12::sigs::FlashADCSignal sig0(8);

   sig0.fBuffer = fADC.fBuffer;

   sig0.fCrate = 1;
   sig0.fSlot  = 3;

   sig0.fTag = 100;
   sig0.fNum = 12;

   sig0.Print();
   sig0.PrintBuffer();

   return 0;
}

