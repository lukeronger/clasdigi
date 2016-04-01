#ifndef clas12_geo_RCWire_HH
#define clas12_geo_RCWire_HH 1

#include "TNamed.h"
#include "TBrowser.h"
#include "TMath.h"
#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "CLHEP/Vector/Rotation.h"
#include <array>
#include <map>
#include <tuple>
#include <unordered_map>
#include "RCGeometry.h"

//______________________________________________________________________________

namespace clas12 {

   namespace geo {

      class RCWire {

         public :
            int  fLayer;   // Layer number
            int  fWire;    // Wire number in layer
            int  fChannel; // Unique channel number

            RCWire(int l=0, int w=0);
            virtual ~RCWire();

            void Print(Option_t * opt = "") const;

            ClassDef(RCWire,3)
      };
      //________________________________________________________________________


   }


}

#endif

