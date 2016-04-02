#ifndef DriftChamberParticleHit_HH
#define DriftChamberParticleHit_HH 1

#include "TObject.h"
#include "TLorentzVector.h"
#include "DCWire.h"
#include "ParticleHit.h"

namespace clas12 {

   namespace hits {

      class DriftChamberParticleHit : public ParticleHit {

         public : 
            //int             fChannel;        // Channel number .
            //int             fPDGCode;        // PDG code of particle.
            //int             fTrackID;        // track id of particle.
            //TLorentzVector  fPosition;       //  
            //TLorentzVector  fGlobalPosition; //  
            //TLorentzVector  fMomentum;       // 
            DCWire          fDCWire;         // Wire 

            DriftChamberParticleHit();
            virtual ~DriftChamberParticleHit();

            void Print();

            ClassDef(DriftChamberParticleHit,3)
      };

   }

}

#endif

