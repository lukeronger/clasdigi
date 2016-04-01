#ifndef clas12_hits_ParticleHit_HH
#define clas12_hits_ParticleHit_HH 1

#include "TObject.h"
#include "TLorentzVector.h"

namespace clas12 {

   namespace hits {

      class ParticleHit : public TObject {

         public : 
            int             fChannel;        // Channel number .
            int             fPDGCode;        // PDG code of particle.
            int             fTrackID;        // track id of particle.
            TLorentzVector  fPosition;       //  
            TLorentzVector  fGlobalPosition; //  
            TLorentzVector  fMomentum;       // 

         public :
            ParticleHit();
            virtual ~ParticleHit();

            void Print();

            ClassDef(ParticleHit,1)
      };

   }

}

#endif

