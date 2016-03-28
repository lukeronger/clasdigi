#ifndef geo_clas12_GeoUtil_HH
#define geo_clas12_GeoUtil_HH 1

#include "TMath.h"
#include "TVector3.h"
#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "CLHEP/Vector/Rotation.h"

namespace clas12 {

   namespace geo {

      using namespace CLHEP;
      using namespace TMath;

      // rotate a two vector
      Hep2Vector ApplyRotation(Hep2Vector v, double angle);
      Hep3Vector GetIntersectionPoint(
            const Hep3Vector x0, const Hep3Vector x1,
            const Hep3Vector p0, const Hep3Vector norm );

      inline TVector3 Convert(const CLHEP::Hep3Vector& v0)
      {
         return(TVector3(v0.x(),v0.y(),v0.z()));
      }
   }
}

#endif

