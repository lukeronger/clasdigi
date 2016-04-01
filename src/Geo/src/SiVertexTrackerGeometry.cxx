#include "SiVertexTrackerGeometry.h"
#include "TMath.h"
#include <iomanip>
#include <cmath>
#include "CLHEP/Geometry/Transform3D.h"


namespace eic {

   namespace  geo {

      using namespace CLHEP;
      //using namespace HepGeom;

      SiVertexTrackerGeometry::SiVertexTrackerGeometry()
      {
         NChannels = 0;
         NLadders  = 0;

         for(int i = 0; i<NLayers; i++) {
            // need to double check what G4PVDivsion does here
            fNZPixels[i] = std::floor(fLayerLength.at(i)/fZPixelPitch.at(i));
            fNTPixels[i] = std::floor(fLayerWidth.at(i)/fTPixelPitch.at(i));
            fNPixels[i]  = fNZPixels[i]*fNTPixels[i];
            fDeltaPhi[i] = CLHEP::twopi/fLayerNLadders.at(i);

            fStartLadderNumber[i]  = NLadders;
            fStartChannelNumber[i] = NChannels;
            NChannels  += fLayerNLadders.at(i)*fNPixels[i];
            NLadders   += fLayerNLadders.at(i);
         }

      }
      //______________________________________________________________________________

      void SiVertexTrackerGeometry::Print()
      {
         std::cout << "SiVertexTrackerGeometry\n";
         std::cout << "NChannels  " << NChannels  << std::endl;
         std::cout << "NLadders   " << NLadders    << std::endl; 
         for(int i = 0; i<NLayers; i++) {
            std::cout << "fNZPixels[" << i << "]   " << fNZPixels[i] << std::endl;
            std::cout << "fNTPixels[" << i << "]   " << fNTPixels[i]  << std::endl; 
            std::cout << "fNPixels [" << i << "]   " << fNPixels[i]  << std::endl;
            std::cout << "fDeltaPhi[" << i << "]   " << fDeltaPhi[i]  << std::endl; 
         }
         std::cout << "\n";
      }
      //______________________________________________________________________________

      //double   SiVertexTrackerGeometry::GetLayerRadius(int layer) const
      //{
      //   return 
      //}
      //double   SiVertexTrackerGeometry::GetLayerPhi(int layer) const
      //{
      //   return 
      //}
      Hep3Vector   SiVertexTrackerGeometry::GetLayerPosition(int layer, int lad) const 
      {
         if( lad >= fLayerNLadders.at(layer) ) {
            std::cout << "Warning: Ladder number out of range, " << lad << " >= " << fLayerNLadders.at(layer) << std::endl;
         }
         double      phi = fDeltaPhi.at(layer)*double(lad);
         Hep3Vector  res = {fLayerRadius.at(layer),0,0};
         res.rotateZ(phi);
         return res;
      }

      HepRotation SiVertexTrackerGeometry::GetLayerRotation(int layer, int lad) const
      {
         if( lad >= fLayerNLadders.at(layer) ) {
            std::cout << "Warning: Ladder number out of range, " << lad << " >= " << fLayerNLadders.at(layer) << std::endl;
         }
         double       phi = fDeltaPhi.at(layer)*double(lad);
         HepRotation  res = HepRotation::IDENTITY;
         res.rotateZ(phi);
         res.rotateZ(fLayerRotation.at(layer));
         return res;
      }

      Hep3Vector  SiVertexTrackerGeometry::GetLadderNorm(int ladder) const
      {
         std::cout << " SiVertexTrackerGeometry::GetLadderNorm ladder " << ladder <<std::endl;
         int lay = GetLayerNumberFromLadder(ladder);
         int lad = ladder - fStartLadderNumber.at(lay);
         std::cout << " SiVertexTrackerGeometry::GetLadderNorm lay " << lay <<std::endl;
         std::cout << " SiVertexTrackerGeometry::GetLadderNorm start lad " << fStartLadderNumber.at(lay) <<std::endl;
         std::cout << " SiVertexTrackerGeometry::GetLadderNorm lad " << lad <<std::endl;
         double      phi = fDeltaPhi.at(lay)*double(lad);
         Hep3Vector  res = {1,0,0};
         res.rotateZ(phi);
         res.rotateZ(fLayerRotation.at(lay));
         return res;
      }
      //______________________________________________________________________________

      Hep3Vector  SiVertexTrackerGeometry::GetChannelPosition(int channel) const
      {
         int lay = 0;
         int chan = channel;
         for(auto n : fLayerNLadders) {
            int m = fStartChannelNumber.at(lay) + n*fNPixels.at(lay);
            std::cout << m << "  " << fStartChannelNumber.at(lay) <<std::endl;
            if( channel < m ) break;
            lay++;
            chan -= n*fNPixels.at(lay);
            std::cout << chan << "  chan" << std::endl;
         }

         std::cout << " llll "<< std::endl;
         std::cout << " channel " <<  channel << std::endl;
         std::cout << " chan " <<  chan << std::endl;
         int     lad         = chan/(fNPixels.at(lay));
         int     module_chan = chan%(fNPixels.at(lay));
         int     ti          = module_chan%(fNTPixels.at(lay));
         int     zi          = module_chan/(fNTPixels.at(lay));
         double  dt          = fLayerWidth.at(lay)/double(fNTPixels.at(lay));
         double  dz          = fLayerLength.at(lay)/double(fNZPixels.at(lay));
         double  phi         = fDeltaPhi.at(lay)*double(lad);
         std::cout << " module_chan " <<  module_chan << std::endl;
         std::cout << " lad " <<  lad << std::endl;
         std::cout << " lay " <<  lay << std::endl;
         std::cout << " ti  " <<  ti << std::endl;
         std::cout << " zi  " <<  zi << std::endl;
         std::cout << " phi  " <<  phi/CLHEP::degree << std::endl;
         Hep3Vector  res = {
            0,
            -1.0*fLayerWidth.at(lay)/2.0  + (double(ti)+0.5)*dt,
            -1.0*fLayerLength.at(lay)/2.0 + (double(zi)+0.5)*dz
         };
         res.rotateZ(fLayerRotation.at(lay));
         Hep3Vector  res2 = { fLayerRadius.at(lay), 0, 0};
         res += res2;
         res.rotateZ(phi);
         return res;
      }
      //Hep3Vector   SiVertexTrackerGeometry::GetChannelPosition(int channel) const 
      //{
      //   // channels are number starting at zero and the first 10 are along along z then phi
      //   // i_phi*10 + j_z
      //   Hep3Vector res = {GetChannelRadius(channel), 0, GetChannelZ(channel)};
      //   res.rotateZ(GetChannelPhi(channel));
      //   return res;
      //}
      ////______________________________________________________________________________

      //Hep3Vector   SiVertexTrackerGeometry::GetChannelNormal(int channel) const 
      //{
      //   // channels are number starting at zero and the first 10 are along along z then phi
      //   // i_phi*10 + j_z
      //   Hep3Vector res = {1.0, 0, 0};
      //   res.rotateZ(GetChannelPhi(channel));
      //   return res;
      //}

      //double      SiVertexTrackerGeometry::GetChannelPhi(int channel) const 
      //{
      //   int i_phi = channel/NScintZ;
      //   //int j_z   = channel%NScintZ;
      //   return double(i_phi)*fDeltaPhi;
      //}

      //double      SiVertexTrackerGeometry::GetChannelZ(int channel) const 
      //{
      //   //int i_phi = channel/NScintZ;
      //   int j_z   = channel%NScintZ;
      //   return (double(j_z-NScintZ/2)+0.5)*fDeltaZ;
      //}

      //double      SiVertexTrackerGeometry::GetChannelRadius(int channel) const 
      //{
      //   // returns the inner radius of the outer scintillators
      //   return InnerRadius + Scint1Thickness ;
      //}

   }
}
