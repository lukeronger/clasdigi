#ifndef clas12_hits_RCHitsEvent_HH
#define clas12_hits_RCHitsEvent_HH 1

#include "TObject.h"
#include "TClonesArray.h"
#include "ADCHit.h"
#include "TDCHit.h"
#include "FlashADCHit.h"
#include "DriftChamberIonPairHit.h"
#include "RecoilChamberParticleHit.h"

namespace clas12 {

   namespace hits {

      class RCHitsEvent : public TObject {

         public:
            int            fRunNumber;
            int            fEventNumber;

            int            fNADCHits;
            int            fNTDCHits;
            int            fNIonPairs;
            int            fNParticleHits;
            int            fNRegionHits;


            TClonesArray * fADCHits;       //->
            TClonesArray * fTDCHits;       //->
            TClonesArray * fIonPairs;      //->
            TClonesArray * fParticleHits;  //->
            TClonesArray * fRegionHits;    //->

            double          fTotalTrackLength = 0.0;
            double          fTotalDeltaE      = 0.0;

         public:
            RCHitsEvent();
            virtual ~RCHitsEvent();

            TDCHit                   * AddTDCHit(int ch, int v, double t) ;
            ADCHit                   * AddADCHit(int ch, int v) ;
            DriftChamberIonPairHit   * AddIonPairHit(double x, double y, double z, double t);
            RecoilChamberParticleHit * AddParticleHit();
            RecoilChamberParticleHit * AddRegionHit();

            RecoilChamberParticleHit * GetParticleHit(int );
            RecoilChamberParticleHit * GetRegionHit(int );

            void Clear(Option_t * opt = "")  ;
            void Print(Option_t * opt = "") const  ;

         ClassDef(RCHitsEvent,4)
      };

   }

}

#endif

