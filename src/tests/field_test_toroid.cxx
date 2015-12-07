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

   ToroidField field;
   field.ReadMap();

   TVector3 val;
   TVector3 x;
   TVector3 ref;

   x.SetMagThetaPhi(350.0,20.0*CLHEP::degree, 0.0*CLHEP::degree);
   ref = field.GetField(x);

   for(int i = 0; i< 90; i++) {
      x.SetMagThetaPhi(350.0,20.0*CLHEP::degree, i*4.0*CLHEP::degree);
      val = field.GetField(x);
      std::cout << (ref-val).Perp() << std::endl;;
      //std::cout << " At " ; x.Print();
      //std::cout << " B is "; val.Print();
   }

   //for(int i = 0; i< 18; i++) {
   //   x.SetMagThetaPhi(300.0,5.0*CLHEP::degree, i*20.0*CLHEP::degree);
   //   val = field.GetField(x);
   //   std::cout << " At " ; x.Print();
   //   std::cout << " B is "; val.Print();
   //}

   //for(int i = 0; i< 10; i++) {
   //   x.SetXYZ(50.0,0.0,100.0+50.0*i);
   //   val = field.GetField(x);
   //   std::cout << " At " ; x.Print();
   //   std::cout << " B is "; val.Print();
   //}

   return 0;
}

