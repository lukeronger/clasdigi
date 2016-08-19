#ifndef RHHit_HH
#define RHHit_HH 1

#include "TObject.h"
#include "TVector3.h"

namespace clas12 {

  namespace hits {

    class RHHit : public TObject {
      public:
        double fTotalEDepSim;
        double fEDepBarSim;
        double fEDepTileSim;
        double fTotalEDepRecon;
        double fEDepBarRecon;
        double fEDepTileRecon;

        double fRefTime;
        double fTimeBar1;
        double fTimeBar2;
        double fTimeTile;
        double fDeltaT;
        double fSumT;
        double fZ;
        double fPhi;
        double fR;
        double fRatioTileBar;

      public:
        RHHit(){}
        virtual ~RHHit(){}

        //void Clear(Option_t * opt = "");
        //void Print(Option_t * opt = "") const;

      ClassDef(RHHit, 1)
    };

  }

}

#endif
