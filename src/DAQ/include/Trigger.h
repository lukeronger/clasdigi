#ifndef clas12_DAQ_Trigger_HH
#define clas12_DAQ_Trigger_HH

#include "TObject.h"
#include <iostream>
#include <functional>

namespace clas12 {

   namespace DAQ {

      /**
       */
      class Trigger : public TObject {

         public:
            unsigned int  fChannel;
            unsigned int  fPreScale;
            unsigned int  fRecorded;
            unsigned int  fCounted;
            bool          fTriggered;
            double        fRefTime;

         protected:
            std::vector< std::function<void(double)> > fTSCallbacks;

         public:
            Trigger(int ch = 0, int ps = 1);
            virtual ~Trigger();

            void Clear(Option_t * opt = "") override;
            void Print(Option_t * opt = "") const override;

            void Fire(double t) ;
            bool IsTriggered() const { return fTriggered; }

            void AddTSCallback( std::function<void(double)> f ){ fTSCallbacks.push_back(f); }

            ClassDef(Trigger,1)
      };

   }

}

#endif

