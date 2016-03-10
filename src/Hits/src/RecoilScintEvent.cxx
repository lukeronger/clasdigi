#include "RecoilScintEvent.h"
#include <iostream>

//______________________________________________________________________________

clas12::hits::RecoilScintEvent::RecoilScintEvent() : fRunNumber(0), fEventNumber(0),
   fNHits(0),  fNPhotonHits(0), fNParticleHits(0)
{
   fHits  = new TClonesArray("clas12::hits::RecoilScintHit",5);
   fPhotonHits  = new TClonesArray("clas12::hits::PhotonHit",5);
   fParticleHits  = new TClonesArray("clas12::hits::ParticleHit",5);
} 
//______________________________________________________________________________

clas12::hits::RecoilScintEvent::~RecoilScintEvent()
{
   delete fHits;
   delete fPhotonHits;
   delete fParticleHits;
} 
//______________________________________________________________________________

clas12::hits::RecoilScintHit * clas12::hits::RecoilScintEvent::AddHit(int chan)
{
   clas12::hits::RecoilScintHit * ahit = new ( (*fHits)[fNHits] ) clas12::hits::RecoilScintHit();
   ahit->fChannel = chan;
   fNHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::RecoilScintHit * clas12::hits::RecoilScintEvent::GetHit(int i)
{
   if( i < fNHits ) {
      return (clas12::hits::RecoilScintHit*)((*fHits)[i]) ;
   }
   return nullptr;
}
//______________________________________________________________________________

clas12::hits::PhotonHit * clas12::hits::RecoilScintEvent::AddPhotonHit(int chan)
{
   clas12::hits::PhotonHit * ahit = new ( (*fPhotonHits)[fNPhotonHits] ) clas12::hits::PhotonHit();
   ahit->fChannel = chan;
   fNPhotonHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::PhotonHit * clas12::hits::RecoilScintEvent::GetPhotonHit(int i)
{
   if( i < fNPhotonHits ) {
      return (clas12::hits::PhotonHit*)((*fPhotonHits)[i]) ;
   }
   return nullptr;
}
//______________________________________________________________________________

clas12::hits::ParticleHit * clas12::hits::RecoilScintEvent::AddParticleHit(int chan)
{
   clas12::hits::ParticleHit * ahit = new ( (*fParticleHits)[fNParticleHits] ) clas12::hits::ParticleHit();
   ahit->fChannel = chan;
   fNParticleHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::ParticleHit * clas12::hits::RecoilScintEvent::GetParticleHit(int i)
{
   if( i < fNParticleHits ) {
      return (clas12::hits::ParticleHit*)((*fParticleHits)[i]) ;
   }
   return nullptr;
}
//______________________________________________________________________________


void clas12::hits::RecoilScintEvent::Clear(Option_t * opt)
{
   fNHits = 0;
   fNPhotonHits = 0;
   fNParticleHits = 0;
   fHits->Clear();
   fPhotonHits->Clear();
   fParticleHits->Clear();
}
//______________________________________________________________________________

void clas12::hits::RecoilScintEvent::Print(Option_t * opt) const
{
   std::cout << "RecoilScintEvent :"
      << " run=" << fRunNumber
      << ", event=" << fEventNumber 
      << ", nHits=" << fNHits 
      << ", nPhotonHits=" << fNPhotonHits 
      << ", nParticleHits=" << fNParticleHits 
      << "\n";
}
//______________________________________________________________________________


