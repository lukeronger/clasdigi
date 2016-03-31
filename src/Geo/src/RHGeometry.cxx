#include "RHGeometry.h"
#include "TMath.h"
#include <iomanip>
#include "CLHEP/Geometry/Transform3D.h"


namespace clas12 {

   namespace  geo {

      using namespace CLHEP;
      //using namespace HepGeom;

      RHGeometry::RHGeometry()
      {
         fDeltaPhi = 360.0*degree/double(NScintPhi);
         fDeltaZ   = ScintLength/double(NScintZ);
      }
      //______________________________________________________________________________

      void RHGeometry::Print()
      {
      }
      //______________________________________________________________________________

      Hep3Vector   RHGeometry::GetChannelPosition(int channel) const 
      {
         // channels are number starting at zero and the first 10 are along along z then phi
         // i_phi*10 + j_z
         Hep3Vector res = {GetChannelRadius(channel), 0, GetChannelZ(channel)};
         res.rotateZ(GetChannelPhi(channel));
         return res;
      }
      //______________________________________________________________________________

      Hep3Vector   RHGeometry::GetChannelNormal(int channel) const 
      {
         // channels are number starting at zero and the first 10 are along along z then phi
         // i_phi*10 + j_z
         Hep3Vector res = {1.0, 0, 0};
         res.rotateZ(GetChannelPhi(channel));
         return res;
      }

      double      RHGeometry::GetChannelPhi(int channel) const 
      {
         int i_phi = channel/NScintZ;
         //int j_z   = channel%NScintZ;
         return double(i_phi)*fDeltaPhi;
      }

      double      RHGeometry::GetChannelZ(int channel) const 
      {
         //int i_phi = channel/NScintZ;
         int j_z   = channel%NScintZ;
         return (double(j_z-NScintZ/2)+0.5)*fDeltaZ;
      }

      double      RHGeometry::GetChannelRadius(int channel) const 
      {
         // returns the inner radius of the outer scintillators
         return InnerRadius + Scint1Thickness ;
      }

   }
}
