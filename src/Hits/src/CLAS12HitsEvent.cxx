#include "CLAS12HitsEvent.h"
#include <iostream>

//______________________________________________________________________________

clas12::hits::CLAS12HitsEvent::CLAS12HitsEvent() :
   fRunNumber(0), fEventNumber(0)
{
   fTrackHitMasks = new TClonesArray("clas12::hits::EventHitMask",5);
   Clear();
} 
//______________________________________________________________________________

clas12::hits::CLAS12HitsEvent::~CLAS12HitsEvent()
{
} 
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
   fEventNumber    = 0;
   fNTrackHitMasks = 0;
   fTrackHitMasks->Clear();
}
//______________________________________________________________________________

void clas12::hits::CLAS12HitsEvent::Print(Option_t * opt) const
{
   std::cout << "Run   : " << fRunNumber << "\n";
   std::cout << "Event : " << fEventNumber << "\n";
   fHTCCEvent.Print(opt);
}
//______________________________________________________________________________

clas12::hits::EventHitMask * clas12::hits::CLAS12HitsEvent::AddTrackHitMask()
{
   EventHitMask * mask = new( (*fTrackHitMasks)[fNTrackHitMasks] ) EventHitMask();
   fNTrackHitMasks++;
  return mask;
}
//______________________________________________________________________________

clas12::hits::EventHitMask * clas12::hits::CLAS12HitsEvent::GetTrackHitMask(int i)
{
   int nhit = fNTrackHitMasks;
   if( i < fNTrackHitMasks ){
      return( (EventHitMask*)((*fTrackHitMasks)[i]) );
   } else {
      return nullptr;
   }
}
//______________________________________________________________________________

clas12::hits::EventHitMask * clas12::hits::CLAS12HitsEvent::TrackHitMask(int i)
{
   //std::cout << " get track hit mask " << i << std::endl;
   int nhit = fNTrackHitMasks;
   //std::cout << " nhit " << nhit << std::endl;
   if( i < fNTrackHitMasks ){
      //std::cout << "mask exists\n";
      return( (clas12::hits::EventHitMask*)(*fTrackHitMasks)[i] );
   } else {
      //std::cout << "mask DOES NOT exist\n";
      int j = nhit;
      while( i >= fNTrackHitMasks ){
         //std::cout << " adding " << j << std::endl;
         AddTrackHitMask();
         //auto hm = new( (*fTrackHitMasks)[j] ) clas12::hits::EventHitMask();;
         j++;
      }
      return( (EventHitMask*)((*fTrackHitMasks)[i]) );
   }
}
//______________________________________________________________________________

