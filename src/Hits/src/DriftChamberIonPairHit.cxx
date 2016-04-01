#include "DriftChamberIonPairHit.h"
#include <iostream>
#include "TRandom3.h"

double clas12::hits::P_j_ion_pair(double y, int j, double k) {
   // using 1 - \bar{P} as probabilty of ion pair
   return 1.0 - TMath::Exp(-2.0*k*y);
}
//______________________________________________________________________________
bool clas12::hits::does_step_create_ion_pair(double y, int j, double k) {
   // TRandom::Exp(tau)  Returns an exponential deviate exp( -t/tau )
   // Todo: check this
   double prob = clas12::hits::P_j_ion_pair(y,j,k);
   double uni  = gRandom->Uniform();
   //std::cout << "step(prob,uni) = " << y << " (" << prob << ", " << uni <<  ")\n";
   if( uni <= prob ) return true;
   return false;
}

//______________________________________________________________________________

clas12::hits::DriftChamberIonPairHit::DriftChamberIonPairHit(
      double x,double y,double z,double t) : 
   fStepLength(0.0), fChannel(0), fPDGCode(0), fTrackID(0),
   fPosition(x,y,z,t), fGlobalPosition(0,0,0,0)
{ }
//______________________________________________________________________________

clas12::hits::DriftChamberIonPairHit::~DriftChamberIonPairHit() { }
//______________________________________________________________________________

void clas12::hits::DriftChamberIonPairHit::Print() {
   std::cout << " Step Length : " << fStepLength << std::endl;
   std::cout << " PDG code    : " << fPDGCode    << std::endl;
}
//______________________________________________________________________________

