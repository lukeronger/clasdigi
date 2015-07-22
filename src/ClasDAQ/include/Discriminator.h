#ifndef clas12_DAQ_Discriminator_HH
#define clas12_DAQ_Discriminator_HH 1

#include "TObject.h"
#include <functional>

namespace clas12 {

   namespace DAQ {

      class Discriminator : public TObject {

         public : 
            int          fChannel;      // Channel Number
            double       fThreshold;    // Discriminator value
            double       fGateWidth;    // Size of gate in ns 

            double       fAccumulated;  // An accumlated quantity
            int          fCounted;      // A counted quantity (eg photons)
            double       fTimeFired;    // The time fired

            bool         fLatched;      // The discriminator has been triggerd and is output a pulse still

            Discriminator(int ch = 0, double thr = 1.0);
            virtual ~Discriminator();

            virtual bool Count(double time); 

            virtual void Clear(Option_t * o = "");
            virtual void Print(Option_t * o = "") const ;

            std::vector< std::function<void()> >       fCallbacks;
            std::vector< std::function<void(double)> > fTriggerCallbacks;

         protected:
            virtual bool ProcessLatch(double time); 

            ClassDef(Discriminator,1)
      };

   }
}

#endif

