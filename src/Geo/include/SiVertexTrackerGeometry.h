#ifndef clas12_geo_RH_SiVertexTrackerGeometry_H
#define clas12_geo_RH_SiVertexTrackerGeometry_H

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

namespace eic {

   namespace geo {

      //fSolidAbsorber = new G4Box("Absorber", 
      //      fAbsorberDX/2., fAbsorberDY/2., 
      //      //10.*mm,10.*mm,
      //      fAbsorberThickness/2.); 

      //fLogicAbsorber = new G4LogicalVolume(fSolidAbsorber, fAbsorberMaterial, 
      //      "Absorber");     

      //G4RotationMatrix rm[12];
      //G4double phi,deltaphi1,deltaphi,deltashi, x, y, z;
      //deltaphi1=0; deltaphi=30.*deg; phi=0; x=3*cm; y=0*cm; z=0*cm;
      //deltashi=-7.*deg;
      ////phi=26.*deg; x=0; y=0; z=fAbsorberZ;
      ////phi=0.*deg; x=0; y=0; z=fAbsorberZ;

      //for (int ia=0;ia<12;ia++) { 
      //   phi=(ia*(deltaphi));
      //   x=-3*cos(phi)*cm;
      //   y=-3*sin(phi)*cm;
      //   rm[ia].rotateX(-(deltaphi*ia+deltashi));
      //   rm[ia].rotateY(90*deg);

      //   //   rm.rotateX(-(deltaphi*ia+deltashi));  //
      //   //   printf("phi=%d %f %f %f x= %f %f %f \n",ia, phi,cos(phi),sin(phi),x,y,z);
      //   //         rm.rotateX(-(deltaphi*ia+deltashi));
      //   sprintf(abname,"VTX_ladder%d",ia);
      //   fPhysicsAbsorber = new G4PVPlacement(G4Transform3D(rm[ia],G4ThreeVector(x,y,z)),
      //         abname,fLogicAbsorber, 
      //         fPhysicsVTX,false,0.);
      //   //rm.rotateX(+(deltaphi*ia+deltashi));
      //   //   rm.rotateY(-90*deg);
      //   //  rm.rotateX(0);
      //};
      ////=========================================================================
      ////                           slices and pixels
      ////=========================================================================

      //G4double PixelDX=fAbsorberDX/50.; //2000.*um;
      //G4double PixelDY=fAbsorberDY/10.; //2000.*um;
      ////G4double PixelDX=20.*um;
      ////G4double PixelDY=20.*um;
      ////G4double PixelDX=24.*um;
      ////G4double PixelDY=24.*um;
      //G4double PixelDZ=fAbsorberThickness; // 0.450*mm

      //if (FDIV>=1) {
      //   printf("SetUpVertex16():: construct slices \n");

      //   G4Box* pxdBox_slice = new G4Box("pxdSlice",
      //         PixelDX/2,                   //gD->GetPixelDX(),
      //         fAbsorberDY/2., // 10.*mm,  //gD->GetHalfMPXWaferDY(),
      //         fAbsorberThickness/2.);    //gD->GetHalfMPXWaferDZ());
      //   pxdSlice_log = new G4LogicalVolume(pxdBox_slice, fAbsorberMaterial, "pxdSlice",0,0,0);

      //   G4VisAttributes* pixelVisAtt= new G4VisAttributes(G4Color(0,1,1,1));
      //   pixelVisAtt->SetLineWidth(1);
      //   pixelVisAtt->SetForceWireframe(true);
      //   pxdSlice_log->SetVisAttributes(pixelVisAtt);


      //   // divide in slices
      //   G4PVDivision * sliceDiv = new G4PVDivision("pxdSlice",
      //         pxdSlice_log,
      //         fLogicAbsorber,
      //         kXAxis,
      //         PixelDX,
      //         0);
      //   if (FDIV>=2) {

      //      printf("SetUpVertex16():: construct pixels \n");

      //      G4Box* pxdBox_pixel = new G4Box("pxdPixel",
      //            PixelDX/2,
      //            PixelDY/2.,
      //         j   PixelDZ/2.);
      //      pxdPixel_log = new G4LogicalVolume(pxdBox_pixel, fAbsorberMaterial, "pxdPixel",0,0,0);
      //      pxdPixel_log->SetVisAttributes(pixelVisAtt);

      //      // divide in pixels
      //      G4PVDivision * pixelDiv = new G4PVDivision("pxdPixel",
      //            pxdPixel_log,
      //            pxdSlice_log,
      //            kYAxis,
      //            PixelDY,
      //            0);
      //   } //-- end if pixel division 
      //} //-- end if slices division 

      using namespace CLHEP;
      using namespace TMath;
      //using namespace HepGeom;

      /*! SiTrackerPixel.
          Note that the longitudinal and transverse coordinates  are such that
          \hat{T} X \hat{Z} = \hat{r}
       */
      class SiTrackerPixel {

         public:
            int  fLayer;
            int  fLadder;
            int  fTi;      // Transverse pixel number
            int  fZi;      // Longitudinal pixel number
            int  fChannel;

         public:
            SiTrackerPixel() { } 
            SiTrackerPixel(int lay, int lad, int Ti, int Zi) : 
               fLayer(lay), fLadder(lad), fTi(Ti), fZi(Zi), fChannel(0) { }
            SiTrackerPixel(const SiTrackerPixel&) = default;
            SiTrackerPixel(SiTrackerPixel&&)      = default;
            SiTrackerPixel& operator=(const SiTrackerPixel&) = default;
            SiTrackerPixel& operator=(SiTrackerPixel&&)      = default;
            virtual ~SiTrackerPixel() = default;
      };

      /*! Recoil Hodoscope Geometry.
Hi Markus, hi Whitney,

I can't tell you right now how many pixels. That what we should tell after simulation: 
( how large could be a pixel pitch, depending on occupancy and resolution we what to have) 

At the moment I assume that we would have 50x50 um pixel pitch  and 50 um thickness of silicon
Now I have only 3 layers with 10,14, 18 ladders. Each ladder is 2 cm wide and length of 10cm,14cm,18cm
(divided by 50x50 um pixel pitch)
For the placement: 
R- is an innermost radius of placement 3,87cm , 4.87 and 5.87 cm. Each ladder is rotated at 30, 26, 20 degree

1 layer 
    # 12 ladders, R:  3.87 cm, L :10 cm   phi=30 
2 layer  
    # 14 ladders,R: 4.87, L : 14 cm  phi =26
3 layer 
    # 18 ladders,R: 5.87, L :18 cm   phi =20

       */

      class SiVertexTrackerGeometry {
         public:

            int    NLayers        = 3;

            std::array<double,3> fLayerRotation = {{ 30.0*degree/2.0, 26.0*degree/2.0, 20.0*degree/2.0 }};
            std::array<double,3> fLayerRadius   = {{ 3.87*cm, 4.87*cm, 5.87*cm }};
            std::array<double,3> fLayerLength   = {{ 10.0*cm, 14.0*cm, 18.0*cm }};
            std::array<double,3> fLayerWidth    = {{ 2.50*cm, 2.50*cm, 2.50*cm }};
            std::array<int,3>    fLayerNLadders      = {{ 12, 14, 18 }};

            // transverse and longitudinal pixels
            std::array<double,3>   fTPixelPitch      = {{ 50.0*um, 50.0*um, 50.0*um }};
            std::array<double,3>   fZPixelPitch      = {{ 50.0*um, 50.0*um, 50.0*um }};
            std::array<double,3>   fLayerSiThickness = {{ 50.0*um, 50.0*um, 50.0*um }};
            std::array<double,3>   fLayerTotalThickness = {{ 100.0*um, 100.0*um, 100.0*um }};

            // Values below are calculated in constructor:
            std::array<int,3>     fNTPixels   = {{ 0, 0, 0 }};
            std::array<int,3>     fNZPixels   = {{ 0, 0, 0 }};
            std::array<int,3>     fNPixels    = {{ 0, 0, 0 }};
            int                   NChannels;
            int                   NLadders;
            std::array<double,3>  fDeltaPhi   = {{ 0.0, 0.0, 0.0 }};
            std::array<int,3>     fStartLadderNumber  = {{ 0, 0, 0 }};
            std::array<int,3>     fStartChannelNumber  = {{ 0, 0, 0 }};

         public: 
            SiVertexTrackerGeometry();
            void  Print();

            int   GetNChannels() const { return NChannels; }

            int   GetLayerNumberFromLadder(int ladder) const {
               int lad = ladder;
               int lay = 0;
               for(auto n : fLayerNLadders) {
                  if( lad < n ) break;
                  lad -= n;
                  lay++;
               }
               return( lay );
            }

            int   GetLadderNumber(int layer, int lad) const {
               return( fStartLadderNumber.at(layer) + lad );
            }

            int   GetChannelNumber(int ladder, int ti, int zi) const {
               std::cout << "input : " << ladder <<  "  " << ti <<  "  " << zi <<  "  " << std::endl;
               int lay = GetLayerNumberFromLadder(ladder);
               int lad = ladder - fStartLadderNumber.at(lay);
               int res = fStartChannelNumber.at(lay);
               res +=  lad*fNPixels.at(lay);
               res +=  zi*fNTPixels.at(lay);
               res +=  ti;
               return res;
            }

            int   GetLayerNumber(int channel) const {
               int lay = 0;
               for(auto n : fLayerNLadders) {
                  int m = fStartChannelNumber.at(lay) + n*fNPixels.at(lay);
                  if( channel < m ) break;
                  lay++;
               }
               return( lay );
            }
            int   GetLadderNumber(int channel) const {
               int lay = 0;
               int chan = channel;
               for(auto n : fLayerNLadders) {
                  std::cout << " n " << n << std::endl;
                  int mi = fStartChannelNumber.at(lay) + n*fNPixels.at(lay);
                  if( channel < mi ) break;
                  lay++;
                  chan -= n*fNPixels.at(lay);
               }
               std::cout << "ppGetLadderNumber " << chan << std::endl;;
               int lad         = chan /(fNPixels.at(lay));
               //int module_chan = chan%(fNPixels.at(lay));
               return( fStartLadderNumber.at(lay) + lad );
            }

            int   GetTi(int channel) const {
               int lay = 0;
               int chan = channel;
               for(auto n : fLayerNLadders) {
                  int m = fStartChannelNumber.at(lay) + n*fNPixels.at(lay);
                  if( channel < m ) break;
                  lay++;
                  chan -= n*fNPixels.at(lay);
               }
               int lad         = chan/(fNPixels.at(lay));
               int module_chan = chan%(fNPixels.at(lay));
               return( module_chan%(fNTPixels.at(lay)) );
            }

            int   GetZi(int channel) const {
               int lay = 0;
               int chan = channel;
               for(auto n : fLayerNLadders) {
                  int m = fStartChannelNumber.at(lay) + n*fNPixels.at(lay);
                  if( channel < m ) break;
                  lay++;
                  chan -= n*fNPixels.at(lay);
               }
               int lad         = chan/(fNPixels.at(lay));
               int module_chan = chan%(fNPixels.at(lay));
               return( module_chan/(fNTPixels.at(lay)) );
            }

            //double      GetLayerRadius(int layer) const ;
            //double      GetLayerPhi(int layer) const ;
            Hep3Vector  GetChannelPosition(int channel) const ;

            Hep3Vector  GetLayerPosition(int layer, int lad) const ;
            HepRotation GetLayerRotation(int layer, int lad) const ;

            Hep3Vector  GetLadderNorm(int lad) const ;

            Hep3Vector  GetChannelNorm(int channel) const  {
             int lad = GetLadderNumber(channel);
             std::cout << " laddder " << lad << std::endl;
             return GetLadderNorm(lad);
            }
            //Hep3Vector   GetChannelPosition(int channel) const ;
            //Hep3Vector   GetChannelNormal(int channel) const ;
            //double       GetChannelPhi(int channel) const ;
            //double       GetChannelZ(int channel) const ;
            //double       GetChannelRadius(int channel) const ;

            //int        GetWireLayer(int channel) const ;
            //double     GetSenseWireRadius(int channel) const ;
            //double     GetSenseWirePhi(int channel) const ;
            //double     GetSenseWireStereoAngle(int channel) const ;

            //Hep3Vector  GetFirstCellPosition(int layer, int subcell=-1) const ;
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

