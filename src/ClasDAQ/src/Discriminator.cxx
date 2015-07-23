#include "Discriminator.h"
#include <iostream>
#include "TDC.h"

//______________________________________________________________________________
clas12::DAQ::Discriminator::Discriminator(int ch, double thr) : 
   fChannel(ch), fThreshold(thr), fGateWidth(10.0),
   fAccumulated(0.0), fCounted(0.0),
   fTimeFired(0.0), fLatched(false)
{ }
//______________________________________________________________________________
clas12::DAQ::Discriminator::~Discriminator()
{ }
//______________________________________________________________________________
bool clas12::DAQ::Discriminator::Count(double time){

   // Increase the discrimantor count at a given time.
   //
   // Note that this function returns true only when the discriminator fires.
   // This mimics a rising edge trigger behavior.
   //
   // Subsequent calls to count after it has fired will return false until :
   //  - gatewidth amount time has passed
   //  - it was manually reset
   // 
   // Currently the following is assumed:
   //  - Count is called with increasing time (ie order in time)
   //

   fCounted++;

   // See if the latch should be released
   if( ProcessLatch(time) ){
      // If still latched don't fire 
      return false;
   }
   
   // The discriminator is triggered and latched 
   if( !fLatched && fCounted >= fThreshold )
   {
      fTimeFired = time;
      fLatched   = true;

      for( auto callback : fCallbacks ) {
         callback();
      }
      for( auto callback : fTriggerCallbacks ) {
         callback(time);
      }

      return true;
   }

   return false;
}
//______________________________________________________________________________
bool clas12::DAQ::Discriminator::ProcessLatch(double time){
   // If there is no latch return false
   if(!fLatched) return false;

   if( time - fTimeFired >= fGateWidth ) {
      fLatched = false;
      std::cout << "unlatched" << std::endl;
   }
   return fLatched;
}
//______________________________________________________________________________
void clas12::DAQ::Discriminator::Clear(Option_t * )
{
   fAccumulated = 0.0;
   fCounted     = 0;
   fTimeFired   = 0.0;
}
//______________________________________________________________________________
void clas12::DAQ::Discriminator::Print(Option_t * ) const
{
   std::cout << " Discriminator (chan=" << fChannel << ") : " << fThreshold << "\n";
}
//______________________________________________________________________________
clas12::DAQ::TDC& clas12::DAQ::Discriminator::operator>>(TDC& rhs)
{
   rhs.AddStartSignal((*this));
   return rhs;
}
//______________________________________________________________________________
//clas12::DAQ::TDC& clas12::DAQ::operator>>(Discriminator& lhs,TDC& rhs)
//{
//  return lhs.operator>>(rhs);
//}
////______________________________________________________________________________
//clas12::DAQ::TDC& clas12::DAQ::operator<<(TDC& lhs, Discriminator& rhs)
//{
//  return lhs.operator<<(rhs);
//}
//______________________________________________________________________________
