#include "ToroidField.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include "CLHEP/Units/SystemOfUnits.h"
#include "TMath.h"
#include "ClasDigiConfig.h"
#include "Field.h"

//______________________________________________________________________________

clas12::mag::ToroidField::ToroidField() : 
   fDelta_phi(30.0/120),
   fDelta_r(2.0),
   fDelta_z(2.0),
   fphi_min(0.0),  // deg
   fphi_max(30.0), // deg
   fr_min(0.0),    // cm
   fr_max(500.0),    // cm
   fz_min(100.0),   // cm
   fz_max(600.0),    // cm
   fStride_phi(121),
   fStride_r(251),
   fStride_z(251),
   fphi_offset(0.0),
   fr_offset(0.0),
   fz_offset(-100.0)
{
   fMapFileName = ClasDigi_DATA_DIR"/clas12TorusOriginalMap.dat";
   //clas12SolenoidFieldMap.dat  clas12TorusOriginalMap.dat

   ReadMap();
} 
//______________________________________________________________________________

clas12::mag::ToroidField::~ToroidField()
{
} 
//______________________________________________________________________________

void clas12::mag::ToroidField::Clear(const char * opt)
{
} 
//______________________________________________________________________________

void clas12::mag::ToroidField::Print(const char * opt) const
{
} 
//______________________________________________________________________________

void clas12::mag::ToroidField::ReadMap()
{
   std::cout << "Reading Toroid Field Map : \n";
   std::cout << fMapFileName << std::endl;

   fMapFile.open(fMapFileName);
   std::string line;

   for(int i = 0;i<20;i++) {

      std::getline(fMapFile, line);
      std::stringstream ss;
      ss << line;
      std::string temp;
      ss >> temp;
      std::cout << line << "\n";
      if( temp == "</mfield>" ) break;

   }

   double phi = 0.0;
   double r = 0.0;
   double z = 0.0;
   double Bphi = 0.0;
   double Br = 0.0;
   double Bz = 0.0;
   int n_lines = 0;
   while(std::getline(fMapFile, line)) {
      n_lines++;
      std::stringstream ss;
      ss << line;
      //std::string temp;
      //ss >> temp;
      //std::cout << line << "\n";
      ss >> phi >> r >> z >> Bphi >> Br >> Bz;
      fphi.push_back(phi);
      fr.push_back(r);
      fz.push_back(z);
      fBphi.push_back(Bphi);
      fBr.push_back(Br);
      fBz.push_back(Bz);
      //std::cout << phi << " " << r << " " << z << " " << Bphi << " " << Br << " " << Bz << "\n";
      //if(n_lines > 200) break;
   }
   std::cout << "ToroidField has " << n_lines << " data points\n";
   std::cout << "done reading solenoid field map \n";
   //fParticles->Clear();
   //fNParticles = 0;
} 
//______________________________________________________________________________

TVector3 clas12::mag::ToroidField::GetField(double x, double y, double z)
{
   double Bx = 0.0;
   double By = 0.0;
   double Bz = 0.0;

   // To get information on the TVector3 in spherical (rho,phi,theta) or
   // cylindrical (z,r,theta) coordinates, the
   // the member functions Mag() (=magnitude=rho in spherical coordinates), Mag2(),
   // Theta(), CosTheta(), Phi(), Perp() (the transverse component=r in cylindrical coordinates),

   TVector3 thePositionVector(x,y,z);
   //thePositionVector.RotateY(-fPolarizationAngle);

   // Now if we were polarized at 80 degrees and wanted B at zero degrees,
   // We would rotate our position
   // back to polangle=0, interpolate the field. Get the vector.
   // Then rotate the field vector back to 80 degrees

   //Double_t z   = thePositionVector.Z();
   //Double_t r   = thePositionVector.Perp();
   double phi = thePositionVector.Phi();
   std::cout << "phi: "  << phi << std::endl;

   double zz = z;//cm
   double rr = TMath::Sqrt(x*x + y*y); //cm
   double pphi = (phi + 2.0*CLHEP::pi)/CLHEP::degree; 
   std::cout << "pphi: "  << pphi << std::endl;
   int  nPhi = (int(pphi)/60);
   std::cout << "nPhi: "  << nPhi << std::endl;
   pphi = pphi - nPhi*60.0;
   std::cout << "pphi2: "  << pphi << std::endl;
   nPhi = nPhi%6;
   std::cout << "nPhi2: "  << nPhi << std::endl;

   // zz -> i, rr -> j

   double sign = 1.0;
   double pp = pphi;
   if( (pphi >= fphi_min) && (pphi <= 2.0*fphi_max) && (zz >= fz_min) && (zz <= fz_max) && (rr >= fr_min) && (rr <= fr_max) ) {
      if( pphi > fphi_max ) {
         sign = -1.0;
         pp = (60.0-pphi);
      }
      int ii = (int)TMath::Floor((zz + fz_offset)/fDelta_z);
      int jj = (int)TMath::Floor((rr + fr_offset)/fDelta_r);
      int kk = (int)TMath::Floor((pp + fphi_offset)/fDelta_phi);

      //double corners[4] = {ii * 2.0, (ii + 1) * 2.0, jj * 2.0, (jj + 1) * 2.0};
      //double corners[4] = {ii * 2.0, (ii + 1) * 2.0, jj * 2.0, (jj + 1) * 2.0};

      // get interpolated Bz value
      int k0 = (ii)   + fStride_z*jj     + fStride_z*fStride_r*kk;
      int k1 = (ii+1) + fStride_z*jj     + fStride_z*fStride_r*kk;
      int k2 = (ii+1) + fStride_z*(jj+1) + fStride_z*fStride_r*kk;
      int k3 = (ii)   + fStride_z*(jj+1) + fStride_z*fStride_r*kk;
      int k4 = (ii)   + fStride_z*jj     + fStride_z*fStride_r*(kk+1);
      int k5 = (ii+1) + fStride_z*jj     + fStride_z*fStride_r*(kk+1);
      int k6 = (ii+1) + fStride_z*(jj+1) + fStride_z*fStride_r*(kk+1);
      int k7 = (ii)   + fStride_z*(jj+1) + fStride_z*fStride_r*(kk+1);

      std::array<double,6> corners = {fz[k0], fz[k1], fr[k1], fr[k2], fphi[k3], fphi[k4]};

      std::array<double,8> cornerBz = {fBz[k0], fBz[k1], fBz[k2], fBz[k3], fBz[k4], fBz[k5], fBz[k6], fBz[k7]};
      double interpBz = clas12::mag::TrilinearInterpolation(cornerBz, corners, zz , rr, pp);

      std::array<double,8> cornerBr = {fBr[k0], fBr[k1], fBr[k2], fBr[k3], fBr[k4], fBr[k5], fBr[k6], fBr[k7]};
      double interpBr = clas12::mag::TrilinearInterpolation(cornerBr, corners, zz , rr, pp);

      std::array<double,8> cornerBphi = {fBphi[k0], fBphi[k1], fBphi[k2], fBphi[k3], fBphi[k4], fBphi[k5], fBphi[k6], fBphi[k7]};
      double interpBphi = clas12::mag::TrilinearInterpolation(cornerBphi, corners, zz , rr, pp);
      //double cornerDataPoints2[4] = {BrFieldRaw[ii][jj], BrFieldRaw[ii+1][jj], BrFieldRaw[ii][jj+1], BrFieldRaw[ii+1][jj+1] };
      //double interpBr = BilinearInterpolation(&cornerDataPoints2[0], &corners[0], Z, R);

      interpBz    *= 0.1; // kG->T
      interpBr    *= 0.1; // kG->T
      interpBphi  *= 0.1; // kG->T

      TVector3 theField(
            interpBr * TMath::Cos(pp*CLHEP::degree) - interpBphi*TMath::Sin(pp*CLHEP::degree), 
            interpBr * TMath::Sin(pp*CLHEP::degree) + interpBphi*TMath::Cos(pp*CLHEP::degree), 
            interpBz);
      theField.RotateZ(nPhi*60.0*CLHEP::degree);
      Bx = theField.X();// * fScalingCoefficient;
      By = theField.Y();// * fScalingCoefficient;
      Bz = theField.Z();// * fScalingCoefficient;

   } else {
      Bx = 0.0;
      By = 0.0;
      Bz = 0.0;
   }

   return TVector3(Bx,By,Bz);
}

//______________________________________________________________________________
//void clas12::mag::ToroidField::ReadLundEvent(std::ifstream& in)
//{
//   fEventNumber++;
//   Clear();
//   int npart = ReadLundHeader(in);
//   for(int i = 0; i< npart; i++) {
//      ReadLundParticle(in);
//   }
//}
////______________________________________________________________________________
//
//int clas12::mag::ToroidField::ReadLundHeader(std::ifstream& in)
//{
//   std::string line;
//   std::getline(in, line);
//   std::stringstream ss;
//   ss << line;
//
//   // Lund format reference: https://gemc.jlab.org/gemc/Documentation/Entries/2011/3/18_The_LUND_Format.html
//   // Header:
//   // Column    Quantity
//   //   1      Number of particles
//   //   2*     Number of target nucleons
//   //   3*     Number of target protons
//   //   4*     Target Polarization
//   //   5      Beam Polarization
//   //   6*     x
//   //   7*     y
//   //   8*     W
//   //   9*     Q2
//   //   10*    nu
//   int ipart,A,Z;
//
//   ss >> ipart;
//   ss >> A;
//   ss >> Z;
//   ss >> fTargetPol;
//   ss >> fBeamPol;
//   double temp;
//   if(ss.eof()){
//      std::cout << "error: end of sstream\n";
//   }
//   for(int i = 5; i<10; i++) {
//      ss >> temp;
//   }
//   //std::cout << "ipart = " << ipart <<std::endl;
//   return ipart;
//}
////______________________________________________________________________________
//
//int clas12::mag::ToroidField::ReadLundParticle(std::ifstream& in)
//{ 
//   std::string line;
//   std::getline(in, line);
//   std::stringstream ss;
//   ss << line;
//
//   // Lund format reference: https://gemc.jlab.org/gemc/Documentation/Entries/2011/3/18_The_LUND_Format.html
//   // NOTE the vertex is in METERS unlike the website above
//   int iLund, charge, type, pdg, parent, daughter;
//   double px,py,pz, E, mass, vx,vy,vz;
//   TParticle      * part     = AddParticle();
//   //std::cout << fNParticles << " particles\n";
//   //std::cout << line << std::endl;
//
//   ss >> iLund ;
//   ss >> charge;
//   ss >> type;
//   ss >> pdg;
//   ss >> parent;
//   ss >> daughter;
//   ss >> px;
//   ss >> py;
//   ss >> pz;
//   ss >> E;
//   ss >> mass;
//   ss >> vx;
//   ss >> vy;
//   ss >> vz;
//   //if(ss.eof()){
//   //   std::cout << "error: end of sstream\n";
//   //}
//
//   part->SetPdgCode(pdg);
//   part->SetMomentum(px,py,pz,E);
//   part->SetProductionVertex(vx,vy,vz,0.0);
//   //part->Print();
//
//   return iLund;
//}
////______________________________________________________________________________


