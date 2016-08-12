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
            int            fNParticleHitsBar;
            int            fNParticleHitsTile;
            int            fNPhotonHits;
            int            fNChannelHits;
            TClonesArray * fHits;           //->
            TClonesArray * fParticleHitsBar;   //->
            TClonesArray * fParticleHitsTile;   //->
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

            ParticleHit * AddParticleHitBar(int chan = 0);
            ParticleHit * GetParticleHitBar(int i);

            ParticleHit * AddParticleHitTile(int chan = 0);
            ParticleHit * GetParticleHitTile(int i);

            PhotonHit * AddPhotonHit(int chan = 0);
            PhotonHit * GetPhotonHit(int i);

            ScintChannelHit * AddChannelHit(int chan = 0);
            ScintChannelHit * GetChannelHit(int i);

            void Clear(Option_t * opt = "")  ;
            void Print(Option_t * opt = "") const  ;

         ClassDef(RecoilScintEvent,10)
      };

   }

}

#endif

