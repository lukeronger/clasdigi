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
void clas12::hits::CLAS12HitsEvent::Clear(Option_t * opt) 
{
   fHTCCEvent.Clear(opt);
   fDCEvent.Clear(opt);
}
//______________________________________________________________________________

void clas12::hits::CLAS12HitsEvent::Print(Option_t * opt) const
{
   std::cout << "Run   : " << fRunNumber << "\n";
   std::cout << "Event : " << fEventNumber << "\n";
   fHTCCEvent.Print(opt);
}
//______________________________________________________________________________

