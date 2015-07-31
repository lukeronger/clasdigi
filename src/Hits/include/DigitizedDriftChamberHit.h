#ifndef DigitizedDriftChamberHit_HH
#define DigitizedDriftChamberHit_HH 1

#include "TObject.h"
#include "TLorentzVector.h"

namespace clas12 {

   namespace DriftChamber {

      //double P_j_ion_pair(double y, int j, double k = 28.0/*1/cm*/);

   }

class DigitizedDriftChamberHit : public TObject {
   public : 
      double          StepLength;   // Step length used to determine ion pair probabilty
      int             PDGCode;      // PDG code of particle.
      TLorentzVector  fPosition;      // Location where ion pair was produced position and time 
      DigitizedDriftChamberHit();
      virtual ~DigitizedDriftChamberHit();
      void Print();

      ClassDef(DigitizedDriftChamberHit,1)
};


}

#endif

