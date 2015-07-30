#include "ModuleChannel.h"


//______________________________________________________________________________

clas12::DAQ::ModuleChannel::ModuleChannel(int id) : fChannel(id)
{ }
//______________________________________________________________________________

clas12::DAQ::ModuleChannel::~ModuleChannel()
{ } 
//______________________________________________________________________________

void clas12::DAQ::ModuleChannel::Clear(Option_t * opt)
{ }
//______________________________________________________________________________

void clas12::DAQ::ModuleChannel::Print(Option_t * opt) const
{
   std::cout << " channel = " << fChannel << std::endl;
}
//______________________________________________________________________________

