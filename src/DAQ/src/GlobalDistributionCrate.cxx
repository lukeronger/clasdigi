#include "GloabalDistributionCrate.h"
#include <iostream>
#include <iomanip>
#include <string>


//______________________________________________________________________________

clas12::DAQ::GloabalDistributionCrate::GloabalDistributionCrate(const char * n, const char * t, int id) : 
   Crate(n,t,id)
{
   fModules.SetOwner(true);
}
//______________________________________________________________________________

clas12::DAQ::GloabalDistributionCrate::GloabalDistributionCrate(const char * n, int id) : 
   Crate(n,n,id)
{ }
//______________________________________________________________________________

clas12::DAQ::GloabalDistributionCrate::GloabalDistributionCrate(int id) : 
   Crate(id)
{ }
//______________________________________________________________________________

clas12::DAQ::GloabalDistributionCrate::~GloabalDistributionCrate()
{ } 
//______________________________________________________________________________
void clas12::DAQ::GloabalDistributionCrate::AddModule(int slot, GloabalDistributionCrateModule * m) {
   std::string name = m->GetName();
   if( name.length() + 1 > fMaxNameSize ) fMaxNameSize = name.length() + 1;
   if( fSlotMap.count(slot) ) {
      std::cout << " replacing module in slot " << slot << ".\n";
      fModuleNames[fSlotMap[slot]] = name;
      GloabalDistributionCrateModule * amod = dynamic_cast<GloabalDistributionCrateModule*>(fModules.RemoveAt( fSlotMap[slot] ));
      if(amod) {
         delete amod;
         amod = nullptr;
         //std::cout << "deleted mod" << std::endl;
      }
      fModules.AddAt( m, fSlotMap[slot] );
   } else {
      fSlotMap[slot] = fModuleNames.size();
      fModuleNames.push_back(name);
      fModules.Add(m);
   }
}
//______________________________________________________________________________
void clas12::DAQ::GloabalDistributionCrate::Print(Option_t * opt)
{
   using namespace std;

   cout << setfill(' ') << setw(6) << left << "slot" 
      << " /" 
      << setfill('-') << setw(fMaxNameSize) << right << "-" 
      << "--\\" 
      << setfill(' ') << setw(8) << left << " N ch." << endl;

   for(int i = 0; i<fMaxSlots; i++) {

      if( fSlotMap.count(i) ) { 
         GloabalDistributionCrateModule * mod = dynamic_cast<GloabalDistributionCrateModule*>( fModules.At( fSlotMap[i] ) );
         cout << setfill(' ') << setw(6) << right << i 
            << " |" << setfill('_') << setw(fMaxNameSize) << right << fModuleNames[fSlotMap[i]] 
            << "__| " 
            << setfill(' ') << setw(8) << left << mod->fNChannels << endl;
      } else {
         cout << setfill(' ') << setw(6) << right << i << " |" << setfill('_') << setw(fMaxNameSize) << right << "_" << "__|" << endl;
      }

   }

}
//______________________________________________________________________________


