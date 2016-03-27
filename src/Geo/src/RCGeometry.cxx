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
            fCellInnerRadius[i] = (InnerRadius + InnerGap + double(i)*(2.0*DeltaR + LayerGap ));
            fNCells[i]          = 2.0*int(CLHEP::pi*fCellInnerRadius[i]/MaxWireSep);
            fCellDeltaPhi[i]    = (2.*CLHEP::pi/double(fNCells[i]));
            double sign = 1.0;
            if(i%2==0) sign=1.;
            else sign=-1.;
            fCellStereoAngle[i] = sign*StereoAngle;
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

      int  RCGeometry::GetWireLayer(int channel) const {
         int res = 0;
         for(auto n: fNCells) {
            if( channel >= n) break;
            res++;
         }  
         return res;
      }
      //______________________________________________________________________________


      double RCGeometry::GetSenseWireRadius(int channel) const {
         int lay = GetWireLayer(channel);
         return fCellCentralRadius.at(lay);
      }
      //______________________________________________________________________________


      double RCGeometry::GetSenseWirePhi(int channel) const {
         int     lay = GetWireLayer(channel);
         int     wire_number = channel - fNCells.at(lay);
         return wire_number*fCellDeltaPhi.at(lay);
      }
      //______________________________________________________________________________


      Hep3Vector RCGeometry::GetSenseWirePosition(int channel) const {
         int     lay = GetWireLayer(channel);
         double  r   = GetSenseWireRadius(channel);
         Hep3Vector res = {0,r,0};
         res.rotateZ(GetSenseWirePhi(channel));
         return res;
      }
      //______________________________________________________________________________


      Hep3Vector RCGeometry::GetUpstreamSenseWirePosition(int channel) const {
         int     lay = GetWireLayer(channel);
         double  r   = GetSenseWireRadius(channel);
         Hep3Vector res = {0,r,-WireLength/2.0};
         res.rotateX(fCellStereoAngle.at(lay));
         res.rotateZ(GetSenseWirePhi(channel));
         return res;
      }
      //______________________________________________________________________________


      Hep3Vector RCGeometry::GetUnitSubCellPoint(int layer,int subcell, int point) const {
         double  r   = fCellInnerRadius.at(layer);
         double phi_sign = -1.0;
         double Lsign = -1.0;
         int    p    = point%4;
         int    up   = point/4;

         if( (p == 1) || (p == 2) ) {
            phi_sign  = 1.0;
         }
         if( p > 1 ) {
            r += DeltaR;
         }
         if( subcell > 1) {
            r += DeltaR;
         }
         if( up > 0 ) {
            Lsign = 1.0;
         }
         Hep3Vector res2 = {0,0,Lsign*WireLength/2.0};
         res2.rotateX( fCellStereoAngle.at(layer)   );
         Hep3Vector res = {r,0,0};
         res += res2;
         res.rotateZ( phi_sign*fCellDeltaPhi.at(layer)/2.0 );
         return( res );
      }
      //______________________________________________________________________________


      std::vector<Hep2Vector> RCGeometry::GetSubCellTrapPoints(int layer, int subcell) {
         std::vector<Hep2Vector>  res;
         for(int i = 0; i <8; i++){
            Hep3Vector p = GetUnitSubCellPoint(layer, subcell, i);
            res.push_back( {p.x(),p.y()} );
         }
         return res;
      }
      //______________________________________________________________________________


   }
}
