#include "ThrownEvent.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TParticle.h"
#include "TClonesArray.h"

//______________________________________________________________________________

clas12::sim::ThrownEvent::ThrownEvent() :
   fRunNumber(0), fEventNumber(0),fNParticles(0),fBeamPol(0.0),fTargetPol(0.0)
{
   fParticles = new TClonesArray("TParticle",4);
} 
//______________________________________________________________________________

clas12::sim::ThrownEvent::~ThrownEvent()
{ } 
//______________________________________________________________________________

TParticle * clas12::sim::ThrownEvent::AddParticle()
{
   TParticle * part = new( (*fParticles)[fNParticles] ) TParticle();
   fNParticles++;
   return part;
}
//______________________________________________________________________________

TParticle * clas12::sim::ThrownEvent::GetParticle(int i)
{
   if( i < fNParticles) {
      TParticle * part = (TParticle*)((*fParticles)[i]);
      return part;
   } else {
      std::cout << " error  particle index out of range clas12::sim::ThrownEvent::GetParticle("   << i << ")\n";
      TParticle * part = (TParticle*)((*fParticles)[0]);
      return part;
   }
}
//______________________________________________________________________________

void clas12::sim::ThrownEvent::Clear(Option_t * opt)
{
   fParticles->Clear();
   fNParticles = 0;
} 
//______________________________________________________________________________

void clas12::sim::ThrownEvent::Print(Option_t * opt) const
{
   std::cout << " Event : " << fEventNumber <<std::endl;

   for(int i = 0; i<fNParticles;i++) {
      (*fParticles)[i]->Print();
   }
} 
//______________________________________________________________________________
void clas12::sim::ThrownEvent::ReadLundEvent(std::ifstream& in)
{
   fEventNumber++;
   Clear();
   int npart = ReadLundHeader(in);
   for(int i = 0; i< npart; i++) {
      ReadLundParticle(in);
   }
}
//______________________________________________________________________________

int clas12::sim::ThrownEvent::ReadLundHeader(std::ifstream& in)
{
   std::string line;
   std::getline(in, line);
   std::stringstream ss;
   ss << line;

   // Lund format reference: https://gemc.jlab.org/gemc/Documentation/Entries/2011/3/18_The_LUND_Format.html
   // Header:
   // Column    Quantity
   //   1      Number of particles
   //   2*     Number of target nucleons
   //   3*     Number of target protons
   //   4*     Target Polarization
   //   5      Beam Polarization
   //   6*     x
   //   7*     y
   //   8*     W
   //   9*     Q2
   //   10*    nu
   int ipart,A,Z;

   ss >> ipart;
   ss >> A;
   ss >> Z;
   ss >> fTargetPol;
   ss >> fBeamPol;
   double temp;
   if(ss.eof()){
      std::cout << "error: end of sstream\n";
   }
   for(int i = 5; i<10; i++) {
      ss >> temp;
   }
   //std::cout << "ipart = " << ipart <<std::endl;
   return ipart;
}
//______________________________________________________________________________

int clas12::sim::ThrownEvent::ReadLundParticle(std::ifstream& in)
{ 
   std::string line;
   std::getline(in, line);
   std::stringstream ss;
   ss << line;

   // Lund format reference: https://gemc.jlab.org/gemc/Documentation/Entries/2011/3/18_The_LUND_Format.html
   // NOTE the vertex is in METERS unlike the website above
   int iLund, charge, type, pdg, parent, daughter;
   double px,py,pz, E, mass, vx,vy,vz;
   TParticle      * part     = AddParticle();
   //std::cout << fNParticles << " particles\n";
   //std::cout << line << std::endl;

   ss >> iLund ;
   ss >> charge;
   ss >> type;
   ss >> pdg;
   ss >> parent;
   ss >> daughter;
   ss >> px;
   ss >> py;
   ss >> pz;
   ss >> E;
   ss >> mass;
   ss >> vx;
   ss >> vy;
   ss >> vz;
   //if(ss.eof()){
   //   std::cout << "error: end of sstream\n";
   //}

   part->SetPdgCode(pdg);
   part->SetMomentum(px,py,pz,E);
   part->SetProductionVertex(vx,vy,vz,0.0);
   //part->Print();

   return iLund;
}
//______________________________________________________________________________

//void ThrownEvent::LundFormat( std::ostream& s )
//{
//   LundHeaderFormat(fEG_Event,s);
//   for(int i = 0; i<fEG_Event.fParticles->GetEntries(); i++ ){
//      LundEventFormat(i,fEG_Event,s);
//   }
//}
////________________________________________________________________________________
//void ThrownEvent::LundHeaderFormat( InSANE_EG_Event& eg_event, std::ostream& s)
//{
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
//   s  << eg_event.fParticles->GetEntries()    << " "
//      << eg_event.fXSec->GetA()              << " "
//      << eg_event.fXSec->GetZ()              << " "
//      << eg_event.fTargetPol                 << " "
//      << eg_event.fBeamPol                   << " "
//      << 0.0 /* x  */                         << " "
//      << 0.0 /* y  */                         << " "
//      << 0.0 /* W  */                         << " "
//      << 0.0 /* Q2 */                         << " "
//      << 0.0 /* nu */                         << "\n";
//}
////________________________________________________________________________________
//void ThrownEvent::LundEventFormat(
//      int           i, 
//      InSANE_EG_Event& eg_event,
//      std::ostream& s)
//{
//   // Lund format reference: https://gemc.jlab.org/gemc/Documentation/Entries/2011/3/18_The_LUND_Format.html
//   // Particles:
//   // Column    Quantity
//   //   1      index
//   //   2      charge
//   //   3      type(=1 is active)
//   //   4      particle id
//   //   5      parent id (decay bookkeeping)
//   //   6      daughter (decay bookkeeping)
//   //   7      px [GeV]
//   //   8      py [GeV]
//   //   9      pz [GeV]
//   //   10     E [GeV]
//   //   11     mass (not used)
//   //   12     x vertex [m]
//   //   13     y vertex [m]
//   //   14     z vertex [m]
//   // NOTE the vertex is in METERS unlike the website above
//   int iLund = i+1;
//   InSANEParticle * part     = (InSANEParticle*)eg_event.fParticles->At(i);
//   TParticlePDG   * part_pdg = part->GetPDG();
//   s << "  "
//      << iLund                  << " "
//      << part_pdg->Charge()/3.0 << " "
//      << 1                      << " "
//      << part_pdg->PdgCode()    << " "
//      << 0                      << " "
//      << 0                      << " "
//      << part->Px()             << " "
//      << part->Py()             << " "
//      << part->Pz()             << " "
//      << part->Energy()         << " "
//      << part_pdg->Mass()       << " "
//      << part->Vx()/100.0       << " "
//      << part->Vy()/100.0       << " "
//      << part->Vz()/100.0       << "\n";
//}
//______________________________________________________________________________



