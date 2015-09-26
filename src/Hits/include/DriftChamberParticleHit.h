#ifndef DriftChamberParticleHit_HH
#define DriftChamberParticleHit_HH 1

#include "TObject.h"
#include "TLorentzVector.h"
#include "DCWire.h"

namespace clas12 {

   namespace hits {

      using clas12::geo::DCWire;

      class DriftChamberParticleHit : public TObject {

         public : 
            int             fPDGCode;        // PDG code of particle.
            TLorentzVector  fPosition;       // Location where ion pair was produced position and time 
            TLorentzVector  fGlobalPosition; // Location where ion pair was produced position and time 
            TLorentzVector  fMomentum;       // Momentum vector
            DCWire          fDCWire;         // Wire 

            DriftChamberParticleHit();
            virtual ~DriftChamberParticleHit();

            void Print();

            ClassDef(DriftChamberParticleHit,1)
      };

   }

}

#endif

