#ifndef DriftChamberIonPairHit_HH
#define DriftChamberIonPairHit_HH 1

#include "TObject.h"
#include "TLorentzVector.h"
#include "TMath.h"


namespace clas12 {

   namespace hits {

      double P_j_ion_pair(double y, int j, double k = 28.0/*1/cm*/);

      class DriftChamberIonPairHit : public TObject {
         public : 
            double          StepLength;   // Step length used to determine ion pair probabilty
            int             PDGCode;      // PDG code of particle.
            TLorentzVector  fPosition;      // Location where ion pair was produced position and time 
            DriftChamberIonPairHit();
            virtual ~DriftChamberIonPairHit();
            void Print();

            ClassDef(DriftChamberIonPairHit,1)
      };

   }

}

#endif

