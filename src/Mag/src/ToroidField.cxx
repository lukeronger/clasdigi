#include "ToroidField.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <fstream>
#include "ClasDigiConfig.h"

//______________________________________________________________________________

clas12::mag::ToroidField::ToroidField() : 
   fDelta_phi(30.0/120),
   fDelta_r(2.0),
   fDelta_z(2.0),
   fphi_min(0.0),  // deg
   fphi_max(30.0), // deg
   fr_min(0.0),    // cm
   fr_max(3.0),    // cm
   fz_min(-3.0),   // cm
   fz_max(3.0)     // cm
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


