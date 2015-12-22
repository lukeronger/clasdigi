#ifndef clas12_hits_RecoilScintEvent_HH
#define clas12_hits_RecoilScintEvent_HH 1

#include "TObject.h"
#include "TClonesArray.h"
#include "RecoilScintHit.h"
#include "PhotonHit.h"

namespace clas12 {

   namespace hits {

      class RecoilScintEvent : public TObject {

         public:
            int            fRunNumber;
            int            fEventNumber;
            int            fNHits;
            int            fNPhotonHits;
            TClonesArray * fHits;        //->
            TClonesArray * fPhotonHits;  //->

         public:
            RecoilScintEvent();
            virtual ~RecoilScintEvent();

            RecoilScintHit * AddHit(int chan = 0);
            RecoilScintHit * GetHit(int i);

            PhotonHit * AddPhotonHit(int chan = 0);
            PhotonHit * GetPhotonHit(int i);

            //TDCHit                  * AddTDCHit(int ch, int v, double t) ;
            //ADCHit                  * AddADCHit(int ch, int v) ;
            //DriftChamberIonPairHit  * AddIonPairHit(double x, double y, double z, double t);
            //DriftChamberParticleHit * AddParticleHit();
            //DriftChamberParticleHit * GetRegionHit(int );

            void Clear(Option_t * opt = "") override ;
            void Print(Option_t * opt = "") const override ;

         ClassDef(RecoilScintEvent,4)
      };

   }

}

#endif

