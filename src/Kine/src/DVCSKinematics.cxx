#include "DVCSKinematics.h"
#include <iostream>
#include "CLHEP/Units/SystemOfUnits.h"

DVCSKinematics::DVCSKinematics() : fSolved(false),
   fVariable(ConstrainedVariable::kPhotonEnergy)
{
   SetP1_PThetaPhi(0.0,0,0);
   SetP2_PThetaPhi(0.3,30.0*CLHEP::degree,130*CLHEP::degree);
   SetEEprimeTheta(11.0,2.0,25.0*CLHEP::degree);
}
//______________________________________________________________________________

DVCSKinematics::~DVCSKinematics()
{
}
//______________________________________________________________________________

void DVCSKinematics::SetEEprimeTheta(double E0, double Eprime, double theta)
{
   double p0 = TMath::Sqrt(E0*E0 - 0.000511*0.000511);
   double pp = TMath::Sqrt(Eprime*Eprime - 0.000511*0.000511);
   fe1 = {0.0,0.0, p0, E0};
   fe2 = {0.0,0.0, pp, Eprime};
   fe2.SetTheta(theta);
   fK1 = fe1 - fe2;
}
void DVCSKinematics::SetP1_PThetaPhi(double p, double theta, double phi)
{
   double E0 = TMath::Sqrt(p*p + GetM1()*GetM1());
   fP1 = {0, 0, p, E0};
   if(p > 0 ){
      fP1.SetTheta(theta);
      fP1.SetPhi(phi);
   }
}
void DVCSKinematics::SetP2_PThetaPhi(double p, double theta, double phi)
{
   double E0 = TMath::Sqrt(p*p + GetM2()*GetM2());
   fP2 = {0, 0, p, E0};
   fP2.SetTheta(theta);
   fP2.SetPhi(phi);
}
//______________________________________________________________________________
double DVCSKinematics::Gett_min() const 
{
   double eps = 4.0*GetM1()*GetM1()*Getx()*Getx()/GetQ2();
   double res = -GetQ2()*2.0*(1.0-Getx())*(1+ eps*eps - TMath::Sqrt(1+eps*eps))/(4.0*Getx()*(1.0-Getx())+eps*eps);
   return res;
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
//______________________________________________________________________________

int DVCSKinematics::Solve()
{
   //if( fVariable == ConstrainedVariable::kPhotonEnergy ) {

   p2_case1();
   TVector3  k2 = fe1.Vect() + fP1.Vect() - fe2.Vect() - fP2.Vect();
   fK2.SetVect(k2);
   fK2.SetE(k2.Mag());
   //}
   return 0;
}
//______________________________________________________________________________
void DVCSKinematics::Print()
{
   fe1.Print();
   fe2.Print();
   fK1.Print();
   fK2.Print();
   fP1.Print();
   fP2.Print();

   std::cout << " Q2          = " << GetQ2() << " (GeV/c)^2" << std::endl;
   std::cout << " nu          = " << Getnu() << " GeV" << std::endl;
   std::cout << " x           = " << Getx()  << "      " << std::endl;
   std::cout << " t           = " << Gett()  << "      " << std::endl;
   std::cout << " t_min       = " << Gett_min()  << "      " << std::endl;
   std::cout << " k1^2        = " << fK1*fK1 << " GeV^2" << std::endl;
   std::cout << " k2^2        = " << fK2*fK2 << " GeV^2" << std::endl;
   std::cout << " sqrt(P1^2)  = " << TMath::Sqrt(fP1*fP1) << " GeV^2" << std::endl;
   std::cout << " sqrt(P2^2)  = " << TMath::Sqrt(fP2*fP2) << " GeV^2" << std::endl;
   std::cout << " sqrt(pe1^2)  = " << TMath::Sqrt(fe1*fe1) << " GeV^2" << std::endl;
   std::cout << " sqrt(pe2^2)  = " << TMath::Sqrt(fe2*fe2) << " GeV^2" << std::endl;
   std::cout << "  s1    = " << (fe1+fP1)*(fe1+fP1)   << std::endl;
   std::cout << "  s2    = " << (fe2+fK2+fP2)*(fe2+fK2+fP2)   << std::endl;
   fe1.Vect().Print();
   fe2.Vect().Print();
   fK1.Vect().Print();
   fK2.Vect().Print();
   fP1.Vect().Print();
   fP2.Vect().Print();

}
//______________________________________________________________________________

double DVCSKinematics::p2_case1(){
   using namespace TMath;
   double Q2  = GetQ2();
   double M1  = GetM1();
   double M2  = GetM2();
   double p1  = fP1.Vect().Mag();
   double k1  = fK1.Vect().Mag();
   double nu1 = fK1.E();
   double cosThetaK1P2 = Cos( fK1.Vect().Angle( fP2.Vect() ) );
   double cosThetaP1P2 = Cos( fP1.Vect().Angle( fP2.Vect() ) );
   double cosThetaK1P1 = Cos( fK1.Vect().Angle( fP1.Vect() ) );

   double sqrt_term = (Power(4*cosThetaK1P2*k1*Power(M1,2) + 4*cosThetaK1P2*k1*Power(M2,2) - 8*cosThetaK1P1*cosThetaK1P2*Power(k1,2)*p1 + 
               4*cosThetaP1P2*Power(M1,2)*p1 + 4*cosThetaP1P2*Power(M2,2)*p1 - 8*cosThetaK1P1*cosThetaP1P2*k1*Power(p1,2) + 
               8*cosThetaK1P2*k1*nu1*Sqrt(Power(M1,2) + Power(p1,2)) + 8*cosThetaP1P2*nu1*p1*Sqrt(Power(M1,2) + Power(p1,2)) - 
               4*cosThetaK1P2*k1*Q2 - 4*cosThetaP1P2*p1*Q2,2) - 
            4*(4*Power(cosThetaK1P2,2)*Power(k1,2) - 4*Power(nu1,2) + 8*cosThetaK1P2*cosThetaP1P2*k1*p1 + 
               4*Power(cosThetaP1P2,2)*Power(p1,2) - 8*nu1*Sqrt(Power(M1,2) + Power(p1,2)) - 4*(Power(M1,2) + Power(p1,2)))*
            (Power(M1,4) + 2*Power(M1,2)*Power(M2,2) + Power(M2,4) - 4*Power(M2,2)*Power(nu1,2) - 
             4*cosThetaK1P1*k1*Power(M1,2)*p1 - 4*cosThetaK1P1*k1*Power(M2,2)*p1 + 
             4*Power(cosThetaK1P1,2)*Power(k1,2)*Power(p1,2) + 4*Power(M1,2)*nu1*Sqrt(Power(M1,2) + Power(p1,2)) - 
             4*Power(M2,2)*nu1*Sqrt(Power(M1,2) + Power(p1,2)) - 8*cosThetaK1P1*k1*nu1*p1*Sqrt(Power(M1,2) + Power(p1,2)) - 
             4*Power(M2,2)*(Power(M1,2) + Power(p1,2)) + 4*Power(nu1,2)*(Power(M1,2) + Power(p1,2)) - 2*Power(M1,2)*Q2 - 
             2*Power(M2,2)*Q2 + 4*cosThetaK1P1*k1*p1*Q2 - 4*nu1*Sqrt(Power(M1,2) + Power(p1,2))*Q2 + Power(Q2,2)));

   //if(sqrt_term < 0.0) sqrt_term *= -1.0;

   double sol = (-4*cosThetaK1P2*k1*Power(M1,2) - 4*cosThetaK1P2*k1*Power(M2,2) + 8*cosThetaK1P1*cosThetaK1P2*Power(k1,2)*p1 - 
         4*cosThetaP1P2*Power(M1,2)*p1 - 4*cosThetaP1P2*Power(M2,2)*p1 + 8*cosThetaK1P1*cosThetaP1P2*k1*Power(p1,2) - 
         8*cosThetaK1P2*k1*nu1*Sqrt(Power(M1,2) + Power(p1,2)) - 8*cosThetaP1P2*nu1*p1*Sqrt(Power(M1,2) + Power(p1,2)) + 
         4*cosThetaK1P2*k1*Q2 + 4*cosThetaP1P2*p1*Q2 - 
         Sqrt(sqrt_term))/
      (2.*(4*Power(cosThetaK1P2,2)*Power(k1,2) - 4*Power(nu1,2) + 8*cosThetaK1P2*cosThetaP1P2*k1*p1 + 
           4*Power(cosThetaP1P2,2)*Power(p1,2) - 8*nu1*Sqrt(Power(M1,2) + Power(p1,2)) - 4*(Power(M1,2) + Power(p1,2))));

   double sol2 = (-4*cosThetaK1P2*k1*Power(M1,2) - 4*cosThetaK1P2*k1*Power(M2,2) + 8*cosThetaK1P1*cosThetaK1P2*Power(k1,2)*p1 - 
         4*cosThetaP1P2*Power(M1,2)*p1 - 4*cosThetaP1P2*Power(M2,2)*p1 + 8*cosThetaK1P1*cosThetaP1P2*k1*Power(p1,2) - 
         8*cosThetaK1P2*k1*nu1*Sqrt(Power(M1,2) + Power(p1,2)) - 8*cosThetaP1P2*nu1*p1*Sqrt(Power(M1,2) + Power(p1,2)) + 
         4*cosThetaK1P2*k1*Q2 + 4*cosThetaP1P2*p1*Q2 + 
         Sqrt(sqrt_term))/
      (2.*(4*Power(cosThetaK1P2,2)*Power(k1,2) - 4*Power(nu1,2) + 8*cosThetaK1P2*cosThetaP1P2*k1*p1 + 
           4*Power(cosThetaP1P2,2)*Power(p1,2) - 8*nu1*Sqrt(Power(M1,2) + Power(p1,2)) - 4*(Power(M1,2) + Power(p1,2))));

   std::cout << " P2 solution = " << sol << std::endl;
   std::cout << " sol2        = " << sol2 << std::endl;
   TVector3 p2_vec = fP2.Vect();
   p2_vec.SetMag(sol2);
   fP2.SetVect(p2_vec);
   fP2.SetE(TMath::Sqrt(sol2*sol2+GetM2()*GetM2()));

   return sol2;
}
