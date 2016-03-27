#ifndef clas12_geo_RH_RCGeometry_H
#define clas12_geo_RH_RCGeometry_H

#include "TMath.h"
#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "CLHEP/Vector/Rotation.h"
#include "GeoUtil.h"
#include <array>
#include <map>
#include <tuple>
#include <unordered_map>

namespace clas12 {

   namespace geo {

      using namespace CLHEP;
      using namespace TMath;

      /*! Recoil Chamber Geometry.
          Numbering conventions:
            - Each "Layer" has NCells number of unit cells
            - Each  unit cell has 1 sense wire and 8 field wires
            - Each  unit cell has 4 sub cells
                     _______ 
                     \__|__/
                      \_|_/
            - These sub cells are given the same copy number in geant4
            - The Field wires surrounding the wire are number going around the wire starting with the inner radius at smallest phi values 
            - Each unit cell has a unique "channel number" starting at 0.

       */
      class RCGeometry {
         public:
            double InnerRadius    = 30.000*mm;
            double OuterRadius    = 79.995*mm;
            double Length         = 30.000*cm;
            double DeltaR         = 2.0*mm;
            int    NLayers        = 8;
            int    NCellLayers    = 3;
            double MaxWireSep     = 2.0*mm; // *desired* wire separation around the circumference. 
            double WireLength     = Length/Cos(10.0*degree);

            std::array<double, 8>   fCellInnerRadius;
            std::array<int   , 8>   fNCells;
            std::array<double, 8>   fCellDeltaPhi;
            std::array<double, 8>   fCellStereoAngle;
            std::array<double, 8>   fCellCentralRadius;

         public:
            RCGeometry();
            void Print();

            int        GetWireLayer(int channel) const {
               int res = 0;
               for(auto n: fNCells) {
                  if( channel >= n) break;
                  res++;
               }  
               return res;
            }

            double GetSenseWireRadius(int channel) const {
               int lay = GetWireLayer(channel);
               return fCellCentralRadius.at(lay);
            }

            double GetSenseWirePhi(int channel) const {
               int     lay = GetWireLayer(channel);
               int     wire_number = channel - fNCells.at(lay);
               return wire_number*fCellDeltaPhi.at(lay);
            }

            Hep3Vector GetSenseWirePosition(int channel) const {
               int     lay = GetWireLayer(channel);
               double  r   = GetSenseWireRadius(channel);
               Hep3Vector res = {0,r,0};
               res.rotateZ(GetSenseWirePhi(channel));
               return res;
            }

            Hep3Vector GetUpstreamSenseWirePosition(int channel) const {
               int     lay = GetWireLayer(channel);
               double  r   = GetSenseWireRadius(channel);
               Hep3Vector res = {0,r,-WireLength/2.0};
               res.rotateX(fCellStereoAngle.at(lay));
               res.rotateZ(GetSenseWirePhi(channel));
               return res;
            }

      };

   }
}

#endif

