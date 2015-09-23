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

            TClonesArray * fADCHits;   //->
            TClonesArray * fTDCHits;   //->
            TClonesArray * fIonPairs;  //->
            TClonesArray * fParticleHits;  //->

         public:
            DCHitsEvent();
            virtual ~DCHitsEvent();

            TDCHit                  * AddTDCHit(int ch, int v, double t) ;
            ADCHit                  * AddADCHit(int ch, int v) ;
            DriftChamberIonPairHit  * AddIonPairHit(double x, double y, double z, double t);
            DriftChamberParticleHit * AddParticleHit();

            DriftChamberParticleHit * GetParticleHit(int );

            void Clear(Option_t * opt = "") override ;
            void Print(Option_t * opt = "") const override ;

         ClassDef(DCHitsEvent,2)
      };

   }

}

#endif

