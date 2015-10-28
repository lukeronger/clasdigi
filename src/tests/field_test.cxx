#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "SolenoidField.h"
#include "ToroidField.h"

int main( int argc, char **argv )
{
   using namespace clas12::mag;

   SolenoidField field;

   TVector3 val = field.GetField(0.0,0.0,0.0);
   val.Print();
   val = field.GetField(1.0,1.0,1.0);
   val.Print();
   val = field.GetField(0.0,2.0,0.0);
   val.Print();


   ToroidField tfield;
   val = tfield.GetField(0.0,0.0,400.0);
   val.Print();
   val = tfield.GetField(50.0,50.0,400.0);
   val.Print();
   val = tfield.GetField(0.0,50.0,400.0);
   val.Print();
   val = tfield.GetField(0.0,-50.0,400.0);
   val.Print();

   return 0;
}

