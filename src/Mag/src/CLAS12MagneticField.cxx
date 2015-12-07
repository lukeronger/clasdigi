#include "CLAS12MagneticField.h"

clas12::mag::CLAS12MagneticField::CLAS12MagneticField(): fMaximumField(6.0)
{

   fToroidField.ReadMap();
   fSolenoidField.ReadMap();
 
}
//______________________________________________________________________________

clas12::mag::CLAS12MagneticField::~CLAS12MagneticField()
{
}
//______________________________________________________________________________

//TEveVector CLAS12MagneticField::GetField(Float_t x, Float_t y, Float_t z) const {
TEveVectorD clas12::mag::CLAS12MagneticField::GetFieldD(Double_t x, Double_t y, Double_t z) const
{
   double field_value[3] = {0.0, 0.0, 0.0};
   double pos[4] = {x, y, z, 0.0};

   TEveVectorD result1(0,0,0); //(field_value[0]/tesla, field_value[1]/tesla, field_value[2]/tesla);
   result1.Set( fToroidField.GetField(x,y,z) );

   TEveVectorD result2(0,0,0);//(field_value[0]/tesla, field_value[1]/tesla, field_value[2]/tesla);
   result2.Set( fSolenoidField.GetField(x,y,z) );

   result1 += result2;

   // The TEveMagField class has an inverted convetion
   result1 *= -1.0;


   //field_value[2] = z;
   //std::cout << "x = " << pos[0] << ", y = " << pos[1] << ", z = " << pos[2] << "\n";
   //std::cout << "Bx = " << field_value[0] << ", By = " << field_value[1] << ", Bz = " << field_value[2] << "\n";

   return  result1;
}
//______________________________________________________________________________

