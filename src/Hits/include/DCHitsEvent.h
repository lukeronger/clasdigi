#ifndef clas12_hits_DCHitsEvent_HH
#define clas12_hits_DCHitsEvent_HH 1

#include "TObject.h"
#include "TClonesArray.h"
#include "ADCHit.h"
#include "TDCHit.h"
#include "FlashADCHit.h"
#include "DriftChamberIonPairHit.h"
#include "DriftChamberParticleHit.h"

namespace clas12 {

   namespace hits {

      class DCHitsEvent : public TObject {

         public:
            int            fRunNumber;
            int            fEventNumber;

            int            fNADCHits;
            int            fNTDCHits;
            int            fNIonPairs;
            int            fNParticleHits;
            int            fNRegionHits;

            TClonesArray * fADCHits;   //->
            TClonesArray * fTDCHits;   //->
            TClonesArray * fIonPairs;  //->
            TClonesArray * fParticleHits;  //->
            TClonesArray * fRegionHits;  //->

         public:
            DCHitsEvent();
            virtual ~DCHitsEvent();

            TDCHit                  * AddTDCHit(int ch, int v, double t) ;
            ADCHit                  * AddADCHit(int ch, int v) ;
            DriftChamberIonPairHit  * AddIonPairHit(double x, double y, double z, double t);
            DriftChamberParticleHit * AddParticleHit();
            DriftChamberParticleHit * AddRegionHit();

            DriftChamberParticleHit * GetParticleHit(int );
            DriftChamberParticleHit * GetRegionHit(int );

            void Clear(Option_t * opt = "")  ;
            void Print(Option_t * opt = "") const  ;

         ClassDef(DCHitsEvent,3)
      };

   }

}

#endif

