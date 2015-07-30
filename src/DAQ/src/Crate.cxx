#include "Crate.h"
#include <iostream>
#include <iomanip>
#include <string>
#include "Module.h"


//______________________________________________________________________________

clas12::DAQ::Crate::Crate(const char * n, const char * t, int id) : 
   TNamed(n,t), fId(id)
{
   //fModules.SetOwner(true);
}
//______________________________________________________________________________

clas12::DAQ::Crate::Crate(const char * n, int id) : 
   TNamed(n,n), fId(id)
{ }
//______________________________________________________________________________

clas12::DAQ::Crate::Crate(int id) : 
   Crate(Form("crate-%d",id),id)
{ }
//______________________________________________________________________________

clas12::DAQ::Crate::~Crate()
{ } 
//______________________________________________________________________________

void clas12::DAQ::Crate::AddModule(int slot, CrateModule * m) {
   std::string name = m->GetName();
   if( name.length() + 1 > fMaxNameSize ) fMaxNameSize = name.length() + 1;
   if( fSlotMap.count(slot) ) {
      std::cout << " replacing module in slot " << slot << ".\n";
      fModuleNames[fSlotMap[slot]] = name;
      //CrateModule * amod = dynamic_cast<CrateModule*>(
      fModules.erase( fModules.begin() + fSlotMap[slot] );
      //);
      //if(amod) {
      //   delete amod;
      //   amod = nullptr;
      //   //std::cout << "deleted mod" << std::endl;
      //}
      fModules.insert( fModules.begin() + fSlotMap[slot], m );
   } else {
      fSlotMap[slot] = fModuleNames.size();
      fModuleNames.push_back(name);
      fModules.push_back(m);
   }
}
//______________________________________________________________________________
void clas12::DAQ::Crate::Print(Option_t * opt) const
{
   using namespace std;

   cout << setfill(' ') << setw(6) << left << "slot" 
      << " /" 
      << setfill('-') << setw(fMaxNameSize) << right << "-" 
      << "--\\" 
      << setfill(' ') << setw(8) << left << " N ch." << endl;

   for(int i = 0; i<fMaxSlots; i++) {

      if( fSlotMap.count(i) ) { 
         //CrateModule * mod = dynamic_cast<CrateModule*>( fModules.At( fSlotMap[i] ) );
         //if(!mod) mod = dynamic_cast<Module<TDC>*>( fModules.At( fSlotMap[i] ) );
         cout << setfill(' ') << setw(6) << right << i 
            << " |" << setfill('_') << setw(fMaxNameSize) << right << fModuleNames.at(fSlotMap.at(i)) 
            << "__| " 
            << setfill(' ') << setw(8) << left << " " /*mod->fNChannels*/ << endl;
      } else {
         cout << setfill(' ') << setw(6) << right << i << " |" << setfill('_') << setw(fMaxNameSize) << right << "_" << "__|" << endl;
      }

   }

}
//______________________________________________________________________________


