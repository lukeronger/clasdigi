#include "RCWire.h"
#include "TMath.h"
#include <iomanip>


//______________________________________________________________________________

clas12::geo::RCWire::RCWire(int l, int w) : 
   fLayer(l), fWire(w), fChannel(0) 
{ } 
//______________________________________________________________________________

clas12::geo::RCWire::~RCWire()
{ } 
//______________________________________________________________________________

void clas12::geo::RCWire::Print(Option_t *) const
{
   std::cout 
      << "layer: "      << std::setw(3) << fLayer
      << "wire: "       << std::setw(3) << fWire
      << "channel: "    << std::setw(3) << fChannel
      << "\n";
}
//______________________________________________________________________________


