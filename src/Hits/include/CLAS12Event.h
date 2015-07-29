#ifndef clas12_hits_CLAS12Event_HH
#define clas12_hits_CLAS12Event_HH

#include "TObject.h"
#include "ADCHit.h"

namespace clas12 {

   namespace hits {

      class CLAS12Event : public TObject {

         public:
            CLAS12Event();
            virtual ~CLAS12Event();

            int fRunNumber;
            int fEventNumber;

         ClassDef(CLAS12Event,1)
      };

   }

}

#endif

