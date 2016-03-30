#ifndef clas12_DAQ_TDCC_HH
#define clas12_DAQ_TDCC_HH 1

#include "TObject.h"
#include "Discriminator.h"
#include "ModuleChannel.h"

namespace clas12 {

   namespace DAQ {

      class TDC : public ModuleChannel {

         public : 

            int       fOffset       = 100;   // shift of TDC peak (added to value for readout)
            double    fResolution   = 0.06;  // ns/channel (0.06ns is the fine grain resolution of fADC);

            double    fRefTime;     // Reference time (eg, trigger)
            double    fTime;        // stop time ;
            int       fValue;       // TDC value

         public:
            TDC(int ch = 0, int o = 100);
            virtual ~TDC();

            void Start(double t);
            void Stop(double t);

            double TimeDifference() { return( fTime - fRefTime ); }
            int    Readout() { return( fValue = fOffset + int((fTime - fRefTime)/fResolution) ); }

            void AddStartSignal(clas12::DAQ::Discriminator& d);
            void AddStopSignal(clas12::DAQ::Discriminator& d);

            void Reset(Option_t * o = "")  { Clear(o); }
            void Print(Option_t * opt = "") const ;
            void Clear(Option_t * opt = "") ;

            TDC& operator<<(Discriminator& rhs)
            {
               this->AddStopSignal(rhs);
               return (*this);
            }

            ClassDef(TDC,1)
      };

   }
}


#endif

