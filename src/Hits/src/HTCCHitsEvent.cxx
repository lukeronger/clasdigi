#include "HTCCHitsEvent.h"

//______________________________________________________________________________

clas12::hits::HTCCHitsEvent::HTCCHitsEvent() : fRunNumber(0), fEventNumber(0)
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

