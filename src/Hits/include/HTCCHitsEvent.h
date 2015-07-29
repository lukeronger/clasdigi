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
            HTCCHitsEvent();
            virtual ~HTCCHitsEvent();

            int fRunNumber;
            int fEventNumber;

            TClonesArray * fADCHits;   //->
            TClonesArray * fTDCHits;   //->

         ClassDef(HTCCHitsEvent,1)
      };

   }

}

#endif

