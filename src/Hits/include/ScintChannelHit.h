#ifndef ScintChannelHit_HH
#define ScintChannelHit_HH 1

#include "TObject.h"
//#include "TLorentzVector.h"
//#include "TMath.h"


namespace clas12 {

   namespace hits {
      
      class ScintChannelHit : public TObject {
         public: 
            int             fChannel;
            int             fSteps;
            double          fEDep;

         public: 
            ScintChannelHit();
            virtual ~ScintChannelHit();
            ScintChannelHit(const ScintChannelHit&) = default;
            ScintChannelHit(ScintChannelHit&&)      = default;
            ScintChannelHit& operator=(const ScintChannelHit&) = default;
            ScintChannelHit& operator=(ScintChannelHit&&)      = default;

            void Print();
            void Clear(Option_t * opt = "");

            ClassDef(ScintChannelHit,1)
      };

   }

}

#endif

