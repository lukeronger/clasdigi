#include "ECHitsEvent.h"
#include <iostream>

//______________________________________________________________________________

clas12::hits::ECHitsEvent::ECHitsEvent() : fRunNumber(0), fEventNumber(0),
   fNADCHits(0), fNTDCHits(0)
{
   fADCHits  = new TClonesArray("clas12::hits::ADCHit",48);
   fTDCHits  = new TClonesArray("clas12::hits::TDCHit",10);
   fParticleHits = new TClonesArray("clas12::hits::ParticleHit",10);
   fRegionHits   = new TClonesArray("clas12::hits::ParticleHit",10);
} 
//______________________________________________________________________________

clas12::hits::ECHitsEvent::~ECHitsEvent()
{
   delete fADCHits;
   delete fTDCHits;
   delete fParticleHits;
   delete fRegionHits;
} 
//______________________________________________________________________________

clas12::hits::TDCHit * clas12::hits::ECHitsEvent::AddTDCHit(int ch, int v, double t)
{
   TDCHit * ahit = new ( (*fTDCHits)[fNTDCHits] ) TDCHit(ch,v,t);
   fNTDCHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::ADCHit * clas12::hits::ECHitsEvent::AddADCHit(int ch, int v)
{
   ADCHit * ahit = new ( (*fADCHits)[fNADCHits] ) ADCHit(ch,v);
   fNADCHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::ParticleHit * clas12::hits::ECHitsEvent::AddParticleHit()
{
   ParticleHit * ahit = new ((*fParticleHits)[fNParticleHits]) ParticleHit();
   fNParticleHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::ParticleHit * clas12::hits::ECHitsEvent::GetParticleHit(int i)
{
   if( i < fNParticleHits ) {
      return (ParticleHit*)((*fParticleHits)[i]) ;
   }
   return nullptr;
}
//______________________________________________________________________________

clas12::hits::ParticleHit * clas12::hits::ECHitsEvent::AddRegionHit()
{
   ParticleHit * ahit = new ((*fRegionHits)[fNRegionHits]) ParticleHit();
   fNRegionHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::ParticleHit * clas12::hits::ECHitsEvent::GetRegionHit(int i)
{
   if( i < fNRegionHits ) {
      return (ParticleHit*)((*fRegionHits)[i]) ;
   }
   return nullptr;
}
//______________________________________________________________________________

void clas12::hits::ECHitsEvent::Clear(Option_t * opt)
{
   fNADCHits = 0;
   fNTDCHits = 0;
   fNParticleHits = 0;
   fNRegionHits = 0;
   fADCHits->Clear();
   fTDCHits->Clear();
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
      << ", nParticleHIts=" << fNParticleHits
      << "\n";
}
//______________________________________________________________________________


