#ifndef clas12_sigs_CLAS12SigsEvent_HH
#define clas12_sigs_CLAS12SigsEvent_HH 1

#include "TObject.h"

#include "HTCCSigsEvent.h"

namespace clas12 {

   namespace sigs {

      class CLAS12SigsEvent : public TObject {

         public:
            int              fRunNumber;
            int              fEventNumber;

            HTCCSigsEvent    fHTCCEvent;

         public:
            CLAS12SigsEvent();
            virtual ~CLAS12SigsEvent();

            void Clear(Option_t * opt = "" ) override;
            void Print(Option_t * opt = "" ) const override;

         ClassDef(CLAS12SigsEvent,1)
      };

   }

}

#endif

