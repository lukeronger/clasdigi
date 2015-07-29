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


