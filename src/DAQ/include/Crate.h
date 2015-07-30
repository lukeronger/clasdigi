#ifndef clas12_DAQ_Crate_HH
#define clas12_DAQ_Crate_HH

#include "TNamed.h"
#include "TList.h"

#include "CrateModule.h"
#include "SignalDistribution.h"
#include "Module.h"
#include <vector>
#include <string>
#include <map>

namespace clas12 {

   namespace DAQ {

      class Crate : public TNamed {

         protected:

            int                 fMaxNameSize = 10;
            int                 fMaxSlots    = 18;
            std::map<int,int>   fSlotMap;          // Maps slot (key) to arb vector location

         public:
            int                         fId;
            std::vector<std::string>    fModuleNames;
            std::vector<CrateModule*>   fModules;
            SignalDistribution          fSD;

         public:
            Crate(const char * n = "", const char * t = "", int         id = 0 );
            Crate(const char * n, int         id);
            Crate(int         id);
            virtual ~Crate();

            void AddModule(int slot, CrateModule * m) ;

            virtual void Clear(Option_t * opt = "") override
            {
               //std::cout << "clearing Crate\n";
               for(auto mod : fModules ) {
                  mod->Clear(opt);
               }
               //for(int i = 0; i<fModules.size();i++){
               //   fModules.At(i)->Clear(opt);
               //}
            }

            virtual void Reset(Option_t * opt = "") {
               for(auto mod : fModules ) {
                  mod->Reset(opt);
               }
               //for(int i = 0; i<fModules.GetEntries();i++){
               //   fModules.At(i)->Reset(opt);
               //}
            }

            void Print(Option_t * opt = "") const override;

            template <typename T>
            void AddCrateModule(int slot, Module<T> * m )
            {
               std::string name = m->GetName();
               // increment the max name size for Print()
               if( name.length() + 1 > this->fMaxNameSize ) this->fMaxNameSize = name.length() + 1;
               if( this->fSlotMap.count(slot) ) {
                  std::cout << " replacing module in slot " << slot << ".\n";
                  this->fModuleNames[this->fSlotMap[slot]] = name;
                  this->fModules.erase( fModules.begin() + this->fSlotMap[slot] );
                  this->fModules.insert(fModules.begin() + this->fSlotMap[slot],m );
               } else {
                  this->fSlotMap[slot] = this->fModuleNames.size();
                  this->fModuleNames.push_back(name);
                  this->fModules.push_back(m);
               }
            }

            template <typename T>
            Module<T> * GetCrateModule(int slot)//, Module<T> * m)
            {
               if( this->fSlotMap.count(slot) ) {
                  return dynamic_cast<Module<T>*>(this->fModules.at(this->fSlotMap[slot]) );
               } 
               std::cout << "Module not found in slot " << slot << "\n";
               return nullptr;
            }

            ClassDef(Crate,1)
      };

   }

}

#endif

