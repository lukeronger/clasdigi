#ifndef clas12_hits_RecoilScintEvent_HH
#define clas12_hits_RecoilScintEvent_HH 1

#include "TObject.h"
#include "TClonesArray.h"
#include "RecoilScintHit.h"
#include "PhotonHit.h"
#include "ParticleHit.h"
#include "ScintChannelHit.h"
#include "PhotonCounterHit.h"
#include <map>

namespace clas12 {

   namespace hits {

      class RecoilScintEvent : public TObject {

         public:
            int            fRunNumber;
            int            fEventNumber;

            int            fNHits;
            int            fNParticleHits;
            int            fNPhotonHits;
            int            fNChannelHits;
            TClonesArray * fHits;           //->
            TClonesArray * fParticleHits;   //->
            TClonesArray * fPhotonHits;     //->
            TClonesArray * fChannelHits;    //->

	    std::map<int,PhotonCounterHit>  fPhotonCounterHits0;
            std::map<int,PhotonCounterHit>  fPhotonCounterHits1;
            std::map<int,PhotonCounterHit>  fPhotonCounterHitsTile;
            std::map<int,ScintChannelHit>   fScintChannelHitsBar;
            std::map<int,ScintChannelHit>   fScintChannelHitsTile;


         public:
            RecoilScintEvent();
            virtual ~RecoilScintEvent();

            RecoilScintHit * AddHit(int chan = 0);
            RecoilScintHit * GetHit(int i);

            ParticleHit * AddParticleHit(int chan = 0);
            ParticleHit * GetParticleHit(int i);

            PhotonHit * AddPhotonHit(int chan = 0);
            PhotonHit * GetPhotonHit(int i);

            ScintChannelHit * AddChannelHit(int chan = 0);
            ScintChannelHit * GetChannelHit(int i);

            void Clear(Option_t * opt = "")  ;
            void Print(Option_t * opt = "") const  ;

         ClassDef(RecoilScintEvent,8)
      };

   }

}

#endif

