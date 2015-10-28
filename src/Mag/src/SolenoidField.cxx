#include "SolenoidField.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include "TMath.h"
#include "Field.h"
#include "ClasDigiConfig.h"

//______________________________________________________________________________

clas12::mag::SolenoidField::SolenoidField():
   fDelta_r(0.005), // m
   fDelta_z(0.005), // m
   fr_min(0.0),     // m
   fr_max(3.0),     // m
   fz_min(-3.0),    // m
   fz_max(3.0),      // m
   fStride_r(601),
   fStride_z(1201),
   fr_offset(0.0),     // m
   fz_offset(3.0)    // m
{
   fMapFileName = ClasDigi_DATA_DIR"/clas12SolenoidFieldMap.dat";
   //clas12SolenoidFieldMap.dat  clas12TorusOriginalMap.dat


   ReadMap();
} 
//______________________________________________________________________________

clas12::mag::SolenoidField::~SolenoidField()
{ } 
//______________________________________________________________________________

void clas12::mag::SolenoidField::Clear(const char * opt)
{
   //fParticles->Clear();
   //fNParticles = 0;
} 
//______________________________________________________________________________

void clas12::mag::SolenoidField::Print(const char * opt) const
{
   //std::cout << " Event : " << fEventNumber <<std::endl;

} 
//______________________________________________________________________________

void clas12::mag::SolenoidField::ReadMap()
{
   std::cout << "Reading Solenoid Field Map : \n";
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

   double r = 0.0;
   double z = 0.0;
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
      ss >> r >> z >> Br >> Bz;
      fr.push_back(r);
      fz.push_back(z);
      fBr.push_back(Br);
      fBz.push_back(Bz);
      //std::cout << r << " " << z << " " << Br << " " << Bz << "\n";
      //if(n_lines > 20) break;
   }
   std::cout << "Field has " << n_lines << " data points\n";


   std::cout << "done reading solenoid field map \n";
   //fParticles->Clear();
   //fNParticles = 0;
} 
//______________________________________________________________________________
TVector3 clas12::mag::SolenoidField::GetField(double x, double y, double z)
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
   double zz = z/100.0;
   double rr = TMath::Sqrt(x*x + y*y)/100.0; // meters

   // zz -> i, rr -> j

   if( (zz >= fz_min) && (zz <= fz_max) && (rr >= fr_min) && (rr <= fr_max) ) {
      int ii = (int)TMath::Floor((zz + fz_offset)/fDelta_z);
      int jj = (int)TMath::Floor((rr + fr_offset)/fDelta_r);
      double phi = thePositionVector.Phi();

      //  std::cout << "jj=" << jj<< " ii =" << ii<< " phi=" << phi*180.0/TMath::Pi() << std::endl;

      //double corners[4] = {ii * 2.0, (ii + 1) * 2.0, jj * 2.0, (jj + 1) * 2.0};
      double corners[4] = {ii * 2.0, (ii + 1) * 2.0, jj * 2.0, (jj + 1) * 2.0};

      // get interpolated Bz value
      int k0 = ii     + fStride_z*jj;
      int k1 = (ii+1) + fStride_z*jj;
      int k2 = ii     + fStride_z*(jj+1);
      int k3 = (ii+1) + fStride_z*(jj+1);
      double cornerDataPoints[4] = {fBz[k0], fBz[k1], fBz[k2], fBz[k3]};
      double interpBz = BilinearInterpolation(&cornerDataPoints[0], &corners[0], zz , rr);

      // get interpoolated Br value
      double cornerDataPoints2[4] = {fBr[k0], fBr[k1], fBr[k2], fBr[k3]};
      double interpBr = BilinearInterpolation(&cornerDataPoints2[0], &corners[0], zz , rr);
      //double cornerDataPoints2[4] = {BrFieldRaw[ii][jj], BrFieldRaw[ii+1][jj], BrFieldRaw[ii][jj+1], BrFieldRaw[ii+1][jj+1] };
      //double interpBr = BilinearInterpolation(&cornerDataPoints2[0], &corners[0], Z, R);

      TVector3 theField(interpBr * TMath::Cos(phi), interpBr * TMath::Sin(phi), interpBz);
      //  theField.setRhoPhiZ(interpBr,phi, interpBz );
      //theField.RotateY(fPolarizationAngle);
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


//printf("field x = %lf, y = %lf, z = %lf ",Bfield[0],Bfield[1],Bfield[2]);


// TURN FIELD OFF - UNCOMMENT
//   Bfield[2] = 0.0;
//   Bfield[1] = 0.0;
//   Bfield[0] = 0.0;
//printf("field x = %lf, y = %lf, z = %lf ",Bfield[0],Bfield[1],Bfield[2]);

//}

//void clas12::mag::SolenoidField::ReadLundEvent(std::ifstream& in)
//{
//   fEventNumber++;
//   Clear();
//   int npart = ReadLundHeader(in);
//   for(int i = 0; i< npart; i++) {
//      ReadLundParticle(in);
//   }
//}
//______________________________________________________________________________

//int clas12::mag::SolenoidField::ReadLundHeader(std::ifstream& in)
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
