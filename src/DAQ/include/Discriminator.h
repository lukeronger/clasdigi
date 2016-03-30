#ifndef clas12_DAQ_Discriminator_HH
#define clas12_DAQ_Discriminator_HH 1

#include "TObject.h"
#include "ModuleChannel.h"
#include <functional>

namespace clas12 {

   namespace DAQ {

      class TDC;

      class Discriminator : public ModuleChannel {

         public : 
            double       fThreshold;    // Discriminator value
            double       fGateWidth;    // Size of gate in ns 

            double       fAccumulated;  // An accumlated quantity
            int          fCounted;      // A counted quantity (eg photons)
            double       fLastCountTime;// time from the previous call to count
            double       fTimeFired;    // The time fired


            bool         fLatched;      // The discriminator has been triggerd and is output a pulse still

         public : 
            Discriminator(int ch = 0, double thr = 1.0);
            virtual ~Discriminator();

            virtual bool Count(double time); 


            virtual void Reset(Option_t * o = "")  { Clear(o); }
            virtual void Clear(Option_t * o = "") ;
            virtual void Print(Option_t * o = "") const  ;

            std::vector< std::function<void()> >       fCallbacks;
            std::vector< std::function<void(double)> > fTriggerCallbacks;

            TDC& operator>>(TDC& rhs);

         protected:
            virtual bool ProcessLatch(double time); 

            ClassDef(Discriminator,1)
      };

      //TDC& operator>>(Discriminator& lhs,TDC& rhs);
      //TDC& operator<<(TDC& lhs, Discriminator& rhs);

   }
}

#endif

