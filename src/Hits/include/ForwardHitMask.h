#ifndef clas12_hits_ForwardHitMask_HH
#define clas12_hits_ForwardHitMask_HH 1

#include "TObject.h"

namespace clas12 {

   namespace hits {

      /** Hit mask used for fastMC to check if detectors have been hit.
       */
      class ForwardHitMask : public TObject {

         public:
            int      fRunNumber    = 0;
            int      fEventNumber  = 0;

            int      fHTCC         = 0;
            int      fEC           = 0;
            int      fPC           = 0;
            int      fDC           = 0;

         public:
            ForwardHitMask();
            virtual ~ForwardHitMask();

            void Clear(Option_t * opt = "" ) override;
            void Print(Option_t * opt = "" ) const override;

         ClassDef(ForwardHitMask,1)
      };

   }

}

#endif

