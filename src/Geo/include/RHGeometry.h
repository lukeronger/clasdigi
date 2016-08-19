#ifndef clas12_geo_RH_RHGeometry_H
#define clas12_geo_RH_RHGeometry_H

#include "TMath.h"
#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "CLHEP/Vector/Rotation.h"
#include "CLHEP/Geometry/Transform3D.h"
#include "GeoUtil.h"
#include <array>
#include <map>
#include <tuple>
#include <unordered_map>

namespace clas12 {

   namespace geo {

      using namespace CLHEP;
      using namespace TMath;
      //using namespace HepGeom;

      /*! Recoil Hodoscope Geometry.
       */
      class RHGeometry {
         public:
            double ScintWrapThickness  =  2.54*0.004*CLHEP::cm; 
            double ScintGap            =  2.54*0.002*CLHEP::cm; 

            double ScintLength         = 30.0*CLHEP::cm;
            double Scint2Length        = 3.0*CLHEP::cm;

            double Scint1Thickness     =  2.0*CLHEP::mm;
            double Scint2Thickness     = 50.0*CLHEP::mm;

            double PhotonDetThickness =  25.4*0.00002*CLHEP::mm;

            double InnerRadius        = 8.0*CLHEP::cm;
            double ScintDeltaTheta    = 6.0*CLHEP::degree; // angle subtended by bar 

            int    NScintZ           = 10;
            int    NScintPhi         = 60 ;
            int    NChannels         = 600 ;

            double  fDeltaPhi;
            double  fDeltaZ;

         public:
            RHGeometry();
            void Print();

            int          GetNChannels() const { return NChannels; }
            Hep3Vector   GetChannelPosition(int channel) const ;
            Hep3Vector   GetChannelNormal(int channel) const ;
            double       GetChannelPhi(int channel) const ;
            double       GetChannelZ(int channel) const ;
            double       GetChannelRadius(int channel) const ;
            double       GetTilePhi(int channel) const;
            double       GetTileZ(int channel) const;
            double       GetTileR(int channel) const;


            //int        GetWireLayer(int channel) const ;
            //double     GetSenseWireRadius(int channel) const ;
            //double     GetSenseWirePhi(int channel) const ;
            //double     GetSenseWireStereoAngle(int channel) const ;

            //Hep3Vector  GetFirstCellPosition(int layer, int subcell=-1) const ;
            //HepRotation GetFirstCellRotation(int layer, int subcell=-1) const ;
            //HepGeom::Transform3D GetFirstCellTransform(int layer, int subcell=-1) const ;

            //Hep3Vector  GetSenseWirePerp(int channel) const ;

            //Hep3Vector  GetSenseWirePosition(int channel) const ;
            //HepRotation GetSenseWireRotation(int channel) const ;
            //HepGeom::Transform3D GetSenseWireTransform(int channel) const ;

            //Hep3Vector GetUpstreamSenseWirePosition(int channel) const ;
            //Hep3Vector GetDownstreamSenseWirePosition(int channel) const ;

            //Hep3Vector GetUnitSubCellPoint(int layer,int subcell, int point) const ;

            //std::vector<Hep2Vector> GetSubCellTrapPoints(int layer, int subcell) ;

      };

   }
}

#endif

