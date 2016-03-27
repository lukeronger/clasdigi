#include "RCGeometry.h"
#include "TMath.h"
#include <iomanip>


namespace clas12 {

   namespace  geo {

      using namespace CLHEP;


      RCGeometry::RCGeometry()
      {
         // Moving radial the structure goes like this:
         // window | gap | field wire | field gap | sense wire | field gap | field wire | gap | field wire ...
         // g fsf g ... g fsf g 
         for(int i = 0; i< NLayers; i++){
            // The inner radius for a given layer of wires
            fCellInnerRadius[i] = (InnerRadius + DeltaR + double(NCellLayers*i)*DeltaR);
            fNCells[i]          = 2.0*int(CLHEP::pi*fCellInnerRadius[i]/MaxWireSep);
            fCellDeltaPhi[i]    = (2.*CLHEP::pi/double(fNCells[i]));
            double sign = 1.0;
            if(i%2==0) sign=1.;
            else sign=-1.;
            fCellStereoAngle[i] = 10.0*sign*CLHEP::degree;
            fCellCentralRadius[i] = fCellInnerRadius[i] + DeltaR;
         }

      }
      //______________________________________________________________________________

      void RCGeometry::Print()
      {
         std::cout << "layer   Radius   cells   delta_phi   stereo"  << std::endl;
         for(int i = 0; i< NLayers; i++){
            std::cout << i << " "
              << fCellInnerRadius[i]/CLHEP::mm << " " 
              << fNCells[i]       << " " 
              << fCellDeltaPhi[i]/CLHEP::degree << " " 
              << fCellStereoAngle[i]/CLHEP::degree << std::endl;
         }
      }
      //______________________________________________________________________________

   }
}


