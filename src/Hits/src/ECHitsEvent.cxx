#include "ECHitsEvent.h"
#include <iostream>

//______________________________________________________________________________

clas12::hits::ECHitsEvent::ECHitsEvent() : fRunNumber(0), fEventNumber(0),
   fNADCHits(0), fNTDCHits(0)
{
   fADCHits  = new TClonesArray("clas12::hits::ADCHit",48);
   fTDCHits  = new TClonesArray("clas12::hits::TDCHit",10);
   //fIonPairs = new TClonesArray("clas12::hits::DriftChamberIonPairHit",10);
   fParticleHits = new TClonesArray("clas12::hits::DriftChamberParticleHit",10);
   fRegionHits = new TClonesArray("clas12::hits::DriftChamberParticleHit",10);
} 
//______________________________________________________________________________

clas12::hits::ECHitsEvent::~ECHitsEvent()
{
   delete fADCHits;
   delete fTDCHits;
} 
//______________________________________________________________________________

clas12::hits::TDCHit * clas12::hits::ECHitsEvent::AddTDCHit(int ch, int v, double t) {
   TDCHit * ahit = new ( (*fTDCHits)[fNTDCHits] ) TDCHit(ch,v,t);
   fNTDCHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::ADCHit * clas12::hits::ECHitsEvent::AddADCHit(int ch, int v) {
   ADCHit * ahit = new ( (*fADCHits)[fNADCHits] ) ADCHit(ch,v);
   fNADCHits++;
   return ahit;
}
//______________________________________________________________________________

//clas12::hits::DriftChamberIonPairHit * clas12::hits::ECHitsEvent::AddIonPairHit(
//      double x, double y, double z, double t )
//{
//   DriftChamberIonPairHit * ahit = new ( (*fIonPairs)[fNIonPairs] ) DriftChamberIonPairHit(x,y,z,t);
//   fNIonPairs++;
//   return ahit;
//}
//______________________________________________________________________________

clas12::hits::DriftChamberParticleHit * clas12::hits::ECHitsEvent::AddParticleHit()
{
   DriftChamberParticleHit * ahit = new ((*fParticleHits)[fNParticleHits]) DriftChamberParticleHit();
   fNParticleHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::DriftChamberParticleHit * clas12::hits::ECHitsEvent::GetParticleHit(int i)
{
   if( i < fNParticleHits ) {
      return (DriftChamberParticleHit*)((*fParticleHits)[i]) ;
   }
   return nullptr;
}
//______________________________________________________________________________

clas12::hits::DriftChamberParticleHit * clas12::hits::ECHitsEvent::AddRegionHit()
{
   DriftChamberParticleHit * ahit = new ((*fRegionHits)[fNRegionHits]) DriftChamberParticleHit();
   fNRegionHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::DriftChamberParticleHit * clas12::hits::ECHitsEvent::GetRegionHit(int i)
{
   if( i < fNRegionHits ) {
      return (DriftChamberParticleHit*)((*fRegionHits)[i]) ;
   }
   return nullptr;
}
//______________________________________________________________________________

void clas12::hits::ECHitsEvent::Clear(Option_t * opt)
{
   fNADCHits = 0;
   fNTDCHits = 0;
   //fNIonPairs = 0;
   fNParticleHits = 0;
   fNRegionHits = 0;
   fADCHits->Clear();
   fTDCHits->Clear();
   //fIonPairs->Clear();
   fParticleHits->Clear();
   fRegionHits->Clear();
}
//______________________________________________________________________________

void clas12::hits::ECHitsEvent::Print(Option_t * opt) const
{
   std::cout << "ECHitsEvent :"
      << " run=" << fRunNumber
      << ", event=" << fEventNumber 
      << ", nTDC=" << fNTDCHits 
      << ", nADC=" << fNADCHits 
      //<< ", nIonPairs=" << fNIonPairs
      << ", nParticleHIts=" << fNParticleHits
      << "\n";
}
//______________________________________________________________________________


