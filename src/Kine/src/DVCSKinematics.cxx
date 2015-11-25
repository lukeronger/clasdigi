#include "DVCSKinematics.h"
#include <iostream>
#include "CLHEP/Units/SystemOfUnits.h"

DVCSKinematics::DVCSKinematics() : fSolved(false),
   fVariable(ConstrainedVariable::kCase5)
{
   SetEEprimeTheta(11.0,2.0,25.0*CLHEP::degree);
   //SetK2_PThetaPhi(2.0,20.0*CLHEP::degree,180*CLHEP::degree);
   //SetP1_PThetaPhi(0.2,180.0*CLHEP::degree,0);
   //SetP2_PThetaPhi(0.3,30.0*CLHEP::degree,180*CLHEP::degree);

   fK2 = {-0.841946,0.000000,8.981686,9.021062};
   fP1 = {0.000000,0.000000,-0.200000,0.959085};
   fP2 = {-0.003290,0.000000,0.005698,0.938023};
   SetM1(0.938);
   SetM2(0.938);
}
//______________________________________________________________________________

DVCSKinematics::~DVCSKinematics()
{
}
//______________________________________________________________________________

void DVCSKinematics::SetEEprimeTheta(double E0, double Eprime, double theta)
{
   double p0 = TMath::Sqrt(    E0*E0     - 0.000511*0.000511);
   double pp = TMath::Sqrt(Eprime*Eprime - 0.000511*0.000511);
   fe1 = {0.0,0.0, p0, E0};
   fe2 = {0.0,0.0, pp, Eprime};
   fe2.SetTheta(theta);
   fK1 = fe1 - fe2;
}
//______________________________________________________________________________

void DVCSKinematics::SetK2_PThetaPhi(double k, double theta, double phi)
{
   fK2 = {0, 0, k, k};
   if(k > 0 ){
      fK2.SetTheta(theta);
      fK2.SetPhi(phi);
   }
}
//______________________________________________________________________________

void DVCSKinematics::SetP1_PThetaPhi(double p, double theta, double phi)
{
   double m = GetM1();
   double E0 = TMath::Sqrt(p*p + m*m);
   fP1 = {0, 0, p, E0};
   if(p > 0 ){
      fP1.SetTheta(theta);
      fP1.SetPhi(phi);
   }
}
//______________________________________________________________________________

void DVCSKinematics::SetP2_PThetaPhi(double p, double theta, double phi)
{
   double m = GetM2();
   double E0 = TMath::Sqrt(p*p + m*m);
   fP2 = {0, 0, p, E0};
   fP2.SetTheta(theta);
   fP2.SetPhi(phi);
}
//______________________________________________________________________________

void DVCSKinematics::SetM1(double m)
{
  double p = fP1.P(); 
  double E = TMath::Sqrt(p*p + m*m);
  fP1.SetE(E);
}
//______________________________________________________________________________

void DVCSKinematics::SetM2(double m)
{
  double p = fP2.P(); 
  double E = TMath::Sqrt(p*p + m*m);
  fP2.SetE(E);
}
//______________________________________________________________________________

double DVCSKinematics::Gett_min() const 
{
   double m  = GetM1();
   double m2 = GetM2();
   double Q2   = GetQ2();
   double W2   = GetW2();
   double W    = TMath::Sqrt(W2);
   double v1LAB = fK1.E();
   double k1LAB = fK1.Vect().Mag();
   double k1 = k1LAB*(m/W);
   double v1 = W - TMath::Sqrt(k1*k1 + m2*m2);
   //double nu   = Getnu();
   //double eps2 = Q2/(nu*nu);
   //double x    = Getx();
   //double res = -Q2*(2.0*(1.0-x)*(1.0-TMath::Sqrt(1.0+eps2)) + eps2 )/(4.0*x*(1.0-x) + eps2);
   double tmin = -Q2 - 2.0*(v1 - k1)*(W2 - m*m)/(2.0*W);
   //std::cout << " diff: " << res - tmin << std::endl;
   return tmin;
}
//______________________________________________________________________________

double DVCSKinematics::Gett_max() const 
{
   double m  = GetM1();
   double Q2 = GetQ2();
   double x  = Getx();
   double W2 = GetW2();
   double W  = TMath::Sqrt(W2);
   double v1LAB = fK1.E();
   double k1LAB = fK1.Vect().Mag();
   double k1 = k1LAB*(m/W);
   double v1 = W - TMath::Sqrt(k1*k1 + m*m);
   double tmax    = -Q2 - 2.0*(v1 + k1)*(W2 - m*m)/(2.0*W);
   double minus_s = -W2;
   double res = tmax;
   if( res < minus_s ) {
      res = minus_s;
   }
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
//______________________________________________________________________________

void   DVCSKinematics::SetQ2nu(double Q2,double nu)
{
   Setnu(nu,false);
   SetQ2(Q2);
}
//______________________________________________________________________________

double DVCSKinematics::Getx()  const {
   return( GetQ2()/(2.0*GetM1()*Getnu()) );
}
//______________________________________________________________________________

double DVCSKinematics::GetQ2() const 
{
   return -1.0*(fK1*fK1);
}
//______________________________________________________________________________

double DVCSKinematics::Getnu() const
{
   return fK1.E();
}
//______________________________________________________________________________

double DVCSKinematics::GetW2() const {
   double m  = GetM1();
   double Q2 = GetQ2();
   double x  = Getx();
   return( m*m - Q2 + Q2/x );
}
//______________________________________________________________________________

int DVCSKinematics::Solve()
{
   if( fVariable == ConstrainedVariable::kCase1 ) {
      p2_case1();
   } else if( fVariable == ConstrainedVariable::kCase2 ) {
      p1_case2();
   } else if( fVariable == ConstrainedVariable::kCase3 ) {
      k2_case3();
   } else if( fVariable == ConstrainedVariable::kCase4 ) {
      p2_case4();
   } else if( fVariable == ConstrainedVariable::kCase5 ) {
      k2_case5();
   } else if( fVariable == ConstrainedVariable::kCase6 ) {
      p1_case6();
   } else {
      p2_case1();
   }
   return 0;
}
//______________________________________________________________________________

void DVCSKinematics::Print()
{
   std::cout << "e1 "; fe1.Print();
   std::cout << "e2 "; fe2.Print();
   std::cout << "K1 "; fK1.Print();
   std::cout << "K2 "; fK2.Print();
   std::cout << "P1 "; fP1.Print();
   std::cout << "P2 "; fP2.Print();

   std::cout << " M1          = " << GetM1() << " GeV" << std::endl;
   std::cout << " M2          = " << GetM2() << " GeV" << std::endl;
   std::cout << " Q2          = " << GetQ2() << " (GeV/c)^2" << std::endl;
   std::cout << " nu          = " << Getnu() << " GeV" << std::endl;
   std::cout << " x           = " << Getx()  << "      " << std::endl;
   std::cout << " t           = " << Gett()  << "      " << std::endl;
   std::cout << " t_min       = " << Gett_min()  << "      " << std::endl;
   std::cout << " t_max       = " << Gett_max()  << "      " << std::endl;
   std::cout << " W2          = " << GetW2()  << "      " << std::endl;
   std::cout << " k1^2        = " << fK1*fK1 << " GeV^2" << std::endl;
   std::cout << " k2^2        = " << fK2*fK2 << " GeV^2" << std::endl;
   std::cout << " sqrt(P1^2)  = " << TMath::Sqrt(fP1*fP1) << " GeV^2" << std::endl;
   std::cout << " sqrt(P2^2)  = " << TMath::Sqrt(fP2*fP2) << " GeV^2" << std::endl;
   std::cout << " sqrt(pe1^2) = " << TMath::Sqrt(fe1*fe1) << " GeV^2" << std::endl;
   std::cout << " sqrt(pe2^2) = " << TMath::Sqrt(fe2*fe2) << " GeV^2" << std::endl;
   std::cout << " s1          = " << (fe1-fe2+fP1)*(fe1-fe2+fP1)   << std::endl;
   std::cout << " s1          = " << (fK1+fP1)*(fK1+fP1)   << std::endl;
   std::cout << " s2          = " << (fK2+fP2)*(fK2+fP2)   << std::endl;
   std::cout << "e1 "; fe1.Vect().Print();
   std::cout << "e2 "; fe2.Vect().Print();
   std::cout << "K1 "; fK1.Vect().Print();
   std::cout << "K2 "; fK2.Vect().Print();
   std::cout << "P1 "; fP1.Vect().Print();
   std::cout << "P2 "; fP2.Vect().Print();

}
//______________________________________________________________________________

double DVCSKinematics::p2_case1(bool high_t){
//  1) P1 is fixed, p2 direction is fixed. Solve for E2  then K2
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

   std::cout << " sol1  = " << sol << std::endl;
   std::cout << " sol2  = " << sol2 << std::endl;

   double p = sol2;
   if( high_t ) {
      p = sol;
   }

   double m = GetM2();
   TVector3 p2_vec = fP2.Vect();
   p2_vec.SetMag(p);
   fP2.SetVect(p2_vec);
   fP2.SetE(TMath::Sqrt(p*p + m*m));

   TVector3  k2 = fe1.Vect() + fP1.Vect() - fe2.Vect() - fP2.Vect();
   fK2.SetVect(k2);
   fK2.SetE(k2.Mag());

   return p;
}
//______________________________________________________________________________

double DVCSKinematics::p1_case2(bool high_t)
{
   //  2) P2 is fixed, p1 direction is fixed. Solve for E1  then K2 

   // Need direction vector to be nonzero
   if( fP1.Vect().Mag() == 0.0 ){
      fP1.SetVect({0,0,-1.0});
   }
   using namespace TMath;
   double Q2  = GetQ2();
   double M1  = GetM1();
   double M2  = GetM2();
   double p2  = fP2.Vect().Mag();
   double E2  = fP2.E();
   double k1  = fK1.Vect().Mag();
   double nu1 = fK1.E();
   double cosThetaK1P2 = Cos( fK1.Vect().Angle( fP2.Vect() ) );
   double cosThetaP1P2 = Cos( fP1.Vect().Angle( fP2.Vect() ) );
   double cosThetaK1P1 = Cos( fK1.Vect().Angle( fP1.Vect() ) );

   double sqrt_term = (Power(-4*cosThetaK1P1*k1*Power(M1,2) - 4*cosThetaK1P1*k1*Power(M2,2) + 8*cosThetaK1P1*E2*k1*nu1 - 
            8*cosThetaK1P1*cosThetaK1P2*Power(k1,2)*p2 + 4*cosThetaP1P2*Power(M1,2)*p2 + 4*cosThetaP1P2*Power(M2,2)*p2 - 
            8*cosThetaP1P2*E2*nu1*p2 + 8*cosThetaK1P2*cosThetaP1P2*k1*Power(p2,2) + 4*cosThetaK1P1*k1*Q2 - 4*cosThetaP1P2*p2*Q2,2)
         - 4*(-4*Power(E2,2) + 4*Power(cosThetaK1P1,2)*Power(k1,2) + 8*E2*nu1 - 4*Power(nu1,2) - 
            8*cosThetaK1P1*cosThetaP1P2*k1*p2 + 4*Power(cosThetaP1P2,2)*Power(p2,2))*
         (-4*Power(E2,2)*Power(M1,2) + Power(M1,4) + 2*Power(M1,2)*Power(M2,2) + Power(M2,4) + 4*E2*Power(M1,2)*nu1 - 
          4*E2*Power(M2,2)*nu1 + 4*Power(E2,2)*Power(nu1,2) - 4*Power(M1,2)*Power(nu1,2) + 4*cosThetaK1P2*k1*Power(M1,2)*p2 + 
          4*cosThetaK1P2*k1*Power(M2,2)*p2 - 8*cosThetaK1P2*E2*k1*nu1*p2 + 4*Power(cosThetaK1P2,2)*Power(k1,2)*Power(p2,2) - 
          2*Power(M1,2)*Q2 - 2*Power(M2,2)*Q2 + 4*E2*nu1*Q2 - 4*cosThetaK1P2*k1*p2*Q2 + Power(Q2,2)));

   //if(sqrt_term < 0.0) sqrt_term *= -1.0;

   double sol = (4*cosThetaK1P1*k1*Power(M1,2) + 4*cosThetaK1P1*k1*Power(M2,2) - 8*cosThetaK1P1*E2*k1*nu1 + 
         8*cosThetaK1P1*cosThetaK1P2*Power(k1,2)*p2 - 4*cosThetaP1P2*Power(M1,2)*p2 - 4*cosThetaP1P2*Power(M2,2)*p2 + 
         8*cosThetaP1P2*E2*nu1*p2 - 8*cosThetaK1P2*cosThetaP1P2*k1*Power(p2,2) - 4*cosThetaK1P1*k1*Q2 + 4*cosThetaP1P2*p2*Q2 + 
         Sqrt(sqrt_term))/
      (2.*(-4*Power(E2,2) + 4*Power(cosThetaK1P1,2)*Power(k1,2) + 8*E2*nu1 - 4*Power(nu1,2) - 8*cosThetaK1P1*cosThetaP1P2*k1*p2 + 
           4*Power(cosThetaP1P2,2)*Power(p2,2)));

   double sol2 = (4*cosThetaK1P1*k1*Power(M1,2) + 4*cosThetaK1P1*k1*Power(M2,2) - 8*cosThetaK1P1*E2*k1*nu1 + 
         8*cosThetaK1P1*cosThetaK1P2*Power(k1,2)*p2 - 4*cosThetaP1P2*Power(M1,2)*p2 - 4*cosThetaP1P2*Power(M2,2)*p2 + 
         8*cosThetaP1P2*E2*nu1*p2 - 8*cosThetaK1P2*cosThetaP1P2*k1*Power(p2,2) - 4*cosThetaK1P1*k1*Q2 + 4*cosThetaP1P2*p2*Q2 - 
         Sqrt(sqrt_term))/
      (2.*(-4*Power(E2,2) + 4*Power(cosThetaK1P1,2)*Power(k1,2) + 8*E2*nu1 - 4*Power(nu1,2) - 8*cosThetaK1P1*cosThetaP1P2*k1*p2 + 
           4*Power(cosThetaP1P2,2)*Power(p2,2)));


   std::cout << " P1 solution = " << sol << std::endl;
   std::cout << " sol2        = " << sol2 << std::endl;

   double p = sol2;
   if( high_t ) {
      p = sol;
   }

   TVector3 p1_vec = fP1.Vect();
   p1_vec.SetMag(p);
   fP1.SetVect(p1_vec);
   fP1.SetE(TMath::Sqrt(p*p + GetM1()*GetM1()));

   TVector3  k2 = fe1.Vect() + fP1.Vect() - fe2.Vect() - fP2.Vect();
   fK2.SetVect(k2);
   fK2.SetE(k2.Mag());

   return p;
}
//______________________________________________________________________________

double DVCSKinematics::k2_case3()
{
   //  3) P2 is fixed, k2 direction is fixed. Solve for nu2 then P1
   using namespace TMath;
   double Q2  = GetQ2();
   double M1  = GetM1();
   double M2  = GetM2();
   double p2  = fP2.Vect().Mag();
   double E2  = fP2.E();
   double k1  = fK1.Vect().Mag();
   double nu1 = fK1.E();
   double cosThetaP2K1 = Cos( fP2.Vect().Angle( fK1.Vect() ) );
   double cosThetaK1K2 = Cos( fK1.Vect().Angle( fK2.Vect() ) );
   double cosThetaP2K2 = Cos( fP2.Vect().Angle( fK2.Vect() ) );

   double k = (Power(M1,2) - Power(M2,2) + 2*E2*nu1 - 2*cosThetaP2K1*k1*p2 + Q2)/(2.*(E2 + cosThetaK1K2*k1 - nu1 - cosThetaP2K2*p2));

   std::cout << " k sol        = " << k << std::endl;

   TVector3 k2_vec = fK2.Vect();
   k2_vec.SetMag(k);
   fK2.SetVect(k2_vec);
   fK2.SetE(k);

   TVector3  p1 = fe2.Vect() + fP2.Vect() - fe1.Vect() + fK2.Vect();
   fP1.SetVect(p1);
   fP1.SetE( Sqrt(p1.Mag2() + GetM1()*GetM1()) );

   return k;
}
//______________________________________________________________________________
double DVCSKinematics::p2_case4(bool high_t)
{
   //  4) K2 is fixed, p2 direction is fixed. Solve for E2  then P1
   using namespace TMath;
   double Q2  = GetQ2();
   double M1  = GetM1();
   double M2  = GetM2();
   //double p2  = fP2.Vect().Mag();
   //double E2  = fP2.E();
   double k2  = fK2.Vect().Mag();
   double k1  = fK1.Vect().Mag();
   double nu1 = fK1.E();
   double cosThetaK1K2 = Cos( fK1.Vect().Angle( fK2.Vect() ) );
   double cosThetaP2K1 = Cos( fP2.Vect().Angle( fK1.Vect() ) );
   double cosThetaP2K2 = Cos( fP2.Vect().Angle( fK2.Vect() ) );

   double sqrt_term = (Power(-8*cosThetaK1K2*k1*Power(k2,2) + 4*k2*Power(M1,2) - 4*k2*Power(M2,2) + 8*cosThetaK1K2*k1*k2*nu1 + 
               8*Power(k2,2)*nu1 - 4*Power(M1,2)*nu1 + 4*Power(M2,2)*nu1 - 8*k2*Power(nu1,2) + 4*k2*Q2 - 4*nu1*Q2,2) - 
            4*(4*Power(cosThetaP2K1,2)*Power(k1,2) - 8*cosThetaP2K1*cosThetaP2K2*k1*k2 - 4*Power(k2,2) + 
               4*Power(cosThetaP2K2,2)*Power(k2,2) + 8*k2*nu1 - 4*Power(nu1,2))*
            (-4*Power(cosThetaK1K2,2)*Power(k1,2)*Power(k2,2) + 4*cosThetaK1K2*k1*k2*Power(M1,2) - Power(M1,4) - 
             4*Power(cosThetaP2K1,2)*Power(k1,2)*Power(M2,2) - 4*cosThetaK1K2*k1*k2*Power(M2,2) + 
             8*cosThetaP2K1*cosThetaP2K2*k1*k2*Power(M2,2) - 4*Power(cosThetaP2K2,2)*Power(k2,2)*Power(M2,2) + 
             2*Power(M1,2)*Power(M2,2) - Power(M2,4) + 8*cosThetaK1K2*k1*Power(k2,2)*nu1 - 4*k2*Power(M1,2)*nu1 + 
             4*k2*Power(M2,2)*nu1 - 4*Power(k2,2)*Power(nu1,2) + 4*cosThetaK1K2*k1*k2*Q2 - 2*Power(M1,2)*Q2 + 2*Power(M2,2)*Q2 - 
             4*k2*nu1*Q2 - Power(Q2,2)));

   double sol = (8*cosThetaK1K2*k1*Power(k2,2) - 4*k2*Power(M1,2) + 4*k2*Power(M2,2) - 8*cosThetaK1K2*k1*k2*nu1 - 8*Power(k2,2)*nu1 + 
         4*Power(M1,2)*nu1 - 4*Power(M2,2)*nu1 + 8*k2*Power(nu1,2) - 4*k2*Q2 + 4*nu1*Q2 - 
         Sqrt(sqrt_term))/
      (2.*(4*Power(cosThetaP2K1,2)*Power(k1,2) - 8*cosThetaP2K1*cosThetaP2K2*k1*k2 - 4*Power(k2,2) + 
           4*Power(cosThetaP2K2,2)*Power(k2,2) + 8*k2*nu1 - 4*Power(nu1,2)));

   double sol2 = (8*cosThetaK1K2*k1*Power(k2,2) - 4*k2*Power(M1,2) + 4*k2*Power(M2,2) - 8*cosThetaK1K2*k1*k2*nu1 - 8*Power(k2,2)*nu1 + 
         4*Power(M1,2)*nu1 - 4*Power(M2,2)*nu1 + 8*k2*Power(nu1,2) - 4*k2*Q2 + 4*nu1*Q2 + 
         Sqrt(sqrt_term))/
      (2.*(4*Power(cosThetaP2K1,2)*Power(k1,2) - 8*cosThetaP2K1*cosThetaP2K2*k1*k2 - 4*Power(k2,2) + 
           4*Power(cosThetaP2K2,2)*Power(k2,2) + 8*k2*nu1 - 4*Power(nu1,2)));

   std::cout << " P1 solution = " << sol << std::endl;
   std::cout << " sol2        = " << sol2 << std::endl;

   double E2 = sol2;
   if( high_t ) {
      E2 = sol;
   }

   double p2 = TMath::Sqrt(E2*E2 - GetM2()*GetM2());

   TVector3 p2_vec = fP2.Vect();
   p2_vec.SetMag(p2);
   fP2.SetVect(p2_vec);
   fP2.SetE(E2);

   TVector3  p1 = fe2.Vect() + fP2.Vect() - fe1.Vect() + fK2.Vect();
   fP1.SetVect(p1);
   fP1.SetE(TMath::Sqrt(p1*p1 + GetM1()*GetM1()));

   return p2;
}
//______________________________________________________________________________
double DVCSKinematics::k2_case5()
{
   //  5) P1 is fixed, k2 direction is fixed. Solve for nu2 then P2
   using namespace TMath;
   double Q2  = GetQ2();
   double M1  = GetM1();
   double M2  = GetM2();
   double p1  = fP1.Vect().Mag();
   double E1  = fP1.E();
   double k1  = fK1.Vect().Mag();
   double nu1 = fK1.E();
   double cosThetaP1K1 = Cos( fP1.Vect().Angle( fK1.Vect() ) );
   double cosThetaK1K2 = Cos( fK1.Vect().Angle( fK2.Vect() ) );
   double cosThetaP1K2 = Cos( fP1.Vect().Angle( fK2.Vect() ) );

   double k2 = (Power(M1,2) - 2*cosThetaP1K1*k1*Sqrt(Power(E1,2) - Power(M1,2)) - Power(M2,2) + 2*E1*nu1 - Q2)/
        (2.*(E1 - cosThetaK1K2*k1 - cosThetaP1K2*Sqrt(Power(E1,2) - Power(M1,2)) + nu1)); 

   TVector3 k2_vec = fK2.Vect();
   k2_vec.SetMag(k2);
   fK2.SetVect(k2_vec);
   fK2.SetE(k2);

   TVector3  p2 = fe1.Vect() + fP1.Vect() - fe2.Vect() - fK2.Vect();
   fP2.SetVect(p2);
   fP2.SetE( Sqrt(p2.Mag2() + GetM2()*GetM2()) );

   return k2;
}
//______________________________________________________________________________
double DVCSKinematics::p1_case6(bool high_t)
{
   //  6) K2 is fixed, p1 direction is fixed. Solve for E1  then P2
   using namespace TMath;
   double Q2  = GetQ2();
   double M1  = GetM1();
   double M2  = GetM2();
   double k2  = fK2.Vect().Mag();
   double k1  = fK1.Vect().Mag();
   double nu1 = fK1.E();
   double cosThetaK1K2 = Cos( fK1.Vect().Angle( fK2.Vect() ) );
   double cosThetaP1K1 = Cos( fP1.Vect().Angle( fK1.Vect() ) );
   double cosThetaP1K2 = Cos( fP1.Vect().Angle( fK2.Vect() ) );

   double sqrt_term = (Power(8*cosThetaK1K2*k1*Power(k2,2) + 4*k2*Power(M1,2) - 4*k2*Power(M2,2) - 8*cosThetaK1K2*k1*k2*nu1 - 
               8*Power(k2,2)*nu1 - 4*Power(M1,2)*nu1 + 4*Power(M2,2)*nu1 + 8*k2*Power(nu1,2) - 4*k2*Q2 + 4*nu1*Q2,2) - 
            4*(4*Power(cosThetaP1K1,2)*Power(k1,2) - 8*cosThetaP1K1*cosThetaP1K2*k1*k2 - 4*Power(k2,2) + 
               4*Power(cosThetaP1K2,2)*Power(k2,2) + 8*k2*nu1 - 4*Power(nu1,2))*
            (-4*Power(cosThetaK1K2,2)*Power(k1,2)*Power(k2,2) - 4*Power(cosThetaP1K1,2)*Power(k1,2)*Power(M1,2) - 
             4*cosThetaK1K2*k1*k2*Power(M1,2) + 8*cosThetaP1K1*cosThetaP1K2*k1*k2*Power(M1,2) - 
             4*Power(cosThetaP1K2,2)*Power(k2,2)*Power(M1,2) - Power(M1,4) + 4*cosThetaK1K2*k1*k2*Power(M2,2) + 
             2*Power(M1,2)*Power(M2,2) - Power(M2,4) + 8*cosThetaK1K2*k1*Power(k2,2)*nu1 + 4*k2*Power(M1,2)*nu1 - 
             4*k2*Power(M2,2)*nu1 - 4*Power(k2,2)*Power(nu1,2) + 4*cosThetaK1K2*k1*k2*Q2 + 2*Power(M1,2)*Q2 - 2*Power(M2,2)*Q2 - 
             4*k2*nu1*Q2 - Power(Q2,2)));
   double sol = (-8*cosThetaK1K2*k1*Power(k2,2) - 4*k2*Power(M1,2) + 4*k2*Power(M2,2) + 8*cosThetaK1K2*k1*k2*nu1 + 8*Power(k2,2)*nu1 + 
         4*Power(M1,2)*nu1 - 4*Power(M2,2)*nu1 - 8*k2*Power(nu1,2) + 4*k2*Q2 - 4*nu1*Q2 - 
         Sqrt(sqrt_term))/
      (2.*(4*Power(cosThetaP1K1,2)*Power(k1,2) - 8*cosThetaP1K1*cosThetaP1K2*k1*k2 - 4*Power(k2,2) + 
           4*Power(cosThetaP1K2,2)*Power(k2,2) + 8*k2*nu1 - 4*Power(nu1,2)));

   double sol2 = (-8*cosThetaK1K2*k1*Power(k2,2) - 4*k2*Power(M1,2) + 4*k2*Power(M2,2) + 8*cosThetaK1K2*k1*k2*nu1 + 8*Power(k2,2)*nu1 + 
         4*Power(M1,2)*nu1 - 4*Power(M2,2)*nu1 - 8*k2*Power(nu1,2) + 4*k2*Q2 - 4*nu1*Q2 + 
         Sqrt(sqrt_term))/
      (2.*(4*Power(cosThetaP1K1,2)*Power(k1,2) - 8*cosThetaP1K1*cosThetaP1K2*k1*k2 - 4*Power(k2,2) + 
           4*Power(cosThetaP1K2,2)*Power(k2,2) + 8*k2*nu1 - 4*Power(nu1,2)));

   std::cout << " P1 solution = " << sol << std::endl;
   std::cout << " sol2        = " << sol2 << std::endl;

   double E1 = sol2;
   if( high_t ) {
      E1 = sol;
   }

   double p1 = TMath::Sqrt(E1*E1 - GetM1()*GetM1());

   TVector3 p1_vec = fP1.Vect();
   p1_vec.SetMag(p1);
   fP1.SetVect(p1_vec);
   fP1.SetE(E1);

   TVector3  p2 = fe1.Vect() + fP1.Vect() - fe2.Vect() - fK2.Vect();
   fP2.SetVect(p2);
   fP2.SetE( Sqrt(p2.Mag2() + GetM2()*GetM2()) );


   return p1;
}
//______________________________________________________________________________
