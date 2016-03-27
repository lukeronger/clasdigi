#include "GeoUtil.h"

namespace clas12 {

   namespace geo {

      using namespace CLHEP;

      Hep2Vector ApplyRotation(Hep2Vector v, double angle)
      {
         v.rotate(angle);
         return v;
      }
      //______________________________________________________________________________

      Hep3Vector GetIntersectionPoint(
            const Hep3Vector x0, const Hep3Vector x1,
            const Hep3Vector p0, const Hep3Vector norm )
      {
         Hep3Vector w = x0 - p0;
         Hep3Vector u = x1 - x0;
         double si = -1.0*(norm.dot(w)/(norm.dot(u)));
         Hep3Vector sterm = si*u;
         Hep3Vector Psi = p0 + w + sterm  ;
         return Psi;
      }
      //______________________________________________________________________________
   }
}

