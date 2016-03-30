#ifndef clas12_sigs_HTCCSigsEvent_HH
#define clas12_sigs_HTCCSigsEvent_HH 1

#include "TObject.h"
#include "TClonesArray.h"
#include "ADCSignal.h"
#include "TDCSignal.h"

namespace clas12 {

   namespace sigs {

      class HTCCSigsEvent : public TObject {

         public:
            int            fRunNumber;
            int            fEventNumber;

            int            fNADCsigs;
            int            fNTDCsigs;

            TClonesArray * fADCsigs;   //->
            TClonesArray * fTDCsigs;   //->

         public:
            HTCCSigsEvent();
            virtual ~HTCCSigsEvent();

            TDCSignal * AddTDCSignal(int ch, int v) ;
            ADCSignal * AddADCSignal(int ch, int v) ;

            void Clear(Option_t * opt = "")  ;
            void Print(Option_t * opt = "") const  ;

         ClassDef(HTCCSigsEvent,1)
      };

   }

}

#endif

