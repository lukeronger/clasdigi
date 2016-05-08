#include "SolenoidField.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include "TMath.h"
#include "Field.h"
#include "ClasDigiConfig.h"

//______________________________________________________________________________

clas12::mag::SolenoidField::SolenoidField() :
   fDelta_r(0.005), fDelta_z(0.005), fr_min(0.0), fr_max(3.0),     
   fz_min(-3.0), fz_max(3.0),  fStride_r(601), fStride_z(1201),
   fr_offset(0.0), fz_offset(3.0) 
{
   fMapFileName = ClasDigi_DATA_DIR"/clas12SolenoidFieldMap.dat";
   //clas12SolenoidFieldMap.dat  clas12TorusOriginalMap.dat
   //fr_min = 0.0;     // m
   //fr_max = 3.0 ;    // m
   //fz_min = -3.0;    // m
   //fz_max = 3.0;     // m

   std::cout << " fz_min " << fz_min << std::endl;
   std::cout << " fz_max " << fz_max << std::endl;
   std::cout << " fr_min " << fr_min << std::endl;
   std::cout << " fr_max " << fr_max << std::endl;
   std::cout << " fStride_z " << fStride_z << std::endl;
   std::cout << " fStride_r " << fStride_r << std::endl;
   std::cout << " fz_offset " << fz_offset << std::endl;
   std::cout << " fr_offset " << fr_offset << std::endl;


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
   fMapFile.close();
} 
//______________________________________________________________________________

TVector3 clas12::mag::SolenoidField::GetField(const TVector3& v) const
{
   return GetField(v.x(), v.y(), v.z());
}
//______________________________________________________________________________

TVector3 clas12::mag::SolenoidField::GetField(double x, double y, double z) const
{
   double Bx = 0.0;
   double By = 0.0;
   double Bz = 0.0;

   TVector3 thePositionVector(x,y,z);
   //thePositionVector.Print();
   //thePositionVector.RotateY(-fPolarizationAngle);
   double phi = thePositionVector.Phi();

   //fr_min = 0.0;     // m
   //fr_max = 3.0 ;    // m
   //fz_min = -3.0;    // m
   //fz_max = 3.0;     // m
   //fStride_z =  1201;
   //fStride_r =  601;
   //fr_offset = 0.0;
   //fz_offset = 3.0; 

   //Double_t z   = thePositionVector.Z();
   //Double_t r   = thePositionVector.Perp();
   double zz = z/100.0;
   double rr = TMath::Sqrt(x*x + y*y)/100.0; // meters

   //std::cout << " zz " << zz << std::endl;
   //std::cout << " rr " << rr << std::endl;
   //// zz -> i, rr -> j
   //std::cout << " fz_min " << fz_min << std::endl;
   //std::cout << " fz_max " << fz_max << std::endl;
   //std::cout << " fr_min " << fr_min << std::endl;
   //std::cout << " fr_max " << fr_max << std::endl;
   //std::cout << " fStride_z " << fStride_z << std::endl;
   //std::cout << " fStride_r " << fStride_r << std::endl;
   //std::cout << " fz_offset " << fz_offset << std::endl;
   //std::cout << " fr_offset " << fr_offset << std::endl;
   //std::cout << " fDelta_z " << fDelta_z << std::endl;
   //std::cout << " fDelta_r " << fDelta_r << std::endl;

   if( (zz >= fz_min) && (zz < fz_max) && (rr >= fr_min) && (rr < fr_max) ) {
      int ii = (int)TMath::Floor((zz + fz_offset)/fDelta_z);
      int jj = (int)TMath::Floor((rr + fr_offset)/fDelta_r);

      //  std::cout << "jj=" << jj<< " ii =" << ii<< " phi=" << phi*180.0/TMath::Pi() << std::endl;
      //std::cout << "ii " << ii << std::endl;
      //std::cout << "jj " << jj << std::endl;

      //double corners[4] = {ii * 2.0, (ii + 1) * 2.0, jj * 2.0, (jj + 1) * 2.0};

      // get interpolated Bz value
      int k0 = ii     + fStride_z*jj;
      int k1 = (ii+1) + fStride_z*jj;
      int k2 = ii     + fStride_z*(jj+1);
      int k3 = (ii+1) + fStride_z*(jj+1);
      double corners[4] = {fz.at(k0), fz.at(k1), fr.at(k1), fr.at(k2)};

      double cornerDataPoints[4] = {fBz.at(k0), fBz.at(k1), fBz.at(k2), fBz.at(k3)};
      double interpBz = BilinearInterpolation(&cornerDataPoints[0], &corners[0], zz , rr);

      // get interpoolated Br value
      double cornerDataPoints2[4] = {fBr.at(k0), fBr.at(k1), fBr.at(k2), fBr.at(k3)};
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
