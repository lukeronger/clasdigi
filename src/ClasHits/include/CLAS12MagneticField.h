#ifndef CLAS12MagneticField_HH
#define CLAS12MagneticField_HH

#include <iostream>

#include "TVirtualMagField.h"
#include "TEveTrackPropagator.h"
#include "TEveVector.h"

class CLAS12MagneticField : public TEveMagField {
   protected:
      double         fMaximumField;

   public:
      CLAS12MagneticField();
      ~CLAS12MagneticField();

      //using   TEveMagField::GetField;

      Double_t   GetMaxFieldMagD() const { return fMaximumField;  }
      //virtual Float_t  GetMaxFieldMag() const { return fMaximumField; }
      //virtual TEveVector GetField(Float_t x, Float_t y, Float_t z) const;
      
      TEveVectorD GetFieldD(Double_t x, Double_t y, Double_t z) const ; 

      ClassDef(CLAS12MagneticField,1)
};

#endif
