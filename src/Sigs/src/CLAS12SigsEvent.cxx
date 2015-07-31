#include "CLAS12SigsEvent.h"
#include <iostream>

//______________________________________________________________________________

clas12::sigs::CLAS12SigsEvent::CLAS12SigsEvent() :
   fRunNumber(0), fEventNumber(0)
{ } 
//______________________________________________________________________________

clas12::sigs::CLAS12SigsEvent::~CLAS12SigsEvent()
{ } 
//______________________________________________________________________________
void clas12::sigs::CLAS12SigsEvent::Clear(Option_t * opt) 
{
   fHTCCEvent.Clear(opt);
}
//______________________________________________________________________________

void clas12::sigs::CLAS12SigsEvent::Print(Option_t * opt) const
{
   std::cout << "Run   : " << fRunNumber << "\n";
   std::cout << "Event : " << fEventNumber << "\n";
   fHTCCEvent.Print(opt);
}
//______________________________________________________________________________

