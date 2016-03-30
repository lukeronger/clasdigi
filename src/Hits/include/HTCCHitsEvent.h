#ifndef clas12_hits_HTCCHitsEvent_HH
#define clas12_hits_HTCCHitsEvent_HH 1

#include "TObject.h"
#include "TClonesArray.h"
#include "ADCHit.h"
#include "TDCHit.h"
#include "FlashADCHit.h"

namespace clas12 {

   namespace hits {

      class HTCCHitsEvent : public TObject {

         public:
            int            fRunNumber;
            int            fEventNumber;

            int            fNADCHits;
            int            fNTDCHits;

            TClonesArray * fADCHits;   //->
            TClonesArray * fTDCHits;   //->

         public:
            HTCCHitsEvent();
            virtual ~HTCCHitsEvent();

            TDCHit * AddTDCHit(int ch, int v, double t) ;
            ADCHit * AddADCHit(int ch, int v) ;

            void Clear(Option_t * opt = "")  ;
            void Print(Option_t * opt = "") const  ;

         ClassDef(HTCCHitsEvent,1)
      };

   }

}

#endif

