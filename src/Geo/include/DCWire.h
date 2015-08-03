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


         const std::array<double,3> EndPlateAngle = {59.0*degree, 60.0*degree, 59.0*degree};
         const std::array<double,3> RegionTilt    = {25.0*degree, 25.0*degree, 25.0*degree};

         const std::array<double,3> RegionXOffset = {7.2664*cm, 17.8603*cm, 18.0536*cm};

         const std::array<double,6> SectorRotation = {
             30.0*degree,  90.0*degree, 150.0*degree,
            210.0*degree, 270.0*degree, 330.0*degree
         };

         const std::array<int,6> SuperLayerRegion      = {1,1,2,2,3,3};
         const std::array<int,6> SuperLayerRegionIndex = {0,0,1,1,2,2};

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
            5.1050*degree, 5.1050*degree,
            4.6661*degree, 4.6661*degree,
            4.6708*degree, 4.6708*degree
         };

         const std::array<double,6> LayerSep = {
            0.3861*cm, 0.4042*cm,
            0.6219*cm, 0.6586*cm,
            0.9351*cm, 0.9780*cm
         };

         const std::array<double,6> DistanceToTarget = {
            228.08*cm, 238.69*cm,
            350.47*cm, 370.47*cm,
            483.23*cm, 505.36*cm
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
         const std::array<double,3> NoseWidthInside  = { 10.7950*cm, 20.7467*cm , 20.7467*cm };
         const std::array<double,3> NoseWidthOutside = { 5.04698*cm, 12.1260*cm , 12.1260*cm };
                                                                  // ^Don't know R2 values
         // the depth along z in the untilted frame
         // from drawing 01-10-0201
         const std::array<double,3> NoseDepth = {
            23.419*2.54*cm,
            23.419*2.54*cm,
            23.419*2.54*cm
         };
         const std::array<double,3> NoseHeight = {
            3.0*2.54*cm,
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
            NoseSideLength.at(0)*Sin(NoseEndPlateAngle.at(0)) - (2.265*2.54*cm),
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

         // The reference locations for the nose to end plate is the closest upstream and to the beam
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

         //_____________________________________________________________________

         const std::array<double,3> EndPlateLongSideLength  = {        81.305 *2.54*cm, 319.2000*cm, 478.00*cm};
         const std::array<double,3> EndPlateShortSideLength = { (80.130-4.468)*2.54*cm, 306.5281*cm, 437.00*cm};
                                                             //          ^WRONG        ^WRONG need to lookup RII and III numbers

      }
      //________________________________________________________________________

      std::vector<CLHEP::Hep2Vector> RegionTrapPoints(int region);
      double                         RegionTrapWidth(int region);
      double                         SuperLayerRefWire_z(int sl);
      double                         SuperLayerRefWire_y(int sl);
      CLHEP::HepRotation             RegionRotation(int sec, int region);
      CLHEP::Hep3Vector              RegionTranslation(int sec, int region);
      double  WindowAngle(double th, double th_tilt=25*CLHEP::degree);
   }

}

#endif

