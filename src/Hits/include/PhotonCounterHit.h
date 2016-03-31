#ifndef PhotonCounterHit_HH
#define PhotonCounterHit_HH 1

#include "TObject.h"
#include "TVector3.h"
//#include "TMath.h"


namespace clas12 {

   namespace hits {
      
      class PhotonCounterHit : public TObject {
         public: 
            int             fChannel;
            int             fCount;
            double          fTime;
            double          fLambda;
            double          fEnergy;
            TVector3        fMomentum;
            TVector3        fPosition;

         public: 
            PhotonCounterHit();
            virtual ~PhotonCounterHit();
            PhotonCounterHit(const PhotonCounterHit&) = default;
            PhotonCounterHit(PhotonCounterHit&&)      = default;
            PhotonCounterHit& operator=(const PhotonCounterHit&) = default;
            PhotonCounterHit& operator=(PhotonCounterHit&&)      = default;

            virtual void Print(Option_t * option = "");

            ClassDef(PhotonCounterHit,2)
      };

   }

}

#endif

