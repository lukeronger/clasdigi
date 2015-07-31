#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "ThrownEvent.h"

int main( int argc, char **argv )
{
   using namespace clas12::sim;

   ThrownEvent event;

   std::cout << "Opening " << argv[1] << std::endl;
   std::ifstream inputfile(argv[1]);

   for(int i=0 ;i<10;i++) {
      event.ReadLundEvent(inputfile);
      event.Print();
   }

   return 0;
}

