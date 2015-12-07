#ifndef clas12_mag_CLAS12MagneticField_HH
#define clas12_mag_CLAS12MagneticField_HH 1

#include <iostream>

#include "TVirtualMagField.h"
#include "TEveTrackPropagator.h"
#include "TEveVector.h"

//#include "CLHEP/Units/PhysicalConstants.h"

#include "ToroidField.h"
#include "SolenoidField.h"

namespace clas12 {

   namespace mag {

      class CLAS12MagneticField : public TEveMagField {

         protected:
            double         fMaximumField;

            clas12::mag::ToroidField      fToroidField;
            clas12::mag::SolenoidField    fSolenoidField;

         public:
            CLAS12MagneticField();
            virtual ~CLAS12MagneticField();

            //using   TEveMagField::GetField;

            Double_t   GetMaxFieldMagD() const { return fMaximumField;  }
            //virtual Float_t  GetMaxFieldMag() const { return fMaximumField; }
            //virtual TEveVector GetField(Float_t x, Float_t y, Float_t z) const;

            TEveVectorD GetFieldD(Double_t x, Double_t y, Double_t z) const ; 

            ClassDef(CLAS12MagneticField,1)
      };

   }
}

#endif
