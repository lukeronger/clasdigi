#ifndef clas12_hits_ThrownEvent_HH
#define clas12_hits_ThrownEvent_HH 1

#include "TObject.h"
#include <iostream>

#include "TParticle.h"
#include "TClonesArray.h"

namespace clas12 {

   namespace sim {

      class ThrownEvent : public TObject {

         public :
            int       fRunNumber;
            int       fEventNumber;
            int       fNParticles;
            double    fBeamPol; 
            double    fTargetPol; 

            TClonesArray * fParticles; //->

         public :
            ThrownEvent();
            virtual ~ThrownEvent();

            TParticle * AddParticle();
            TParticle * GetParticle(int i);
            int         GetNParticles() const {return fNParticles;}

            virtual void Print(Option_t * opt = "") const ;
            virtual void Clear(Option_t * opt = "") ;

            void ReadLundEvent(   std::ifstream& in);
            int  ReadLundHeader(  std::ifstream& in);
            int  ReadLundParticle(std::ifstream& in);

            //void LundFormat( std::ostream& s = std::cout );
            //void LundHeaderFormat( InSANE_EG_Event& eg_event, std::ostream& s = std::cout) ;
            //void LundEventFormat( int           i, InSANE_EG_Event& eg_event, std::ostream& s = std::cout) ;

            ClassDef(ThrownEvent,2)
      };

   }

}

#endif

