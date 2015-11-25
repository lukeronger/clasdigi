#include "TriggerEvent.h"
#include <iostream>

//______________________________________________________________________________

clas12::hits::TriggerEvent::TriggerEvent() :
   fRunNumber(0), fEventNumber(0), fTrigType(0), fTrigTime(0.0)
{ } 
//______________________________________________________________________________

clas12::hits::TriggerEvent::~TriggerEvent()
{ } 
//______________________________________________________________________________
void clas12::hits::TriggerEvent::Clear(Option_t * opt) 
{
   fTrigType = 0;
   fTrigTime = 0.0;
}
//______________________________________________________________________________

void clas12::hits::TriggerEvent::Print(Option_t * opt) const
{
   std::cout << "TriggerEvent\n" ;
   std::cout << "Run      : " << fRunNumber << "\n";
   std::cout << "Event    : " << fEventNumber << "\n";
   std::cout << "TrigType : " << fTrigType << "\n";
   std::cout << "TrigTime : " << fTrigTime << "\n";
}
//______________________________________________________________________________

