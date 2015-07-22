#ifndef CLAS12_TriggerSupervisor_HH
#define CLAS12_TriggerSupervisor_HH

#include "TObject.h"

#include <iostream>
#include <vector>
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

            void Fire(double t) {
               fCounted++;
               if(fCounted%fPreScale == 0)
               {
                  fRefTime   = t;
                  fTriggered = true;
                  fRecorded++;
                  std::cout << "Trigger FIRED" << std::endl;
               } 
               for(auto ts : fTSCallbacks) {
                  ts(t);
               }
            }
            bool IsTriggered() const { return fTriggered; }

            void AddTSCallback( std::function<void(double)> f ){ fTSCallbacks.push_back(f); }

            ClassDef(Trigger,1)
      };



      /** Trigger Supervisor (TS).
       */
      class TriggerSupervisor : public TObject {

         private:
            bool                  fInhibit;
            std::vector<Trigger>  fTriggers;

            std::vector< std::function<void(double)> > fTimingCallbacks;
            std::vector< std::function<int()> >        fReadoutCallbacks;

         public:

            TriggerSupervisor() : fInhibit(false) { }
            virtual ~TriggerSupervisor() { }

            void Print(Option_t * opt = "") const override;

            void Fire(double t) {
               for(auto ts : fTimingCallbacks) {
                  ts(t);
               }
               std::cout << "TS Fired, readout at " << t << std::endl;
            }

            void Readout() {
               for(auto c : fReadoutCallbacks) {
                  c();
               }
            }

            void AddTrigger(const Trigger& trig) {
               fTriggers.push_back(trig);
               Trigger& atrig = fTriggers.back();
               atrig.AddTSCallback( [this](double t){this->Fire(t); } );
            }

            Trigger * GetTrigger(int i) { return &fTriggers[i]; }
            std::vector<Trigger>&  Triggers() { return fTriggers; }


            ClassDef(TriggerSupervisor,1)
      };

   }
}

#endif

