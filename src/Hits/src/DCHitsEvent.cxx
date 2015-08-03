#include "DCHitsEvent.h"
#include <iostream>

//______________________________________________________________________________

clas12::hits::DCHitsEvent::DCHitsEvent() : fRunNumber(0), fEventNumber(0),
   fNADCHits(0), fNTDCHits(0),fNIonPairs(0)
{
   fADCHits  = new TClonesArray("clas12::hits::ADCHit",48);
   fTDCHits  = new TClonesArray("clas12::hits::TDCHit",10);
   fIonPairs = new TClonesArray("clas12::hits::DriftChamberIonPairHit",10);
} 
//______________________________________________________________________________

clas12::hits::DCHitsEvent::~DCHitsEvent()
{
   delete fADCHits;
   delete fTDCHits;
} 
//______________________________________________________________________________

clas12::hits::TDCHit * clas12::hits::DCHitsEvent::AddTDCHit(int ch, int v, double t) {
   TDCHit * ahit = new ( (*fTDCHits)[fNTDCHits] ) TDCHit(ch,v,t);
   fNTDCHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::ADCHit * clas12::hits::DCHitsEvent::AddADCHit(int ch, int v) {
   ADCHit * ahit = new ( (*fADCHits)[fNADCHits] ) ADCHit(ch,v);
   fNADCHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::DriftChamberIonPairHit * clas12::hits::DCHitsEvent::AddIonPairHit(
      double x, double y, double z, double t )
{
   DriftChamberIonPairHit * ahit = new ( (*fIonPairs)[fNIonPairs] ) DriftChamberIonPairHit(x,y,z,t);
   fNIonPairs++;
   return ahit;

}
//______________________________________________________________________________

void clas12::hits::DCHitsEvent::Clear(Option_t * opt)
{
   fNADCHits = 0;
   fNTDCHits = 0;
   fNIonPairs = 0;
   fADCHits->Clear();
   fTDCHits->Clear();
   fIonPairs->Clear();
}
//______________________________________________________________________________

void clas12::hits::DCHitsEvent::Print(Option_t * opt) const
{
   std::cout << "DCHitsEvent :"
      << " run=" << fRunNumber
      << ", event=" << fEventNumber 
      << ", nTDC=" << fNTDCHits 
      << ", nADC=" << fNADCHits 
      << ", nIonPairs=" << fNIonPairs 
      << "\n";
}
//______________________________________________________________________________


