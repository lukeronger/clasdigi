#include "DVCSKinematics.h"
#include <iostream>

DVCSKinematics::DVCSKinematics() : fSolved(false),
   fVariable(ConstrainedVariable::kPhotonEnergy)
{
   fP1 = {0,0,0,0.938};
   fP2 = {0.2,0,0.2,TMath::Sqrt(0.2*0.2+0.2*0.2+0.938*0.938)};
   fK1.SetXYZT(0.5,0.0,1.0,9.0);
   SetQ2nu(2.0, 9.0);
}
//______________________________________________________________________________
DVCSKinematics::~DVCSKinematics()
{
}
//______________________________________________________________________________
void DVCSKinematics::SetK1(const TLorentzVector& v)
{
   fK1     = v;
   fSolved = false;
}
//______________________________________________________________________________
void DVCSKinematics::SetK2(const TLorentzVector& v)
{
   fK2     = v;
   fSolved = false;
}
//______________________________________________________________________________
void DVCSKinematics::SetP1(const TLorentzVector& v)
{
   fP1     = v;
   fSolved = false;
}
//______________________________________________________________________________
void DVCSKinematics::SetP2(const TLorentzVector& v)
{
   fP2     = v;
   fSolved = false;
}
//______________________________________________________________________________
void   DVCSKinematics::SetQ2(double Q2)
{
   // Adjust the momentum so that the photon energy remains the same.
   // Q2 = q^2 - nu^2
   double nu  = fK1.E();
   TVector3 q = fK1.Vect();
   double q2  = Q2 + nu*nu; //q.Mag2();
   q.SetMag(TMath::Sqrt(q2));
   fK1.SetVect(q);
   fSolved = false;
}
double DVCSKinematics::GetQ2() const 
{
   return -1.0*fK1.Mag2();
}
//______________________________________________________________________________

void   DVCSKinematics::Setnu(double nu, bool Q2fixed)
{
   double Q2 = GetQ2();
   fK1.SetE(nu);
   // keep Q2 fixed
   if( Q2fixed ) {
      TVector3 q = fK1.Vect();
      double q2  = Q2 + nu*nu; //q.Mag2();
      q.SetMag(TMath::Sqrt(q2));
      fK1.SetVect(q);
   }
   fSolved = false;
}
double DVCSKinematics::Getnu() const
{
   return fK1.E();
}
//______________________________________________________________________________
void   DVCSKinematics::SetQ2nu(double Q2,double nu)
{
   Setnu(nu,false);
   SetQ2(Q2);
}

int DVCSKinematics::Solve()
{
   //if( fVariable == ConstrainedVariable::kPhotonEnergy ) {
      TVector3  k2 = fK1.Vect() + fP1.Vect() - fP2.Vect();
      TLorentzVector lhs = (fK1+fP1-fP2);
      k2.Print();
      lhs.Print();
      std::cout << " |k_2|   = " << k2.Mag() << std::endl;;
      std::cout << "  k^2    = " << lhs*lhs   << std::endl;
   //}
   return 0;
}
