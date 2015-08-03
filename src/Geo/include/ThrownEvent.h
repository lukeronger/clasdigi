#ifndef clas12_hits_ThrownEvent_HH
#define clas12_hits_ThrownEvent_HH 1

#include "TObject.h"
#include "TParticle.h"
#include "TClonesArray.h"
#include <iostream>
#include <fstream>

namespace clas12 {

   namespace sim {

      class ThrownEvent : public TObject {

         public :
            int       fRunNumber;
            int       fEventNumber;
            int       fNParticles;
            double    fBeamPol; 
            double    fTargetPol; 

            TClonesArray * fParticles;

         public :
            ThrownEvent();
            virtual ~ThrownEvent();

            TParticle * AddParticle()
            {
               TParticle * part = new( (*fParticles)[fNParticles] ) TParticle();
               fNParticles++;
               return part;
            }

            virtual void Print(Option_t * opt = "") const override;
            virtual void Clear(Option_t * opt = "") override;

            void ReadLundEvent(std::ifstream& in);
            int  ReadLundHeader(std::ifstream& in);
            int  ReadLundParticle(std::ifstream& in);

            //void LundFormat( std::ostream& s = std::cout );
            //void LundHeaderFormat( InSANE_EG_Event& eg_event, std::ostream& s = std::cout) ;
            //void LundEventFormat( int           i, InSANE_EG_Event& eg_event, std::ostream& s = std::cout) ;

            ClassDef(ThrownEvent,1)
      };

   }

}

#endif

