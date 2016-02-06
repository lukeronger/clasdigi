#include "DCGeometry.h"
#include "TMath.h"
#include <iomanip>


namespace clas12 {

   namespace  geo {

      using namespace CLHEP;

      Hep2Vector ApplyRotation(Hep2Vector v, double angle)
      {
         v.rotate(angle);
         return v;
      }
      //______________________________________________________________________________

      std::vector<Hep2Vector> RegionTrapPoints(int region)
      {
         // returns the 8 points defining a trapezoid volume defined by the two 
         // endplates and the front and back windows.
         // The first point is "nose" point were the endplates meet 
         // closest to the z axis and furthest upstream towards the target.
         // The origin of the solid's  coordinate system is this first gaurd wire
         // in the midplane (used to define theta_min).
         using namespace clas12::geo::DC;

         int index = region-1;
         std::vector<Hep2Vector> points;
         if( index < 0 || index >= 3 )
         {
            std::cout << "clas12::geo::RegionTrapPoints(region=" << region << ") : Region out of range\n";
            return  points;
         }
         double RegionLength = RegionDepth(region);

         // The mid plane cross section is a rectangle plus a right triangle. 
         // extra_back is the length of the triangle on the back window plane
         //    ______
         //   /| 
         //  /_|_____ 
         //   e        
         // The line segment above e is extra_back
         double extra_back = RegionLength*TMath::Tan(RegionTilt[index]);

         double l1 = EndPlateShortSideLength[index];
         double l2 = EndPlateLongSideLength[index];

         // This returns the nose angle (between two end plates) for the window when viewed normal to it
         double actual_plate_angle = WindowAngle( EndPlateAngle[index]/2.0 , RegionTilt[index] );

         // nose height cut from triangular tip.
         double nose_width  =  NoseWidthInside[index]/2.0;
         double nose_height =  nose_width/TMath::Tan(EndPlateAngle[index]/2.0);
         //double nose_side   = TMath::Sqrt(nose_width*nose_width + nose_height*nose_height);

         double h1 = l1*TMath::Cos(actual_plate_angle);
         double x1 = l1*TMath::Sin(actual_plate_angle);
         double h2 = l2*TMath::Cos(actual_plate_angle);
         double x2 = l2*TMath::Sin(actual_plate_angle);

         //std::cout << "Rough check : " << extra_back << " vs " << l2-l1 << std::endl;

         Hep2Vector p0(  nose_width, nose_height );
         Hep2Vector p1( -nose_width, nose_height );
         Hep2Vector p2( -x1,  h1);
         Hep2Vector p3(  x1,  h1);

         double dx = extra_back;//RegionLength*TMath::Tan( RegionTilt[index]  );

         Hep2Vector p4(  nose_width, nose_height-dx );
         Hep2Vector p5( -nose_width, nose_height-dx );
         Hep2Vector p6( -x2, h2-dx);
         Hep2Vector p7(  x2, h2-dx);

         points = { p1, p2, p3, p0, p5, p6, p7, p4 };

         return points;
      }
      //______________________________________________________________________________

      double  RegionTrapWidth(int region)
      {

         int index = region-1;
         if( index < 0 || index >= 3 )
         {
            std::cout << "clas12::geo::RegionTrapWidth(region=" << region << ") : Region out of range\n";
            return  0.0;
         }
         using namespace clas12::geo::DC;
         double RegionLength = RegionDepth(region);

         return RegionLength/2.0;
      }
      //______________________________________________________________________________

      double  RegionTrapOffset(int region)
      {
         int index = region-1;
         if( index < 0 || index >= 3 )
         {
            std::cout << "clas12::geo::RegionTrapWidth(region=" << region << ") : Region out of range\n";
            return  0.0;
         }
         double RegionLength = RegionDepth(region);
         return RegionLength/2.0;
      }
      //______________________________________________________________________________

      double RegionTrapCorner_z(int region)
      {
         // coordinate to place the geant4 trap 
         // note this is the front corner of the edge where the endplates would meet
         using namespace clas12::geo::DC;
         int index = region-1;
         double z_sl =  SuperLayerRefWire_z(RegionSuperLayers[index][0]);
         double c = Cos( RegionTilt[index] );
         return( z_sl - FrontGap[index]*c );
      }
      //______________________________________________________________________________

      double RegionTrapCorner_y(int region)
      {
         // coordinate to place the geant4 trap
         // note this is the front corner of the edge where the endplates would meet
         using namespace clas12::geo::DC;
         int index = region-1;
         return( RegionXOffset[index] );
      }
      //______________________________________________________________________________

      double SuperLayerRefWire_z(int sl)
      {
         using namespace clas12::geo::DC;
         int index = sl-1;
         return DistanceToRefWire.at(index)*Cos(ThetaMin.at(index));
      }
      //______________________________________________________________________________

      double SuperLayerRefWire_y(int sl)
      {
         using namespace clas12::geo::DC;
         using namespace TMath; 
         int index = sl-1;
         return DistanceToRefWire.at(index)*Sin(ThetaMin.at(index));
      }
      //______________________________________________________________________________

      HepRotation LayerWireRotation(int sl)
      {
         using namespace clas12::geo::DC;
         HepRotation  rot;
         rot.rotateZ( ThetaStereo[sl-1] );
         return rot;
      }
      //______________________________________________________________________________

      Hep3Vector ToWireMidPlane(int sl, int layer, int wire)
      {
         // Returns vector that translates the midplane location 
         // relative to the refernece which is the upstream vertex of the front window
         // plane. 
         using namespace clas12::geo::DC;
         using namespace CLHEP;

         int index = SuperLayerRegionIndex.at(sl-1);
         double RegionLength = FrontGap[index] + MidGap[index] + BackGap[index];
         RegionLength += 21.0*LayerSep.at( RegionSuperLayerIndex[index][0] ) ;
         RegionLength += 21.0*LayerSep.at( RegionSuperLayerIndex[index][1] ) ;

         double arb_offset = 4*cm;
         int    i = (layer%2);
         double y = arb_offset + (0.5*double(i) + double(wire-1))*LayerWireSpacing[sl-1];
         double z = -RegionLength/2.0;
         z += SuperLayerZOffset.at(sl-1);
         z += double(layer)*3.0*LayerSep[sl-1]; Hep3Vector  vec(   0.0, y, z);
         Hep3Vector  offset(0.0, RefWireOffset.at(sl-1).y(), RefWireOffset.at(sl-1).x());
         vec += offset;
         return vec;
      }
      //______________________________________________________________________________

      double  WireLength(int sl,int layer,int wire)
      {
         // Returns the wire's length
         using namespace clas12::geo::DC;
         using namespace CLHEP;
         using namespace TMath;

         int region = (sl-1)/2 + 1;
         int index  = (sl-1)/2;
         if( index < 0 || index >= 3 )
         {
            std::cout << "clas12::geo::WireLength(region=" << region << ") : Region out of range\n";
            return  0.0;
         }

         Hep3Vector wire_position = ToWireMidPlane(sl,layer,wire);

         //double x       = wire_position.x() // zero
         double y1      = wire_position.y();
         double z_depth = wire_position.z();
         double RegionLength = FrontGap[index] + MidGap[index] + BackGap[index];
         RegionLength += 21.0*LayerSep.at( RegionSuperLayerIndex[index][0] ) ;
         RegionLength += 21.0*LayerSep.at( RegionSuperLayerIndex[index][1] ) ;

         // The mid plane cross section is a rectangle plus a right triangle. 
         // extra_back is the length of the triangle on the back window plane
         //    ______
         //   /| 
         //  /_|_____ 
         //   e        
         // The line segment above e is extra_back
         // coordinate system is normal to the window faces
         //double extra_back = RegionLength*Tan(RegionTilt[index]);
         double y0 = z_depth*Tan(RegionTilt[index]);

         // This returns the nose angle (between two end plates) for the window when viewed normal to it
         double actual_plate_angle = WindowAngle( EndPlateAngle[index]/2.0 , RegionTilt[index] );
         //std::cout << " actual_plate_angle " << actual_plate_angle/CLHEP::degree << std::endl;

         double l_total  = (y1 + y0)*Tan(actual_plate_angle);

         // Now we rotate the wire by the stereo angle.
         double th_stereo = ThetaStereo[sl-1];
         double phi_1     = pi/2.0 - actual_plate_angle - th_stereo;
         double phi_2     = pi/2.0 + actual_plate_angle - th_stereo;

         double w1 = l_total*( Cos(th_stereo) + Sin(th_stereo)/Tan(phi_1) );
         double w2 = l_total*( Cos(th_stereo) + Sin(th_stereo)/Tan(phi_2) );

         return(w1 + w2);
      }
      //______________________________________________________________________________

      double  WireShift(int sl,int layer,int wire)
      {
         // Shift of wire's center, along the wire, due to stereo angle
         using namespace clas12::geo::DC;
         using namespace CLHEP;
         using namespace TMath;

         int region = (sl-1)/2 + 1;
         int index  = (sl-1)/2;
         if( index < 0 || index >= 3 )
         {
            std::cout << "clas12::geo::WireLength(region=" << region << ") : Region out of range\n";
            return  0.0;
         }

         Hep3Vector wire_position = ToWireMidPlane(sl,layer,wire);

         //double x       = wire_position.x() // zero
         double y1      = wire_position.y();
         double z_depth = wire_position.z();
         double RegionLength = RegionDepth(region);

         // The mid plane cross section is a rectangle plus a right triangle. 
         // extra_back is the length of the triangle on the back window plane
         //    ______
         //   /| 
         //  /_|_____ 
         //   e        
         // The line segment above e is extra_back
         // coordinate system is normal to the window faces
         //double extra_back = RegionLength*Tan(RegionTilt[index]);
         double y0 = z_depth*Tan(RegionTilt[index]);

         // This returns the nose angle (between two end plates) for the window when viewed normal to it
         double actual_plate_angle = WindowAngle( EndPlateAngle[index]/2.0 , RegionTilt[index] );
         //std::cout << " actual_plate_angle " << actual_plate_angle/CLHEP::degree << std::endl;

         double l_total  = (y1 + y0)*Tan(actual_plate_angle);

         // Now we rotate the wire by the stereo angle.
         double th_stereo = ThetaStereo[sl-1];
         double phi_1     = pi/2.0 - actual_plate_angle - th_stereo;
         double phi_2     = pi/2.0 + actual_plate_angle - th_stereo;

         double w1 = l_total*( Cos(th_stereo) + Sin(th_stereo)/Tan(phi_1) );
         double w2 = l_total*( Cos(th_stereo) + Sin(th_stereo)/Tan(phi_2) );

         return(w1 - w2);
      }
      //______________________________________________________________________________

      Hep3Vector  WireStereoShift(int sl,int layer,int wire)
      {
         // Shift of wire center along wire due to stereo angle
         using namespace clas12::geo::DC;
         using namespace CLHEP;
         using namespace TMath;

         int region = (sl-1)/2 + 1;
         int index  = (sl-1)/2;
         if( index < 0 || index >= 3 )
         {
            std::cout << "clas12::geo::WireLength(region=" << region << ") : Region out of range\n";
            return  {0.0,0.0,0.0};
         }

         Hep3Vector wire_position = ToWireMidPlane(sl,layer,wire);

         //double x       = wire_position.x() // zero
         double y1      = wire_position.y();
         double z_depth = wire_position.z();
         double RegionLength = RegionDepth(region);

         // The mid plane cross section is a rectangle plus a right triangle. 
         // extra_back is the length of the triangle on the back window plane
         //    ______
         //   /| 
         //  /_|_____ 
         //   e        
         // The line segment above e is extra_back
         // coordinate system is normal to the window faces
         //double extra_back = RegionLength*Tan(RegionTilt[index]);
         double y0 = z_depth*Tan(RegionTilt[index]);

         // This returns the nose angle (between two end plates) for the window when viewed normal to it
         double actual_plate_angle = WindowAngle( EndPlateAngle[index]/2.0 , RegionTilt[index] );
         //std::cout << " actual_plate_angle " << actual_plate_angle/CLHEP::degree << std::endl;

         double l_total  = (y1 + y0)*Tan(actual_plate_angle);

         // Now we rotate the wire by the stereo angle.
         double th_stereo = ThetaStereo[sl-1];
         double phi_1     = pi/2.0 - actual_plate_angle - th_stereo;
         double phi_2     = pi/2.0 + actual_plate_angle - th_stereo;

         double w1 = l_total*( Cos(th_stereo) + Sin(th_stereo)/Tan(phi_1) );
         double w2 = l_total*( Cos(th_stereo) + Sin(th_stereo)/Tan(phi_2) );
         double shift = (w1 - w2)/2.0;
         Hep3Vector res = {shift*Cos(th_stereo),shift*Sin(th_stereo), 0};
         return(res);
      }
      //______________________________________________________________________________

      Hep3Vector  GetLeftEndplatePosition(int sec, int sl)
      {
         using namespace clas12::geo::DC;
         int region = (sl-1)/2 +1;
         Hep3Vector  ref = {0.0, RegionTrapCorner_y(region), RegionTrapCorner_z(region)};
         Hep3Vector  to_endplate_center = {
            0.0,
            EndPlateShortSideLength.at(region-1)/2.0,
            RegionDepth(region)/2.0
         };
         // rotate the 
         to_endplate_center.rotateX(-1.0*RegionTilt.at(region-1));
         Hep3Vector pos = ref + to_endplate_center;
         pos.rotateZ(1.0*EndPlateAngle.at(region-1)/2.0);
         return( SectorZRotation(sec)*pos );
      }
      //______________________________________________________________________________

      Hep3Vector  GetRightEndplatePosition(int sec, int sl)
      {
         using namespace clas12::geo::DC;
         int region = (sl-1)/2 +1;
         Hep3Vector  ref = {0.0, RegionTrapCorner_y(region), RegionTrapCorner_z(region)};
         Hep3Vector  to_endplate_center = {
            0.0,
            EndPlateShortSideLength.at(region-1)/2.0,
            RegionDepth(region)/2.0
         };
         // rotate the 
         to_endplate_center.rotateX(-1.0*RegionTilt.at(region-1));
         Hep3Vector pos = ref + to_endplate_center;
         pos.rotateZ(-1.0*EndPlateAngle.at(region-1)/2.0);
         return( SectorZRotation(sec)*pos );
      }
      //______________________________________________________________________________

      HepRotation SectorZRotation(int sec)
      {
         using namespace clas12::geo::DC;
         HepRotation  rot;
         rot.rotateZ( SectorRotation[sec-1] );
         return rot;
      }
      //______________________________________________________________________________

      HepRotation RegionRotation(int sec, int region)
      {
         using namespace clas12::geo::DC;
         HepRotation  rot;
         rot.rotateX( - RegionTilt[region-1] );
         rot.rotateZ( SectorRotation[sec-1] );
         return rot;
      }
      //______________________________________________________________________________

      Hep3Vector RegionTranslation(int sec, int region)
      {
         using namespace clas12::geo::DC;
         CLHEP::Hep3Vector  vec(
               0.0,
               RegionTrapCorner_y(region),
               RegionTrapCorner_z(region)
               );
         vec.rotateZ( SectorRotation[sec-1] );
         return vec;
      }
      //______________________________________________________________________________

      double  WindowAngle(double th, double th_tilt)
      {
         // The angle of the window where the endplate meets.
         using namespace clas12::geo::DC;
         Hep3Vector Y1(0,1.0,0);
         Hep3Vector X1(1,0,0);
         X1.setRThetaPhi(1.0,90*degree,90*degree - th);
         Hep3Vector dz(0,0,TMath::Tan(th_tilt)) ;
         //std::cout << " Angle between Y and vector is " << X1.angle(Y1)/degree << std::endl;
         Hep3Vector X2  = X1 + dz;
         Hep3Vector Y2  = Y1 + dz;
         //std::cout << " Now angle is " << X2.angle(Y2)/degree << std::endl;
         return X2.angle(Y2);
      }
      //______________________________________________________________________________

      double RegionDepth(int region){
         // Distance from region's front window to its back window in the
         // tilted frame (normal to window)
         using namespace clas12::geo::DC;
         int index = region-1;
         double RegionLength = FrontGap.at(index) + MidGap.at(index) + BackGap.at(index);
         RegionLength += 21.0*LayerSep.at( RegionSuperLayerIndex.at(index).at(0) ) ;
         RegionLength += 21.0*LayerSep.at( RegionSuperLayerIndex.at(index).at(1) ) ;
         return RegionLength;
      }
      //______________________________________________________________________________

   }
}


