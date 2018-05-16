#ifndef RecoilChamberParticleHit_HH
#define RecoilChamberParticleHit_HH 1

#include "TObject.h"
#include "TLorentzVector.h"
#include "ParticleHit.h"

namespace clas12 {

   namespace hits {


      class RecoilChamberParticleHit : public ParticleHit {

         public : 
           double fDeltaE      = 0.0;
           double fTrackLength = 0.0;

            //int             fChannel;        // Channel number .
            //int             fPDGCode;        // PDG code of particle.
            //int             fTrackID;        // track id.
            //TLorentzVector  fPosition;       //  
            //TLorentzVector  fGlobalPosition; //  
            //TLorentzVector  fMomentum;       // 
            //RCWire          fRCWire;

         public :
            RecoilChamberParticleHit();
            virtual ~RecoilChamberParticleHit();
            RecoilChamberParticleHit(const RecoilChamberParticleHit&) = default;
            RecoilChamberParticleHit(RecoilChamberParticleHit&&)      = default;
            RecoilChamberParticleHit& operator=(const RecoilChamberParticleHit&) = default;
            RecoilChamberParticleHit& operator=(RecoilChamberParticleHit&&)      = default;

            void Print();

            ClassDef(RecoilChamberParticleHit,2)
      };

   }

}

#endif

