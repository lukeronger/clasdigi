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

   for (int n=0; n<10; ++n)
      std::cout << dis(gen) << ' ';
   std::cout << '\n';

   TriggerSupervisor TS;
   
   TS.AddTrigger( {0,1} );
   TS.AddTrigger( {1,3} );
   TS.AddTrigger( {2,2} );
   TS.AddTrigger( {3,1} );
   TS.AddTrigger( {4,1} );
   TS.AddTrigger( {5,1} );

   Discriminator  d0(0,1.0);
   Discriminator  d1(1,1.0);

   TDC tdc;
   tdc.AddStartSignal(d0);
   tdc.AddStopSignal(d1);

   d0.Count(10.0);
   d1.Count(15.0);

   tdc.Print();
   tdc.Clear();

   d0.Count(100.0);
   d1.Count(125.0);

   tdc.Print();
   tdc.Clear();

   return 0;

   Trigger * trig = TS.GetTrigger(0);
   d0.fTriggerCallbacks.push_back( [trig](double t){ trig->Fire(t); } );

   trig = TS.GetTrigger(1);
   d0.fTriggerCallbacks.push_back( [trig](double t){ trig->Fire(t); } );

   trig = TS.GetTrigger(2);
   d0.fTriggerCallbacks.push_back( [trig](double t){ trig->Fire(t); } );




   for(int i=0; i<10; i++) {
      int rn = dis(gen);
      //std::cout << rn << ' ';
      d0.Count(23.3*i);
   }

   TS.Print();

   //for(auto t : TS.Triggers() ) t.Print();

   return 0;
}

