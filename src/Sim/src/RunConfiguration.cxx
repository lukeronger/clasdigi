#include "RunConfiguration.h"


clas12::sim::RunConfiguration::RunConfiguration(const char * t, const char * n, int run) : 
   TNamed(t,n), fRunNumber(run)
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
{ } 
//______________________________________________________________________________


