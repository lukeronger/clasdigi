#include "RunConfiguration.h"
#include <iomanip>
#include <iostream>


clas12::sim::RunConfiguration::RunConfiguration(const char * n, const char * t, int run) : 
   TNamed(n,t), fRunNumber(run), fNSimulated(0), 
   fInputFileName(""),  fInputTreeName(""),
   fOutputFileName(""), fOutputTreeName("")
{ } 
//______________________________________________________________________________

clas12::sim::RunConfiguration::RunConfiguration(const char * n, int run) : 
   TNamed(n,n), fRunNumber(run)
{ } 
//______________________________________________________________________________


clas12::sim::RunConfiguration::RunConfiguration(int run) : fRunNumber(run)
{ } 
//______________________________________________________________________________

clas12::sim::RunConfiguration::~RunConfiguration()
= default; 
//______________________________________________________________________________

void clas12::sim::RunConfiguration::Print(std::ostream& s) const
{
   s  << std::right << std::setw(10) << "N events" << " : " 
      << std::left  << std::setw(60) << fNSimulated << "\n"
      << std::right << std::setw(10) << "input file" << " : " 
      << std::left  << std::setw(60) << fInputFileName << "\n"
      << std::right << std::setw(10) << "input tree" << " : " 
      << std::left  << std::setw(60) << fInputTreeName << "\n"
      << std::right << std::setw(10) << "output file" << " : " 
      << std::left  << std::setw(60) << fOutputFileName << "\n"
      << std::right << std::setw(10) << "output tree" << " : " 
      << std::left  << std::setw(60) << fOutputTreeName << "\n";
}
//______________________________________________________________________________

void clas12::sim::RunConfiguration::Print(Option_t *  /*opt*/) const
{
   Print(std::cout);
}
//______________________________________________________________________________

