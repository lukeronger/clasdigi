#ifndef clas12_hits_RecoilScintEvent_HH
#define clas12_hits_RecoilScintEvent_HH 1

#include "TObject.h"
#include "TClonesArray.h"
#include "RecoilScintHit.h"
#include "PhotonHit.h"
#include "ParticleHit.h"

namespace clas12 {

   namespace hits {

      class RecoilScintEvent : public TObject {

         public:
            int            fRunNumber;
            int            fEventNumber;
            int            fNHits;
            int            fNParticleHits;
            int            fNPhotonHits;
            TClonesArray * fHits;           //->
            TClonesArray * fParticleHits;   //->
            TClonesArray * fPhotonHits;     //->

         public:
            RecoilScintEvent();
            virtual ~RecoilScintEvent();

            RecoilScintHit * AddHit(int chan = 0);
            RecoilScintHit * GetHit(int i);

            ParticleHit * AddParticleHit(int chan = 0);
            ParticleHit * GetParticleHit(int i);

            PhotonHit * AddPhotonHit(int chan = 0);
            PhotonHit * GetPhotonHit(int i);


            void Clear(Option_t * opt = "") override ;
            void Print(Option_t * opt = "") const override ;

         ClassDef(RecoilScintEvent,4)
      };

   }

}

#endif

