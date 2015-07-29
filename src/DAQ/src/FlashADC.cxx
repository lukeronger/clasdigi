#include "FlashADC.h"
#include <iostream>
#include <iomanip>

//______________________________________________________________________________

double clas12::DAQ::pulse_waveform(double t, double tau, double sig) {

   // Returns a pulse waveform that peaks at tau.
   // Has width set by sig.
   // Default values give a peak at x=7.5, y=1
   // with a FWHM of roughly 10.

   if ( t <= 0) {
      return 0.0;
   } else {
      double tmp = std::log(t/tau)/sig;
      return std::exp(-(tmp * tmp)/2.5);
   }
}
//______________________________________________________________________________



clas12::DAQ::FlashADC::FlashADC(int ch) : ModuleChannel(ch),
   fTimeResolution(0.06), fDisc(ch)
{
   AddStopSignal(fDisc);
   // Sample rate is every 4ns  and TC requires previous to be below thresh.
   // So setting the gate width to 5ns  prevents this but not in a detailed way.
   fDisc.fGateWidth = 5;

   int a0 = fNSB - fPulseMax ;
   int a1 = fNSA + fPulseMax ;

   fBuffer.reserve(fTriggerWindow);

   for(int i = 0; i<a0; i++){
      fPulse.push_back( 0.0 );
      //std::cout << i << " " << fPulse[i] << std::endl;
   }
   for(int i = 0; i<a1; i++){
      fPulse.push_back( 2048*clas12::DAQ::pulse_waveform(4.0*i) );
      //std::cout << a0+i << " " << fPulse[a0+i] << std::endl;
   }
   fTCs.clear();
}
//______________________________________________________________________________
clas12::DAQ::FlashADC::~FlashADC()
{ }
//______________________________________________________________________________
void clas12::DAQ::FlashADC::Reset(double t)
{
   fBuffer.clear();
   fTCs.clear();
   fTime    = t;
   fRefTime = t;
   fDisc.Clear();
}
//______________________________________________________________________________
void clas12::DAQ::FlashADC::AddPulseToBuffer(int n, double amp ) {
   // adds a pulse to the buffer with the peak at sample n
   int nbuf    = fBuffer.size();
   int npulse  = fPulse.size();
   if( nbuf - n < npulse ) {
      fBuffer.resize(n+npulse,0.0);
   }
   for(int i=0 ; i<npulse ; i++) {
      if(n-fNSB+i < 0 ) continue;
      fBuffer[n-fNSB+i] += (amp*fPulse[i]);
      //std::cout << n-fPulseMax+i << " " << fBuffer[n-fPulseMax+i] << std::endl;
   }
}
//______________________________________________________________________________
void clas12::DAQ::FlashADC::Stop(double t)
{
   if( fTCs.size() == 0 ) {
      fRefTime    = t;
   }
      //auto i      = std::distance(fBuffer.begin(), fBuffer.end()) + fNSB; 
      //fTCs.push_back( fNSB );
      //AddPulseToBuffer( fNSB);
      //fBuffer.insert( fBuffer.end(), fPulse.begin(), fPulse.end() );
   //} else {
      int  i_peak = fNSB + int((t-fRefTime)/fSampleFreq);
      AddPulseToBuffer( i_peak );
      fTCs.push_back( i_peak );
   //}

   fTime = t;
   //std::cout << "FlashADC::Stop\n";
   //PrintBuffer();
}
//______________________________________________________________________________
void clas12::DAQ::FlashADC::PrintBufferHist(int nY, int peak ) const
{
   for(int j = 0 ; j<=nY; j++) {
      for(int i = 0 ; i<fBuffer.size() && i<80; i++) {
         if( fBuffer[i] > peak*(nY-j)/nY   ) {
            std::cout << '|' ;
         } else {
            std::cout << ' ' ;
         }
      }
      std::cout << std::endl;
   }
}
//______________________________________________________________________________
void clas12::DAQ::FlashADC::PrintBuffer() const
{
   int i = 0;
   for(auto val : fTCs ) {
      std::cout << std::setw(8) << val << " ";
      i++;
      if(i%8==0) std::cout << std::endl;
   }
   std::cout << std::endl;
   i = 0;
   for(auto val : fBuffer ) {
      std::cout << std::setw(8) << val << " ";
      i++;
      if(i%8==0) std::cout << std::endl;
   }
   std::cout << std::endl;
}
//______________________________________________________________________________
void clas12::DAQ::FlashADC::AddStopSignal(Discriminator& d)
{
   // Add callback to discriminator 
   // Note that there is no way to remove these 
   // Todo: think of how to do cleanup 
   d.fTriggerCallbacks.push_back( [this](double t){ this->Stop(t); } );
}
//______________________________________________________________________________
void clas12::DAQ::FlashADC::Clear(Option_t * )
{
   fRefTime   = 0.0;
   fTime      = 0.0;
}
//______________________________________________________________________________
void clas12::DAQ::FlashADC::Print(Option_t *) const 
{
   std::cout << " FlashADC (" << fChannel << ") : "  
      << "RefTime(" << fRefTime <<  "), "
      << "Time(" << fTime <<  "), "
      << "TemRes(" << fTimeResolution <<  ")\n";
   //PrintBuffer();
}
//______________________________________________________________________________

