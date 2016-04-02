#include "DCWire.h"
#include "TMath.h"
#include <iomanip>


//______________________________________________________________________________

clas12::hits::DCWire::DCWire(int sec, int reg, int sl, int l, int w) : 
   fSector(sec), fRegion(reg), fSuperLayer(sl), fLayer(l), fWire(w), fChannel(0) 
{ } 
//______________________________________________________________________________

clas12::hits::DCWire::~DCWire()
{ } 
//______________________________________________________________________________

void clas12::hits::DCWire::Print(Option_t *) const
{
   std::cout 
      << "sector: "     << std::setw(3) << fSector
      << "region: "     << std::setw(3) << fRegion
      << "superlayer: " << std::setw(3) << fSuperLayer
      << "layer: "      << std::setw(3) << fLayer
      << "wire: "       << std::setw(3) << fWire
      << "channel: "    << std::setw(3) << fChannel
      << "\n";
}
//______________________________________________________________________________


