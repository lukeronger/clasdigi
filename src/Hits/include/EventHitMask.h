#ifndef clas12_hits_EventHitMask_HH
#define clas12_hits_EventHitMask_HH 1

#include "TObject.h"

namespace clas12 {

   namespace hits {

      /** Hit mask used for fastMC to check if detectors have been hit.
       */
      class EventHitMask : public TObject {

         public:
            int      fRunNumber    = 0;
            int      fEventNumber  = 0;

            int      fHTCC         = 0;
            int      fEC           = 0;
            int      fPC           = 0;
            int      fDC           = 0;
            int      fSVT          = 0;
            int      fBMT          = 0;
            int      fRC           = 0;
            int      fRH           = 0;

            int      fStatus        = 0;
            int      fFowardStatus  = 0;
            int      fCentralStatus = 0;

            int      fNGoodTracks   = 0;
            int      fElectron      = 0;

         public:
            EventHitMask();
            virtual ~EventHitMask();

            void Clear(Option_t * opt = "" ) ;
            void Print(Option_t * opt = "" ) const ;

         ClassDef(EventHitMask,1)
      };

   }

}

#endif

