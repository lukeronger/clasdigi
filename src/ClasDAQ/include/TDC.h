#ifndef clas12_DAQ_TDCC_HH
#define clas12_DAQ_TDCC_HH 1

#include "TObject.h"
#include "Discriminator.h"

namespace clas12 {

   namespace DAQ {

      class TDC : public TObject {


         public : 
            int    fChannel;   // Channel Number
            int    fValue;     // TDC value

            int    fOffset;    // Offset of TDC peak (kind of like pedestal)
            double fResolution;// ns/channel

            double fRefTime;   // Reference time (eg, trigger)
            double fTime;      // stop time ;

         public:
            TDC(int ch = 0);
            virtual ~TDC();

            void Start(double t);
            void Stop(double t);

            double TimeDifference() { return( fTime - fRefTime ); }
            int    Readout() { return( fValue = fOffset + int((fTime - fRefTime)/fResolution) ); }

            void AddStartSignal(clas12::DAQ::Discriminator& d);
            void AddStopSignal(clas12::DAQ::Discriminator& d);

            void Print(Option_t * opt = "") const;
            void Clear(Option_t * opt = "");

            ClassDef(TDC,1)
      };

   }
}

#endif

