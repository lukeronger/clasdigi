#include "RunConfiguration.h"
#include <iomanip>
#include <iostream>

//#include "json.hpp"
//using json = nlohmann::json;

namespace clas12 {
   namespace sim {

      RunConfiguration::RunConfiguration(const char * n, const char * t, int run) : 
         TNamed(n,t), fRunNumber(run), fNSimulated(0), 
         fInputFileName(""),  fInputTreeName(""),
         fOutputFileName(""), fOutputTreeName("")
      {
      } 
      //______________________________________________________________________________

      RunConfiguration::RunConfiguration(const char * n, int run) : 
         TNamed(n,n), fRunNumber(run)
      { } 
      //______________________________________________________________________________


      RunConfiguration::RunConfiguration(int run) : fRunNumber(run)
      { } 
      //______________________________________________________________________________

      RunConfiguration::~RunConfiguration() = default; 
      //______________________________________________________________________________

      void RunConfiguration::Print(std::ostream& s) const
      {
         s  << std::right << std::setw(20) << "N events" << " : " 
            << std::left  << std::setw(60) << fNSimulated << "\n"
            << std::right << std::setw(20) << "input file" << " : " 
            << std::left  << std::setw(60) << fInputFileName << "\n"
            << std::right << std::setw(20) << "input tree" << " : " 
            << std::left  << std::setw(60) << fInputTreeName << "\n"
            << std::right << std::setw(20) << "output file" << " : " 
            << std::left  << std::setw(60) << fOutputFileName << "\n"
            << std::right << std::setw(20) << "output tree" << " : " 
            << std::left  << std::setw(60) << fOutputTreeName << "\n";
      }
      //______________________________________________________________________________

      void RunConfiguration::Print(Option_t *  /*opt*/) const
      {
         Print(std::cout);
      }
      //______________________________________________________________________________
      
      //void RunConfiguration::Additional(std::string name, std::string value)
      //{
      //   fAdditionalJSON[name] = value;
      //}
      ////______________________________________________________________________________

      //json RunConfiguration::JSON()
      //{
      //   fJSON["run_number"]  = fRunNumber;
      //   fJSON["input_file"]  = fInputFileName;
      //   fJSON["input_tree"]  = fInputTreeName;
      //   fJSON["output_file"] = fOutputFileName;
      //   fJSON["output_tree"] = fOutputTreeName;
      //   fJSON["n_events_simulated"]    = fNSimulated;
      //   fJSON[""]    = fNSimulated;
      //   for (json::iterator it = fAdditionalJSON.begin(); it != fAdditionalJSON.end(); ++it) {
      //        std::cout << it.key() << " : " << it.value() << "\n";
      //        fJSON[ it.key() ] =  it.value();
      //   }
      //   return & fJSON;
      //}
      //______________________________________________________________________________
   }
}

