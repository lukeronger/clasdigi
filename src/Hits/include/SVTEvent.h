#ifndef clas12_hits_SVTEvent_HH
#define clas12_hits_SVTEvent_HH 1

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

      class SVTEvent : public TObject {

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

            std::map<int,PhotonCounterHit>  fPhotonCounterHits;
            std::map<int,ScintChannelHit>   fScintChannelHits;

         public:
            SVTEvent();
            virtual ~SVTEvent();

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

         ClassDef(SVTEvent,6)
      };

   }

}

#endif

