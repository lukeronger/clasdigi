#ifndef clas12_sigs_DCSigsEvent_HH
#define clas12_sigs_DCSigsEvent_HH 1

#include "TObject.h"
#include "TClonesArray.h"
#include "ADCSignal.h"
#include "TDCSignal.h"

namespace clas12 {

   namespace sigs {

      class DCSigsEvent : public TObject {

         public:
            int            fRunNumber;
            int            fEventNumber;

            int            fNADCsigs;
            int            fNTDCsigs;

            TClonesArray * fADCsigs;   //->
            TClonesArray * fTDCsigs;   //->

         public:
            DCSigsEvent();
            virtual ~DCSigsEvent();

            TDCSignal * AddTDCSignal(int ch, int v) ;
            ADCSignal * AddADCSignal(int ch, int v) ;

            void Clear(Option_t * opt = "") override ;
            void Print(Option_t * opt = "") const override ;

         ClassDef(DCSigsEvent,1)
      };

   }

}

#endif

