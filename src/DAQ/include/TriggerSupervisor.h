#ifndef CLAS12_TriggerSupervisor_HH
#define CLAS12_TriggerSupervisor_HH

#include "TObject.h"
#include "Trigger.h"

#include <iostream>
#include <vector>
#include <functional>

namespace clas12 {

   namespace DAQ {


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

