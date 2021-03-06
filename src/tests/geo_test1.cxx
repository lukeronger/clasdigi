#include <iostream>
#include <vector>

#include "DCWire.h"

int main( int argc, char **argv )
{
   using namespace clas12::geo;
   using namespace clas12::geo::DC;
   using namespace CLHEP;

   //RegionTrapPoints(1);
   std::vector<CLHEP::Hep2Vector> points = RegionTrapPoints(1);

   std::cout << " RI   length : " << RegionTrapWidth(1) << " cm" << std::endl;
   std::cout << " RII  length : " << RegionTrapWidth(2) << " cm" << std::endl;
   std::cout << " RIII length : " << RegionTrapWidth(3) << " cm" << std::endl;


   std::cout << " NoseHeight.at(0)       : " << DC::NoseHeight.at(0)/inch << std::endl;
   std::cout << " NoseTiltShift.at(0)    : " << DC::NoseTiltShift.at(0)/inch << std::endl;
   std::cout << " NoseSideLength.at(0)   : " << DC::NoseSideLength.at(0)/inch << std::endl;
   std::cout << " NoseOpeningShift.at(0) : " << DC::NoseOpeningShift.at(0)/inch << std::endl;
   std::cout << " NoseHeight.at(0)       : " << DC::NoseHeight.at(0)/inch << std::endl;
   std::cout << " RI nose plate angle    : " << DC::NoseEndPlateAngle.at(0)/CLHEP::degree << " deg" << std::endl;
   std::cout << " NoseRefLocation_X.at(0): " << DC::NoseRefLocation_X.at(0)/inch << std::endl;
   std::cout << " NoseRefLocation_Y.at(0): " << DC::NoseRefLocation_Y.at(0)/inch << std::endl;
   std::cout << " NoseEndPlateRefLocation.at(0).x(): " << DC::NoseEndPlateRefLocation.at(0).x()/inch << std::endl;
   std::cout << " NoseEndPlateRefLocation.at(0).y(): " << DC::NoseEndPlateRefLocation.at(0).y()/inch << std::endl;
   std::cout << "\n";
   std::cout << " EndPlateSLRefWire_Right.at(0).x(): " << DC::EndPlateSLRefWire_Right.at(0).x()/inch << std::endl;
   std::cout << " EndPlateSLRefWire_Right.at(0).y(): " << DC::EndPlateSLRefWire_Right.at(0).y()/inch << std::endl;
   std::cout << "\n";
   std::cout << " EndPlateSLRefWire_Left.at(0).x(): " << DC::EndPlateSLRefWire_Left.at(0).x()/inch << std::endl;
   std::cout << " EndPlateSLRefWire_Left.at(0).y(): " << DC::EndPlateSLRefWire_Left.at(0).y()/inch << std::endl;

   std::cout << "\n";
   std::cout << " EndPlateSLRefWire_Right.at(1).x(): " << DC::EndPlateSLRefWire_Right.at(1).x()/inch << std::endl;
   std::cout << " EndPlateSLRefWire_Right.at(1).y(): " << DC::EndPlateSLRefWire_Right.at(1).y()/inch << std::endl;
   std::cout << "\n";
   std::cout << " EndPlateSLRefWire_Left.at(1).x(): " << DC::EndPlateSLRefWire_Left.at(1).x()/inch << std::endl;
   std::cout << " EndPlateSLRefWire_Left.at(1).y(): " << DC::EndPlateSLRefWire_Left.at(1).y()/inch << std::endl;

   std::cout << " RegionTrapCorner_z(1): " << RegionTrapCorner_z(1)/cm << std::endl;
   std::cout << " RegionTrapCorner_y(1): " << RegionTrapCorner_y(1)/cm << std::endl;

   std::cout << "\n";
   std::cout << " RegionTranslation(1).x(): " << RegionTranslation(1,1).x()/cm << std::endl;
   std::cout << " RegionTranslation(2).x(): " << RegionTranslation(2,1).x()/cm << std::endl;
   std::cout << " RegionTranslation(3).x(): " << RegionTranslation(3,1).x()/cm << std::endl;

   for(int sl = 1;sl<=6;sl++) {
      std::cout << " RefWireOffset.at(sl-1).x(): " << RefWireOffset.at(sl-1).x() << std::endl;
      std::cout << " RefWireOffset.at(sl-1).y(): " << RefWireOffset.at(sl-1).y() << std::endl;
   }
   for(int sl = 1;sl<=6;sl++) {
      std::cout << " CenterToRefWire.at(sl-1): " << CenterToRefWire.at(sl-1)/cm << std::endl;
   }
   for(int sl = 1;sl<=6;sl++) {
      std::cout << " DistanceToRefWire.at(sl-1): " << DistanceToRefWire.at(sl-1)/cm<< std::endl;
   }

   std::cout << ToWireMidPlane(1,1,89) << std::endl; 
   std::cout << ToWireMidPlane(1,1,90) << std::endl; 
   std::cout << ToWireMidPlane(1,1,91) << std::endl; 
   std::cout << ToWireMidPlane(1,2,89) << std::endl; 
   std::cout << ToWireMidPlane(1,2,90) << std::endl; 
   std::cout << ToWireMidPlane(1,2,91) << std::endl; 
}

