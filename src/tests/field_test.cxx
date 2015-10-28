#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include "SolenoidField.h"
#include "ToroidField.h"
#include "CLHEP/Units/SystemOfUnits.h"

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

   TVector3 x;
   x.SetMagThetaPhi(400.0,20.0*CLHEP::degree, 20.0*CLHEP::degree);
   TVector3 x2;
   x2.SetMagThetaPhi(400.0,20.0*CLHEP::degree, -20.0*CLHEP::degree);

   val = tfield.GetField(x);
   std::cout << " At " ; x.Print();
   std::cout << " B is "; val.Print();

   val = tfield.GetField(x2);
   std::cout << " At " ; x2.Print();
   std::cout << " B is "; val.Print();



   return 0;
}

