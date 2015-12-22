#ifndef PhotonHit_HH
#define PhotonHit_HH 1

#include "TObject.h"
#include "TVector3.h"
//#include "TMath.h"


namespace clas12 {

   namespace hits {
      
      class PhotonHit : public TObject {
         public: 
            int             fChannel;        // Channel number .
            double          fTime;
            double          fLambda;
            double          fEnergy;
            TVector3        fMomentum;
            TVector3        fPosition;

         public: 
            PhotonHit();
            virtual ~PhotonHit();
            void Print();

            ClassDef(PhotonHit,2)
      };

   }

}

#endif

