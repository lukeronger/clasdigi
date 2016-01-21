#ifndef RecoilChamberParticleHit_HH
#define RecoilChamberParticleHit_HH 1

#include "TObject.h"
#include "TLorentzVector.h"

namespace clas12 {

   namespace hits {


      class RecoilChamberParticleHit : public TObject {

         public : 
            int             fChannel;        // Channel number .
            int             fPDGCode;        // PDG code of particle.
            TLorentzVector  fPosition;       //  
            TLorentzVector  fGlobalPosition; //  
            TLorentzVector  fMomentum;       // 

         public :
            RecoilChamberParticleHit();
            virtual ~RecoilChamberParticleHit();

            void Print();

            ClassDef(RecoilChamberParticleHit,1)
      };

   }

}

#endif

