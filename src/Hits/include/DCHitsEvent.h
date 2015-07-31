#ifndef clas12_hits_DCHitsEvent_HH
#define clas12_hits_DCHitsEvent_HH 1

#include "TObject.h"
#include "TClonesArray.h"
#include "ADCHit.h"
#include "TDCHit.h"
#include "FlashADCHit.h"
#include "TLorentzVector.h"

namespace clas12 {

   namespace hits {

      class DCHitsEvent : public TObject {

         public:
            int            fRunNumber;
            int            fEventNumber;

            int            fNADCHits;
            int            fNTDCHits;
            int            fNIonPairs;

            TClonesArray * fADCHits;   //->
            TClonesArray * fTDCHits;   //->
            TClonesArray * fIonPairs;  //->

         public:
            DCHitsEvent();
            virtual ~DCHitsEvent();

            TDCHit         * AddTDCHit(int ch, int v, double t) ;
            ADCHit         * AddADCHit(int ch, int v) ;
            TLorentzVector * AddIonPair(double x, double y, double z, double t);

            void Clear(Option_t * opt = "") override ;
            void Print(Option_t * opt = "") const override ;

         ClassDef(DCHitsEvent,1)
      };

   }

}

#endif

