#include <iostream>
#include <random>
#include "TriggerSupervisor.h"
#include "Discriminator.h"
#include "TDC.h"

int main( int argc, char **argv )
{
   using namespace clas12::DAQ;

   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dis(0, 5);

   Discriminator  d0(0,1.0);
   Discriminator  d1(1,1.0);

   TDC tdc0;
   tdc0.AddStartSignal(d0);
   tdc0.AddStopSignal(d1);

   TDC tdc1;
   d0 >> tdc1 << d1;

   d0.Count(10.1234);
   d1.Count(15.023);

   tdc0.Print();
   std::cout << "TDC readout : " << tdc0.Readout() << std::endl;
   std::cout << "  time diff : " << tdc0.TimeDifference() << std::endl;
   tdc0.Print();
   std::cout << "TDC readout : " << tdc1.Readout() << std::endl;
   std::cout << "  time diff : " << tdc1.TimeDifference() << std::endl;
   tdc1.Clear();

   d0.Count(100.030);
   d1.Count(125.230);

   tdc0.Print();
   std::cout << "TDC readout : " << tdc0.Readout() << std::endl;
   std::cout << "  time diff : " << tdc0.TimeDifference() << std::endl;
   tdc0.Print();
   std::cout << "TDC readout : " << tdc1.Readout() << std::endl;
   std::cout << "  time diff : " << tdc1.TimeDifference() << std::endl;
   tdc1.Clear();

   return 0;
}

