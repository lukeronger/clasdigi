#include "HTCCSigsEvent.h"
#include <iostream>

//______________________________________________________________________________

clas12::sigs::HTCCSigsEvent::HTCCSigsEvent() : fRunNumber(0), fEventNumber(0),
   fNADCsigs(0), fNTDCsigs(0)
{
   fADCsigs = new TClonesArray("clas12::sigs::ADCSignal",48);
   fTDCsigs = new TClonesArray("clas12::sigs::TDCSignal",10);
} 
//______________________________________________________________________________

clas12::sigs::HTCCSigsEvent::~HTCCSigsEvent()
{
   delete fADCsigs;
   delete fTDCsigs;
} 
//______________________________________________________________________________

clas12::sigs::TDCSignal * clas12::sigs::HTCCSigsEvent::AddTDCSignal(int ch, int v) {
   TDCSignal * ahit = new ( (*fTDCsigs)[fNTDCsigs] ) TDCSignal(ch,v);
   fNTDCsigs++;
   return ahit;
}
//______________________________________________________________________________

clas12::sigs::ADCSignal * clas12::sigs::HTCCSigsEvent::AddADCSignal(int ch, int v) {
   ADCSignal * ahit = new ( (*fADCsigs)[fNADCsigs] ) ADCSignal(ch,v);
   fNADCsigs++;
   return ahit;
}
//______________________________________________________________________________

void clas12::sigs::HTCCSigsEvent::Clear(Option_t * opt)
{
   fNADCsigs = 0;
   fNTDCsigs = 0;
   fADCsigs->Clear();
   fTDCsigs->Clear();
}
//______________________________________________________________________________

void clas12::sigs::HTCCSigsEvent::Print(Option_t * opt) const
{
   std::cout << "HTCCSigsEvent :"
      << " run=" << fRunNumber
      << ", event=" << fEventNumber 
      << ", nTDC=" << fNTDCsigs 
      << ", nADC=" << fNADCsigs 
      << "\n";
}
//______________________________________________________________________________


