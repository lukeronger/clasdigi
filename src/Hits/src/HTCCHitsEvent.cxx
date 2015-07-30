#include "HTCCHitsEvent.h"
#include <iostream>

//______________________________________________________________________________

clas12::hits::HTCCHitsEvent::HTCCHitsEvent() : fRunNumber(0), fEventNumber(0),
   fNADCHits(0), fNTDCHits(0)
{
   fADCHits = new TClonesArray("clas12::hits::ADCHit",48);
   fTDCHits = new TClonesArray("clas12::hits::TDCHit",10);
} 
//______________________________________________________________________________

clas12::hits::HTCCHitsEvent::~HTCCHitsEvent()
{
   delete fADCHits;
   delete fTDCHits;
} 
//______________________________________________________________________________

clas12::hits::TDCHit * clas12::hits::HTCCHitsEvent::AddTDCHit(int ch, int v, double t) {
   TDCHit * ahit = new ( (*fTDCHits)[fNTDCHits] ) TDCHit(ch,v,t);
   fNTDCHits++;
   return ahit;
}
//______________________________________________________________________________

clas12::hits::ADCHit * clas12::hits::HTCCHitsEvent::AddADCHit(int ch, int v) {
   ADCHit * ahit = new ( (*fADCHits)[fNADCHits] ) ADCHit(ch,v);
   fNADCHits++;
   return ahit;
}
//______________________________________________________________________________

void clas12::hits::HTCCHitsEvent::Clear(Option_t * opt)
{
   fNADCHits = 0;
   fNTDCHits = 0;
   fADCHits->Clear();
   fTDCHits->Clear();
}
//______________________________________________________________________________

void clas12::hits::HTCCHitsEvent::Print(Option_t * opt) const
{
   std::cout << "HTCCHitsEvent :"
      << " run=" << fRunNumber
      << ", event=" << fEventNumber 
      << ", nTDC=" << fNTDCHits 
      << ", nADC=" << fNADCHits 
      << "\n";
}
//______________________________________________________________________________


