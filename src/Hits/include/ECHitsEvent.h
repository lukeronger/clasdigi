#ifndef clas12_hits_ECHitsEvent_HH
#define clas12_hits_ECHitsEvent_HH 1

#include "TObject.h"
#include "TClonesArray.h"
#include "ADCHit.h"
#include "TDCHit.h"
#include "FlashADCHit.h"
#include "ParticleHit.h"

namespace clas12 {

   namespace hits {

      class ECHitsEvent : public TObject {

         public:
            int            fRunNumber;
            int            fEventNumber;

            int            fNADCHits;
            int            fNTDCHits;
            int            fNParticleHits;
            int            fNRegionHits;

            TClonesArray * fADCHits;   //->
            TClonesArray * fTDCHits;   //->
            TClonesArray * fParticleHits;  //->
            TClonesArray * fRegionHits;  //->

         public:
            ECHitsEvent();
            virtual ~ECHitsEvent();

            TDCHit                  * AddTDCHit(int ch, int v, double t) ;
            ADCHit                  * AddADCHit(int ch, int v) ;

            ParticleHit * AddParticleHit();
            ParticleHit * AddRegionHit();

            ParticleHit * GetParticleHit(int );
            ParticleHit * GetRegionHit(int );

            void Clear(Option_t * opt = "")  ;
            void Print(Option_t * opt = "") const  ;

         ClassDef(ECHitsEvent,3)
      };

   }

}

#endif

