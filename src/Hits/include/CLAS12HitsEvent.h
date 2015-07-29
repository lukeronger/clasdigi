#ifndef clas12_hits_CLAS12HitsEvent_HH
#define clas12_hits_CLAS12HitsEvent_HH 1

#include "TObject.h"

#include "HTCCHitsEvent.h"

namespace clas12 {

   namespace hits {

      class CLAS12HitsEvent : public TObject {

         public:
            CLAS12HitsEvent();
            virtual ~CLAS12HitsEvent();

            int fRunNumber;
            int fEventNumber;

            HTCCHitsEvent    fHTCCEvent;

         ClassDef(CLAS12HitsEvent,1)
      };

   }

}

#endif

