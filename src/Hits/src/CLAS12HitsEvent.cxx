#include "CLAS12HitsEvent.h"
#include <iostream>

//______________________________________________________________________________

clas12::hits::CLAS12HitsEvent::CLAS12HitsEvent() :
   fRunNumber(0), fEventNumber(0)
{ } 
//______________________________________________________________________________

clas12::hits::CLAS12HitsEvent::~CLAS12HitsEvent()
{ } 
//______________________________________________________________________________

void clas12::hits::CLAS12HitsEvent::SetRunNumber(int n)
{
   fRunNumber                   = n;
   fHTCCEvent.fRunNumber        = n;
   fDCEvent.fRunNumber          = n;
   fRCEvent.fRunNumber          = n;
   fECEvent.fRunNumber          = n;
   fRecoilScintEvent.fRunNumber = n;
   fSVTEvent.fRunNumber         = n;
   fHitMask.fRunNumber          = n;
}
//______________________________________________________________________________

void clas12::hits::CLAS12HitsEvent::SetEventNumber(int n)
{
   fEventNumber                   = n;
   fHTCCEvent.fEventNumber        = n;
   fDCEvent.fEventNumber          = n;
   fRCEvent.fEventNumber          = n;
   fECEvent.fEventNumber          = n;
   fRecoilScintEvent.fEventNumber = n;
   fSVTEvent.fEventNumber         = n;
   fHitMask.fEventNumber          = n;
}
//______________________________________________________________________________

void clas12::hits::CLAS12HitsEvent::Clear(Option_t * opt) 
{
   fHTCCEvent.Clear(opt);
   fDCEvent.Clear(opt);
   fRCEvent.Clear(opt);
   fECEvent.Clear(opt);
   fRecoilScintEvent.Clear(opt);
   fSVTEvent.Clear(opt);
   fHitMask.Clear(opt);
}
//______________________________________________________________________________

void clas12::hits::CLAS12HitsEvent::Print(Option_t * opt) const
{
   std::cout << "Run   : " << fRunNumber << "\n";
   std::cout << "Event : " << fEventNumber << "\n";
   fHTCCEvent.Print(opt);
}
//______________________________________________________________________________

