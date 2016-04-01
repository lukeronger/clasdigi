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
            int             fPDGCode;        // PDG code of particle.
            int             fTrackID;        // track id.
            double          fTime;
            double          fLambda;

         public: 
            RecoilScintHit();
            virtual ~RecoilScintHit();
            void Print();

            ClassDef(RecoilScintHit,3)
      };

   }

}

#endif

