#ifndef RecoilScintHit_HH
#define RecoilScintHit_HH 1

#include "TObject.h"
//#include "TLorentzVector.h"
//#include "TMath.h"


namespace clas12 {

   namespace hits {
      
      class RecoilScintHit : public TObject {
         public: 
            int             fChannel;        // Channel number .
            double          fTime;
            double          fLambda;
            int             fPDGCode;        // PDG code of particle.

         public: 
            RecoilScintHit();
            virtual ~RecoilScintHit();
            void Print();

            ClassDef(RecoilScintHit,2)
      };

   }

}

#endif

