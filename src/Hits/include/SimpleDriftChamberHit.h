#ifndef SimpleDriftChamberHit_HH
#define SimpleDriftChamberHit_HH 1

#include "TObject.h"
#include "TLorentzVector.h"

namespace clas12 {

class SimpleDriftChamberHit : public TObject {
   public : 
      double          StepLength;   // Step length used to determine ion pair probabilty
      int             PDGCode;      // PDG code of particle.
      TLorentzVector  fPosition;      // Location where ion pair was produced position and time 
      SimpleDriftChamberHit();
      virtual ~SimpleDriftChamberHit();
      void Print();

      ClassDef(SimpleDriftChamberHit,1)
};


}

#endif

