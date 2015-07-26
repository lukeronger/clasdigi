#include "CLAS12MagneticField.h"
#include <string>
#include <stdlib.h> 

CLAS12MagneticField::CLAS12MagneticField(): fMaximumField(6.0) {



}
CLAS12MagneticField::~CLAS12MagneticField(){

}
//______________________________________________________________________________
//TEveVector CLAS12MagneticField::GetField(Float_t x, Float_t y, Float_t z) const {
TEveVectorD CLAS12MagneticField::GetFieldD(Double_t x, Double_t y, Double_t z) const {
   double field_value[3] = {0.0, 0.0, 0.0};
   double pos[4] = {x, y, z, 0.0};

   TEveVectorD result1(field_value[0], field_value[1], field_value[2]);

   TEveVectorD result2(field_value[0], field_value[1], field_value[2]);

   result1 += result2;

   //field_value[2] = z;
   //std::cout << "x = " << pos[0] << ", y = " << pos[1] << ", z = " << pos[2] << "\n";
   //std::cout << "Bx = " << field_value[0] << ", By = " << field_value[1] << ", Bz = " << field_value[2] << "\n";

   return  result1;
}
//______________________________________________________________________________

