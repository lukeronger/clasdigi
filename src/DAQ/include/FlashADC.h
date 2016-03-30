#ifndef clas12_DAQ_FlashADC_HH
#define clas12_DAQ_FlashADC_HH 1

#include "TObject.h"
#include "Discriminator.h"
#include "ModuleChannel.h"
#include <vector>
#include <cmath>

namespace clas12 {

   namespace DAQ {

      double pulse_waveform(double t, double tau = 7.5, double sig = 0.45) ;

      class FlashADC : public ModuleChannel {

         public : 
            int     fNSB           = 10;  // Number of samples before TC (<512)
            int     fNSA           = 20;  // Number of samples after TC  (<512)
            int     fTriggerWindow = 100; // Trigger window 

            double    fRefTime       = 0.0; // Reference time (eg, trigger)
            double    fTime          = 0.0; // Time since last reset 

            std::vector<int>     fBuffer;  // fADC buffer
            std::vector<int>     fTCs;     // Array of TCs. Stores buffer index

            double    fSampleFreq      = 4.0;    // sample  
            double    fTimeResolution  = 0.0625; // ns/channel after fine  grain time determination

         protected:
            Discriminator        fDisc;    // Internal disc used to measure a TC
            std::vector<int>     fPulse;
            int                  fPulseMax = 2;       // Location of maximum value 


         public:
            FlashADC(int ch = 0);
            virtual ~FlashADC();

            void Stop(double t);
            void Reset(double t);

            double TimeDifference() { return( fTime - fRefTime ); }
            std::vector<int>::iterator   Readout() { return (fBuffer.begin() + 3); }

            //void AddStartSignal(clas12::DAQ::Discriminator& d);
            virtual bool Count(double time){
               return fDisc.Count(time);
            }

            void PrintBuffer() const;
            void PrintBufferHist(int nY = 10, int peak = 1000) const;

            void Print(Option_t * opt = "") const ;
            void Clear(Option_t * opt = "") ;
            void Reset(Option_t * opt = "")  { Clear(opt); }

            FlashADC& operator<<(Discriminator& rhs)
            {
               this->AddStopSignal(rhs);
               return (*this);
            }

         protected:
            // This is protected because the disc is handled internerally
            void AddStopSignal(clas12::DAQ::Discriminator& d);

            void AddPulseToBuffer(int n, double amp = 1.0) ;

            ClassDef(FlashADC,1)
      };

   }
}


#endif

