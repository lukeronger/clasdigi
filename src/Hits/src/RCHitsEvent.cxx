#include "RCHitsEvent.h"
#include <iostream>

//______________________________________________________________________________

clas12::hits::RCHitsEvent::RCHitsEvent() : fRunNumber(0), fEventNumber(0),
   fNADCHits(0), fNTDCHits(0),fNIonPairs(0)
{
   fADCHits  = new TClonesArray("clas12::hits::ADCHit",48);
   fTDCHits  = new TClonesArray("clas12::hits::TDCHit",10);
   fIonPairs = new TClonesArray("clas12::hits::DriftChamberIonPairHit",10);
   fParticleHits = new TClonesArray("clas12::hits::RecoilChamberParticleHit",10);
   fRegionHits = new TClonesArray("clas12::hits::RecoilChamberParticleHit",10);
} 
//______________________________________________________________________________

clas12::hits::RCHitsEvent::~RCHitsEvent()
{
   delete fADCHits;
   delete fTDCHits;
} 
//______________________________________________________________________________

clas12::hits::TDCHit * clas12::hits::RCHitsEvent::AddTDCHit(int ch, int v, double t) {
   TDCHit * ahit = new ( (*fTDCHits)[fNTDCHits] ) TDCHit(ch,v,t);
   fNTDCHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::ADCHit * clas12::hits::RCHitsEvent::AddADCHit(int ch, int v) {
   ADCHit * ahit = new ( (*fADCHits)[fNADCHits] ) ADCHit(ch,v);
   fNADCHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::DriftChamberIonPairHit * clas12::hits::RCHitsEvent::AddIonPairHit(
      double x, double y, double z, double t )
{
   DriftChamberIonPairHit * ahit = new ( (*fIonPairs)[fNIonPairs] ) DriftChamberIonPairHit(x,y,z,t);
   fNIonPairs++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::RecoilChamberParticleHit * clas12::hits::RCHitsEvent::AddParticleHit()
{
   RecoilChamberParticleHit * ahit = new ((*fParticleHits)[fNParticleHits]) RecoilChamberParticleHit();
   fNParticleHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::RecoilChamberParticleHit * clas12::hits::RCHitsEvent::GetParticleHit(int i)
{
   if( i < fNParticleHits ) {
      return (RecoilChamberParticleHit*)((*fParticleHits)[i]) ;
   }
   return nullptr;
}
//______________________________________________________________________________

clas12::hits::RecoilChamberParticleHit * clas12::hits::RCHitsEvent::AddRegionHit()
{
   RecoilChamberParticleHit * ahit = new ((*fRegionHits)[fNRegionHits]) RecoilChamberParticleHit();
   fNRegionHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::RecoilChamberParticleHit * clas12::hits::RCHitsEvent::GetRegionHit(int i)
{
   if( i < fNRegionHits ) {
      return (RecoilChamberParticleHit*)((*fRegionHits)[i]) ;
   }
   return nullptr;
}
//______________________________________________________________________________

void clas12::hits::RCHitsEvent::Clear(Option_t * opt)
{
   fNADCHits = 0;
   fNTDCHits = 0;
   fNIonPairs = 0;
   fNParticleHits = 0;
   fNRegionHits = 0;
   fTotalTrackLength = 0.0;
   fTotalDeltaE      = 0.0;
   fADCHits->Clear();
   fTDCHits->Clear();
   fIonPairs->Clear();
   fParticleHits->Clear();
   fRegionHits->Clear();
}
//______________________________________________________________________________

void clas12::hits::RCHitsEvent::Print(Option_t * opt) const
{
   std::cout << "RCHitsEvent :"
      << " run=" << fRunNumber
      << ", event=" << fEventNumber 
      << ", nTDC=" << fNTDCHits 
      << ", nADC=" << fNADCHits 
      << ", nIonPairs=" << fNIonPairs
      << ", nParticleHIts=" << fNParticleHits
      << "\n";
}
//______________________________________________________________________________


