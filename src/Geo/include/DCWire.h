#ifndef clas12_geo_DCWire_HH
#define clas12_geo_DCWire_HH 1

#include "TNamed.h"
#include "TBrowser.h"
#include "TMath.h"
#include "CLHEP/Vector/TwoVector.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "CLHEP/Vector/Rotation.h"
#include <array>

//______________________________________________________________________________

namespace clas12 {

   namespace geo {

      const double  inch = 2.54*CLHEP::cm;

      CLHEP::Hep2Vector ApplyRotation(CLHEP::Hep2Vector v, double angle);


      class DCWire {

         public :
            int  fSector;
            int  fRegion;
            int  fSuperLayer;   // redundant information Region I: (1,2), Region II: (3,4) R III: (5,6)
            int  fLayer;
            int  fWire;       

            DCWire(int sec=0, int reg=0, int sl=0, int l=0, int w=0);
            virtual ~DCWire();

            void Print(Option_t * opt = "") const;

            ClassDef(DCWire,1)
      };
      //________________________________________________________________________

      namespace DC {

         using namespace CLHEP;
         using namespace TMath;

         // The parameters below can be found in:
         // https://clasweb.jlab.org/wiki/images/d/d1/Dc12geom_doc.pdf 
         // all extra parameters come from the drawings found at 
         // https://userweb.jlab.org/~cwiggins/

         const std::array<double,3> FrontGap      = {2.500*cm, 2.5000*cm, 2.5*cm};
         const std::array<double,3> MidGap        = {2.500*cm, 7.1613*cm, 2.5*cm};
         const std::array<double,3> BackGap       = {2.500*cm, 2.5000*cm, 2.5*cm};

         //const std::array<double,3> RegionWidth   = {59.0*degree, 60.0*degree, 59.0*degree};

         const std::array<double,3> EndPlateAngle = {59.0*degree, 60.0*degree, 59.0*degree};
         const std::array<double,3> RegionTilt    = {25.0*degree, 25.0*degree, 25.0*degree};

         const std::array<double,3> RegionXOffset = {
            8.298*cm, 20.296*cm, 18.054*cm
         };

         const std::array<double,6> SectorRotation = {
             90.0*degree, 150.0*degree, 210.0*degree,
             270.0*degree, 330.0*degree, 30.0*degree
         };

         const std::array<int,6> SuperLayerRegion      = { 1,1,2,2,3,3 };
         const std::array<int,6> SuperLayerRegionIndex = { 0,0,1,1,2,2 };

         const std::array<std::array<int,2>,3> RegionSuperLayers = { 
            std::array<int,2>{1,2}, 
            std::array<int,2>{3,4}, 
            std::array<int,2>{5,6} };

         const std::array<std::array<int,2>,3> RegionSuperLayerIndex = { 
            std::array<int,2>{0,1}, 
            std::array<int,2>{2,3}, 
            std::array<int,2>{4,5} };

         const std::array<double,6> ThetaStero = {
            6.0*degree, -6.0*degree,
            6.0*degree, -6.0*degree,
            6.0*degree, -6.0*degree
         };
         const std::array<double,6> ThetaMin = {
            4.694*degree,  4.495*degree,
            4.812*degree, 4.771*degree,
            4.333*degree, 4.333*degree
         };

         const std::array<double,6> LayerSep = {
            0.3861*cm, 0.4042*cm,
            0.6219*cm, 0.6586*cm,
            0.9351*cm, 0.9780*cm
         };
         const std::array<double,6> LayerWireSpacing = {
            2.0*TMath::Sqrt(3.0)*LayerSep.at(0), 2.0*TMath::Sqrt(3.0)*LayerSep.at(1),
            2.0*TMath::Sqrt(3.0)*LayerSep.at(2), 2.0*TMath::Sqrt(3.0)*LayerSep.at(3),
            2.0*TMath::Sqrt(3.0)*LayerSep.at(4), 2.0*TMath::Sqrt(3.0)*LayerSep.at(5)
         };
         const std::array<double,6> LayerWirePlaneLength = {
            113.0*LayerWireSpacing.at(0), 113.0*LayerWireSpacing.at(1),
            113.0*LayerWireSpacing.at(2), 113.0*LayerWireSpacing.at(3),
            113.0*LayerWireSpacing.at(4), 113.0*LayerWireSpacing.at(5)
         };

         // Distance from target to first wire plane in super layer
         // This we call center 
         const std::array<double,6> DistanceToTarget = {
            228.078*cm, 238.687*cm,
            351.544*cm, 371.773*cm,
            489.099*cm, 511.236*cm
         };

         const std::array<double,6> SuperLayerXOffset = {
            8.298*cm,  8.298*cm, 
            14.296*cm, 14.296*cm,
            18.054*cm, 18.054*cm
         };

         // Width of superlayer from front to back gaurd wires  
         const std::array<double,6> SuperLayerWidth = {
            21.0*LayerSep.at(0), 21.0*LayerSep.at(1), 
            21.0*LayerSep.at(2), 21.0*LayerSep.at(3),
            21.0*LayerSep.at(4), 21.0*LayerSep.at(5)
         };

         // offset of first superlayer from front window for given region.
         const std::array<double,6> SuperLayerZOffset = {
            FrontGap.at(0) + 1.5*LayerSep.at(0), 
            FrontGap.at(0) + SuperLayerWidth.at(0) + MidGap.at(0)+1.5*LayerSep.at(1),
            FrontGap.at(1) + 3.5*LayerSep.at(2), 
            FrontGap.at(1) + SuperLayerWidth.at(2) + MidGap.at(1)+1.5*LayerSep.at(3),
            FrontGap.at(2) + 1.5*LayerSep.at(4), 
            FrontGap.at(2) + SuperLayerWidth.at(4) + MidGap.at(2)+1.5*LayerSep.at(5)
         };


         // Distance from target to first guard wire (at ThetaMin)
         const std::array<double,6> CenterToRefWire = {
            DistanceToTarget.at(0)*Tan( RegionTilt.at(0) - ThetaMin.at(0) ),
            DistanceToTarget.at(1)*Tan( RegionTilt.at(0) - ThetaMin.at(1) ),
            DistanceToTarget.at(2)*Tan( RegionTilt.at(1) - ThetaMin.at(2) ),
            DistanceToTarget.at(3)*Tan( RegionTilt.at(1) - ThetaMin.at(3) ),
            DistanceToTarget.at(4)*Tan( RegionTilt.at(2) - ThetaMin.at(4) ),
            DistanceToTarget.at(5)*Tan( RegionTilt.at(2) - ThetaMin.at(5) )
         };

         // Distance from first guard wire (at ThetaMin) to target 
         const std::array<double,6> DistanceToRefWire = {
            Sqrt( Power(DistanceToTarget.at(0),2.0) +  Power(CenterToRefWire.at(0),2.0) ),
            Sqrt( Power(DistanceToTarget.at(1),2.0) +  Power(CenterToRefWire.at(1),2.0) ),
            Sqrt( Power(DistanceToTarget.at(2),2.0) +  Power(CenterToRefWire.at(2),2.0) ),
            Sqrt( Power(DistanceToTarget.at(3),2.0) +  Power(CenterToRefWire.at(3),2.0) ),
            Sqrt( Power(DistanceToTarget.at(4),2.0) +  Power(CenterToRefWire.at(4),2.0) ),
            Sqrt( Power(DistanceToTarget.at(5),2.0) +  Power(CenterToRefWire.at(5),2.0) )
         };

         // Offset in the end-plate coordinates (tilted)
         const std::array<CLHEP::Hep2Vector,6> RefWireOffset = {
            Hep2Vector( Cos(RegionTilt.at(0))*(DistanceToRefWire.at(0)*Sin( ThetaMin.at(0) ) - SuperLayerXOffset.at(0)),
                        Sin(RegionTilt.at(0))*(DistanceToRefWire.at(0)*Sin( ThetaMin.at(0) ) - SuperLayerXOffset.at(0)) ),
            Hep2Vector( Cos(RegionTilt.at(0))*(DistanceToRefWire.at(1)*Sin( ThetaMin.at(1) ) - SuperLayerXOffset.at(1)),
                        Sin(RegionTilt.at(0))*(DistanceToRefWire.at(1)*Sin( ThetaMin.at(1) ) - SuperLayerXOffset.at(1)) ),
            Hep2Vector( Cos(RegionTilt.at(1))*(DistanceToRefWire.at(2)*Sin( ThetaMin.at(2) ) - SuperLayerXOffset.at(2)),
                        Sin(RegionTilt.at(1))*(DistanceToRefWire.at(2)*Sin( ThetaMin.at(2) ) - SuperLayerXOffset.at(2)) ),
            Hep2Vector( Cos(RegionTilt.at(1))*(DistanceToRefWire.at(3)*Sin( ThetaMin.at(3) ) - SuperLayerXOffset.at(3)),
                        Sin(RegionTilt.at(1))*(DistanceToRefWire.at(3)*Sin( ThetaMin.at(3) ) - SuperLayerXOffset.at(3)) ),
            Hep2Vector( Cos(RegionTilt.at(2))*(DistanceToRefWire.at(4)*Sin( ThetaMin.at(4) ) - SuperLayerXOffset.at(4)),
                        Sin(RegionTilt.at(2))*(DistanceToRefWire.at(4)*Sin( ThetaMin.at(4) ) - SuperLayerXOffset.at(4)) ),
            Hep2Vector( Cos(RegionTilt.at(2))*(DistanceToRefWire.at(5)*Sin( ThetaMin.at(5) ) - SuperLayerXOffset.at(5)),
                        Sin(RegionTilt.at(2))*(DistanceToRefWire.at(5)*Sin( ThetaMin.at(5) ) - SuperLayerXOffset.at(5)) )
         };


         const std::array<double,6> LeftFeedThruOffset = {
            0.4745*cm, 0.5254*cm,
            0.0282*cm, 0.0789*cm,
            0.4745*cm, 0.5254*cm
         };

         const std::array<double,6> RightFeedThruOffset = {
            0.5254*cm, 0.4745*cm,
            0.0789*cm, 0.0282*cm,
            0.5254*cm, 0.4745*cm
         };
         //_____________________________________________________________________
         // Nose piece dimensions (width inside gas volue)
         // and width outside the gas volume (nearest to beam)
         const std::array<double,3> NoseWidthInside  = { 
            4.25*2.54*cm, 
            20.7467*cm,
            20.7467*cm
         };
         const std::array<double,3> NoseWidthOutside = {
            1.987*2.54*cm,
            12.1260*cm,
            12.1260*cm
         };

         // the depth along z in the untilted frame
         const std::array<double,3> NoseDepth = {
            (12.405 - 2.0*Tan(RegionTilt.at(0)) + (1.547*Tan(RegionTilt.at(0))-0.311) )*2.54*cm,
            25.419*2.54*cm,
            23.419*2.54*cm  // from drawing 01-10-0201
         };
         const std::array<double,3> NoseHeight = {
            2.0*2.54*cm,
            3.0*2.54*cm,
            3.0*2.54*cm
         };
         const std::array<double,3> NoseTiltShift = {
            NoseHeight.at(0)*Tan(RegionTilt.at(0)), 
            NoseHeight.at(1)*Tan(RegionTilt.at(1)), 
            NoseHeight.at(2)*Tan(RegionTilt.at(2))
         };
         // Opening shift is the x length looking down beam pipe
         const std::array<double,3> NoseOpeningShift = {
            NoseHeight.at(0)*Tan(EndPlateAngle.at(0)/2.0), 
            NoseHeight.at(1)*Tan(EndPlateAngle.at(1)/2.0), 
            NoseHeight.at(2)*Tan(EndPlateAngle.at(2)/2.0)
         };
         const std::array<double,3> NoseSideLength = {
            Sqrt(NoseHeight.at(0)*NoseHeight.at(0)+ 
                        NoseTiltShift.at(0)*NoseTiltShift.at(0)+
                        NoseOpeningShift.at(0)*NoseOpeningShift.at(0) ),
            Sqrt(NoseHeight.at(1)*NoseHeight.at(1)+ 
                        NoseTiltShift.at(1)*NoseTiltShift.at(1)+
                        NoseOpeningShift.at(1)*NoseOpeningShift.at(1) ),
            Sqrt(NoseHeight.at(2)*NoseHeight.at(2)+
                        NoseTiltShift.at(2)*NoseTiltShift.at(2)+
                        NoseOpeningShift.at(2)*NoseOpeningShift.at(2) )
         };
         const std::array<double,3> NoseEndPlateAngle = {
            90*degree-(Hep3Vector(NoseTiltShift.at(0), NoseOpeningShift.at(0), NoseHeight.at(0)).angle(
                                   Hep3Vector(0.0, NoseOpeningShift.at(0), NoseHeight.at(0))) ),
            90*degree-(Hep3Vector(NoseTiltShift.at(1), NoseOpeningShift.at(1), NoseHeight.at(1)).angle(
                                   Hep3Vector(0.0, NoseOpeningShift.at(1), NoseHeight.at(1))) ),
            90*degree-(Hep3Vector(NoseTiltShift.at(2), NoseOpeningShift.at(2), NoseHeight.at(2)).angle(
                                   Hep3Vector(0.0, NoseOpeningShift.at(2), NoseHeight.at(2))) )
         };
         const std::array<double,3> NoseToEndPlateRotationAngle = {
            -(Hep3Vector(NoseTiltShift.at(0), NoseOpeningShift.at(0), NoseHeight.at(0)).angle(
                                   Hep3Vector(0.0, NoseOpeningShift.at(0), NoseHeight.at(0))) ),
            -(Hep3Vector(NoseTiltShift.at(1), NoseOpeningShift.at(1), NoseHeight.at(1)).angle(
                                   Hep3Vector(0.0, NoseOpeningShift.at(1), NoseHeight.at(1))) ),
            -(Hep3Vector(NoseTiltShift.at(2), NoseOpeningShift.at(2), NoseHeight.at(2)).angle(
                                   Hep3Vector(0.0, NoseOpeningShift.at(2), NoseHeight.at(2))) )
         };

         // Ref Locations (below) in the non-tilted nose-plate plane (as in 01-10-0201)
         const std::array<double,3> NoseRefLocation_Y = {
            0.375*2.54*cm,
            NoseSideLength.at(1)*Sin(NoseEndPlateAngle.at(1)) - (2.265*2.54*cm),
            NoseSideLength.at(2)*Sin(NoseEndPlateAngle.at(2)) - (2.265*2.54*cm)
         };
         const std::array<double,3> NoseRefLocation_X = {
            NoseDepth.at(0) - (22.586*2.54*cm),
            NoseDepth.at(1) - (22.586*2.54*cm),
            NoseDepth.at(2) - (22.586*2.54*cm)
         };
         const std::array<Hep2Vector,3> NoseRefLocation = {
            Hep2Vector(NoseRefLocation_X.at(0), NoseRefLocation_Y.at(0)),
            Hep2Vector(NoseRefLocation_X.at(1), NoseRefLocation_Y.at(1)),
            Hep2Vector(NoseRefLocation_X.at(2), NoseRefLocation_Y.at(2))
         };
         //_____________________________________________________________________
         
         // Now working in x-y plane in tilted endplate coords
         // y is along the wire plane and x is normal to the front window
         //
         // The reference location for the nose to end plate is the closest upstream and to the beam
         // of the three screw locations for the endplate to mount to the nose plate.
         // Note that  the hole placement on the plate side of the 3 screw holes 
         // is asymmetric in drawing 01-10-0201 and 01-08-2001.
         // The end plate coordinate system for the reference point is in the tilted system
         // with the orgin at the nose/plate corner upstream and closest to the beamline 
         //const std::array<double,3> NoseEndPlateRefLocation = {
         //   NoseSideLength 2.265*2.54*
         //};
         const std::array<Hep2Vector,3> NoseEndPlateRefLocation = {
            ApplyRotation(Hep2Vector(NoseRefLocation_X.at(0), NoseRefLocation_Y.at(0)),NoseToEndPlateRotationAngle.at(0)),
            ApplyRotation(Hep2Vector(NoseRefLocation_X.at(1), NoseRefLocation_Y.at(1)),NoseToEndPlateRotationAngle.at(1)),
            ApplyRotation(Hep2Vector(NoseRefLocation_X.at(2), NoseRefLocation_Y.at(2)),NoseToEndPlateRotationAngle.at(2))
         };


         // 
         const std::array<Hep2Vector,3> EndPlateRefLocation_D = {
            NoseEndPlateRefLocation.at(0) + Hep2Vector( -0.280*2.54*cm, 1.655*2.54*cm),
            NoseEndPlateRefLocation.at(1) + Hep2Vector( -0.280*2.54*cm, 1.655*2.54*cm),
            NoseEndPlateRefLocation.at(2) + Hep2Vector( -0.280*2.54*cm, 1.655*2.54*cm)
         };

         const std::array<Hep2Vector,6> EndPlateSLRefWire_Left = {
            EndPlateRefLocation_D.at(0) + Hep2Vector(  1.447*2.54*cm,  0.453*2.54*cm),
            EndPlateRefLocation_D.at(0) + Hep2Vector(  5.710*2.54*cm, -0.588*2.54*cm),
            EndPlateRefLocation_D.at(1) + Hep2Vector(  1.447*2.54*cm,  0.453*2.54*cm),
            EndPlateRefLocation_D.at(1) + Hep2Vector(  5.710*2.54*cm, -0.588*2.54*cm),
            EndPlateRefLocation_D.at(2) + Hep2Vector(  1.447*2.54*cm,  0.453*2.54*cm),
            EndPlateRefLocation_D.at(2) + Hep2Vector(  5.710*2.54*cm, -0.588*2.54*cm)
         };

         const std::array<Hep2Vector,6> EndPlateSLRefWire_Right = {
            EndPlateRefLocation_D.at(0) + Hep2Vector(  1.440*2.54*cm,  1.079*2.54*cm),
            EndPlateRefLocation_D.at(0) + Hep2Vector(  5.717*2.54*cm, -1.221*2.54*cm),
            EndPlateRefLocation_D.at(1) + Hep2Vector(  1.440*2.54*cm,  1.079*2.54*cm),
            EndPlateRefLocation_D.at(1) + Hep2Vector(  5.717*2.54*cm, -1.221*2.54*cm),
            EndPlateRefLocation_D.at(2) + Hep2Vector(  1.440*2.54*cm,  1.079*2.54*cm),
            EndPlateRefLocation_D.at(2) + Hep2Vector(  5.717*2.54*cm, -1.221*2.54*cm)
         };

         // Wire spacing in a layer
         const std::array<double,6> EndPlateWireSpacing_Left = {
            0.565*2.54*cm, 0.658*2.54*cm,
            0.600*2.54*cm, 0.600*2.54*cm,
            0.600*2.54*cm, 0.600*2.54*cm
         };

         const std::array<double,6> EndPlateWireSpacing_Right = {
            0.629*2.54*cm, 0.591*2.54*cm,
            0.700*2.54*cm, 0.700*2.54*cm,
            0.700*2.54*cm, 0.700*2.54*cm
         };

         // Spacing 
         const std::array<double,6> EndPlateLayerSpacing_Left = {
            0.155*2.54*cm, 0.163*2.54*cm,
            0.100*2.54*cm, 0.100*2.54*cm,
            0.100*2.54*cm, 0.100*2.54*cm
         }; 
         const std::array<double,6> EndPlateLayerSpacing_Right = {
            0.155*2.54*cm, 0.163*2.54*cm,
            0.100*2.54*cm, 0.100*2.54*cm,
            0.100*2.54*cm, 0.100*2.54*cm
         };

         // vector to a wire in the next wire layer with the wire being above the current(in +y)
         const std::array<Hep2Vector,6> EndPlateLayerTranslate1_Right = {
            Hep2Vector(0.155*2.54*cm, 0.336*2.54*cm),
            Hep2Vector(0.163*2.54*cm, 0.309*2.54*cm),
            Hep2Vector(0.155*2.54*cm, 0.336*2.54*cm),
            Hep2Vector(0.163*2.54*cm, 0.309*2.54*cm),
            Hep2Vector(0.155*2.54*cm, 0.336*2.54*cm),
            Hep2Vector(0.163*2.54*cm, 0.309*2.54*cm)
         };
         const std::array<Hep2Vector,6> EndPlateLayerTranslate2_Right = {
            Hep2Vector(2.0*0.155*2.54*cm, 0.042*2.54*cm),
            Hep2Vector(2.0*0.163*2.54*cm, 0.026*2.54*cm),
            Hep2Vector(2.0*0.155*2.54*cm, 0.042*2.54*cm),
            Hep2Vector(2.0*0.163*2.54*cm, 0.042*2.54*cm),
            Hep2Vector(2.0*0.155*2.54*cm, 0.042*2.54*cm),
            Hep2Vector(2.0*0.163*2.54*cm, 0.042*2.54*cm)
         };

         const std::array<double,3> EndPlateLongSideLength  = {
            81.305 *2.54*cm,
            319.2000*cm,      // Wrong
            478.00*cm         // Wrong
         };
         const std::array<double,3> EndPlateShortSideLength = {
            (80.130-4.468)*2.54*cm,
            306.5281*cm,      // Wrong
            437.00*cm         // Wrong
         };

      }
      //________________________________________________________________________

      CLHEP::HepRotation             LayerWireRotation(int sl);
      CLHEP::Hep3Vector              ToWireMidPlane(int sl, int layer, int wire);

      std::vector<CLHEP::Hep2Vector> RegionTrapPoints(int region);
      double                         RegionTrapWidth(int region);
      double                         RegionTrapOffset(int region);
      double                         RegionTrapCorner_z(int region);
      double                         RegionTrapCorner_y(int region);
      double                         SuperLayerRefWire_z(int sl);
      double                         SuperLayerRefWire_y(int sl);
      CLHEP::HepRotation             RegionRotation(int sec, int region);
      CLHEP::Hep3Vector              RegionTranslation(int sec, int region);
      double  WindowAngle(double th, double th_tilt=25*CLHEP::degree);
   }

}

#endif

