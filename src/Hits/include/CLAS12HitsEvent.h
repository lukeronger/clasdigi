#ifndef clas12_hits_CLAS12HitsEvent_HH
#define clas12_hits_CLAS12HitsEvent_HH 1

#include "TObject.h"

#include "HTCCHitsEvent.h"
#include "DCHitsEvent.h"
#include "RCHitsEvent.h"
#include "ECHitsEvent.h"
#include "RecoilScintEvent.h"
#include "SVTEvent.h"
#include "EventHitMask.h"

namespace clas12 {

   namespace hits {

      class CLAS12HitsEvent : public TObject {

         public:
            int              fRunNumber;
            int              fEventNumber;

            HTCCHitsEvent    fHTCCEvent;
            ECHitsEvent      fECEvent;
            DCHitsEvent      fDCEvent;
            RCHitsEvent      fRCEvent;
            RecoilScintEvent fRHEvent;
            SVTEvent         fSVTEvent;
            //HodoEvent        fHodoEvent;

            EventHitMask     fHitMask;
            int              fNTrackHitMasks;
            TClonesArray   * fTrackHitMasks; //->

         public:
            CLAS12HitsEvent();
            virtual ~CLAS12HitsEvent();

            void SetRunNumber(  int n);
            void SetEventNumber(int n);

            void Clear(Option_t * opt = "" ) ;
            void Print(Option_t * opt = "" ) const ;

            EventHitMask * AddTrackHitMask();
            EventHitMask * GetTrackHitMask(int );
            EventHitMask * TrackHitMask(int );

         ClassDef(CLAS12HitsEvent,8)
      };

   }

}

#endif

