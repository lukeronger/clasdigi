#include <iostream>
#include <vector>

#include "DCWire.h"

int main( int argc, char **argv )
{
   using namespace clas12::geo;
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

}

