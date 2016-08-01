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
   //fMapFileName = ClasDigi_DATA_DIR"/clas12TorusOriginalMap.dat";
   //clas12SolenoidFieldMap.dat  clas12TorusOriginalMap.dat

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

void clas12::mag::ToroidField::ReadMap(const char * opt)
{
   std::string option = opt;
   bool verbose_printing = false;
   if( option.find('v') != std::string::npos ){
      verbose_printing = true;
   }

   if( verbose_printing ) {
      std::cout << "Reading Toroid Field Map : \n";
      std::cout << fMapFileName << std::endl;
   }

   fMapFile.open(fMapFileName.c_str());
   std::string line;

   for(int i = 0;i<20;i++) {

      std::getline(fMapFile, line);
      std::stringstream ss;
      ss << line;
      std::string temp;
      ss >> temp;
      if( verbose_printing ) {
         std::cout << line << "\n";
      }
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
      //if(n_lines < 50) {
      //   std::cout << phi << " " << r << " " << z << " " << Bphi << " " << Br << " " << Bz << "\n";
      //}
   }
   if( verbose_printing ) {
      std::cout << "ToroidField has " << n_lines << " data points\n";
      std::cout << "done reading solenoid field map \n";
      std::cout << " n_phi : " << fBphi.size() << std::endl;
      std::cout << " n_r   : " << fBr.size() << std::endl;
      std::cout << " n_z   : " << fBz.size() << std::endl;
      std::cout << " fStride_phi*fStride_r*fStride_z   : " << fStride_phi*fStride_r*fStride_z << std::endl;
   }
   //fParticles->Clear();
   //fNParticles = 0;
   fMapFile.close();
} 
//______________________________________________________________________________
TVector3 clas12::mag::ToroidField::GetField(const TVector3& v) const
{
   return GetField(v.x(), v.y(), v.z());
}
//______________________________________________________________________________

TVector3 clas12::mag::ToroidField::GetField(double x, double y, double z) const
{
   double Bx = 0.0;
   double By = 0.0;
   double Bz = 0.0;

   TVector3 thePositionVector(x,y,z);

   double phi = thePositionVector.Phi() - 0.0*CLHEP::degree;

   double zz   = z;                      // cm
   double rr   = TMath::Sqrt(x*x + y*y); // cm
   double pphi = phi/CLHEP::degree;//(phi + 2.0*CLHEP::pi)/CLHEP::degree; 
   int    nPhi = 0.0;//(int(pphi+30)/60);

   if( pphi < 0 ) pphi += 360.0; 
   while( pphi > 30.0 ){
      pphi -= 60.0;
      nPhi++;
   }

   //pphi = pphi - nPhi*60.0;
   //nPhi = nPhi%6;

   // z    -> i, 
   // r    -> j
   // phi  -> k

   double sign = 1.0;
   double pp   = pphi;

   //std::cout << pphi << std::endl;
   //std::cout << nPhi << std::endl;

   if( (pphi > -fphi_max ) && (pphi <=fphi_max) 
         && (zz >= fz_min) && (zz < fz_max) 
         && (rr >= fr_min) && (rr < fr_max) ) {

      if( pphi < 0.0 ) {
         sign = -1.0;
         pp = TMath::Abs(pphi);
      }
      // Fix the problem when the value is at the upper limit
      if( pp == fphi_max ) pp -= 0.000001;

      int ii = (int)TMath::Floor((zz + fz_offset)/fDelta_z);
      int jj = (int)TMath::Floor((rr + fr_offset)/fDelta_r);
      int kk = (int)TMath::Floor((pp + fphi_offset)/fDelta_phi);

      // get interpolated Bz value
      int k0 = (ii)   + fStride_z*jj     + fStride_z*fStride_r*kk;
      int k1 = (ii+1) + fStride_z*jj     + fStride_z*fStride_r*kk;
      int k2 = (ii+1) + fStride_z*(jj+1) + fStride_z*fStride_r*kk;
      int k3 = (ii)   + fStride_z*(jj+1) + fStride_z*fStride_r*kk;
      int k4 = (ii)   + fStride_z*jj     + fStride_z*fStride_r*(kk+1);
      int k5 = (ii+1) + fStride_z*jj     + fStride_z*fStride_r*(kk+1);
      int k6 = (ii+1) + fStride_z*(jj+1) + fStride_z*fStride_r*(kk+1);
      int k7 = (ii)   + fStride_z*(jj+1) + fStride_z*fStride_r*(kk+1);

      //check
      //std::cout << fz.at(k0) << " < " << zz << " < " << fz.at(k1) << std::endl;
      //std::cout << fr.at(k1) << " < " << rr << " < " << fr.at(k2) << std::endl;
      //std::cout << fphi.at(k3) << " < " << pp << " < " << fphi.at(k4) << std::endl;

      std::array<double,6> corners  = {fz.at(k0), fz.at(k1), fr.at(k1), fr.at(k2), fphi.at(k3), fphi.at(k4)};

      std::array<double,8> cornerBz = {fBz.at(k0), fBz.at(k1), fBz.at(k2), fBz.at(k3), fBz.at(k4), fBz.at(k5), fBz.at(k6), fBz.at(k7)};
      double interpBz = clas12::mag::TrilinearInterpolation(cornerBz, corners, zz , rr, pp);

      std::array<double,8> cornerBr = {fBr.at(k0), fBr.at(k1), fBr.at(k2), fBr.at(k3), fBr.at(k4), fBr.at(k5), fBr.at(k6), fBr.at(k7)};
      double interpBr = clas12::mag::TrilinearInterpolation(cornerBr, corners, zz , rr, pp);

      std::array<double,8> cornerBphi = {fBphi.at(k0), fBphi.at(k1), fBphi.at(k2), fBphi.at(k3), fBphi.at(k4), fBphi.at(k5), fBphi.at(k6), fBphi.at(k7)};
      double interpBphi = clas12::mag::TrilinearInterpolation(cornerBphi, corners, zz , rr, pp);

      interpBz    *= 0.1; // kG->T
      interpBr    *= 0.1; // kG->T
      interpBphi  *= 0.1; // kG->T

      double extra_rot = 0.0*CLHEP::degree;

      //std::cout << " pp   " << pp << "\n";
      //std::cout << " pphi " << pphi << "\n";
      //std::cout << " phi_k3 " << fphi.at(k3) << "\n";
      //std::cout << " phi_k4 " << fphi.at(k4) << "\n";

      //TVector3 theField(
      //      sign*interpBr*TMath::Cos(pp*CLHEP::degree) - interpBphi*TMath::Sin(pp*CLHEP::degree), 
      //      sign*interpBr*TMath::Sin(pp*CLHEP::degree) + interpBphi*TMath::Cos(pp*CLHEP::degree), 
      //      sign*interpBz);

      TVector3 theField(
                       sign*interpBr*TMath::Sin(0.0*CLHEP::degree) + interpBphi*TMath::Cos(0.0*CLHEP::degree), 
                       sign*interpBr*TMath::Cos(0.0*CLHEP::degree) - interpBphi*TMath::Sin(0.0*CLHEP::degree), 
                       sign*interpBz );

      if( sign == -1.0 ) {
      //   //extra_rot = (30.0+pp)*CLHEP::degree;
      //   //theField.RotateZ(extra_rot);

      //   extra_rot = 60.0*CLHEP::degree + 2.0*pp*CLHEP::degree;
      theField = TVector3(
                       -1.0*(sign*interpBr*TMath::Sin(0.0*CLHEP::degree) + interpBphi*TMath::Cos(0.0*CLHEP::degree)), 
                       -1.0*(sign*interpBr*TMath::Cos(0.0*CLHEP::degree) - interpBphi*TMath::Sin(0.0*CLHEP::degree)), 
                       -1.0*sign*interpBz );

      //   theField.SetXYZ(sign*theField.X(),
      //                        theField.Y(),
      //                   sign*theField.Z() );
      //////   theField.RotateZ( (30.0+pp)*CLHEP::degree);
      }

      theField.RotateZ( (double(nPhi))*60.0*CLHEP::degree + extra_rot );

      Bx = theField.X();// * fScalingCoefficient;
      By = theField.Y();// * fScalingCoefficient;
      Bz = theField.Z();// * fScalingCoefficient;

   } else {
      Bx = 0.0;
      By = 0.0;
      Bz = 0.0;
   }
   //std::cout << "x (" << x << ", " << y << ", " << z << ")\n";
   //std::cout << "B (" << Bx << ", " << By << ", " << Bz << ")\n";

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


