#ifndef ElectronKinematics_HH
#define ElectronKinematics_HH 1

#include <iostream>
#include <iomanip>
#include <tuple>
#include "CLHEP/Units/SystemOfUnits.h"

#include "TMath.h"
#include "TLorentzVector.h"

namespace kinematics {

   class ElectronKinematics {

      public :
         double          fM1 = 0.938;
         double          fM2 = 0.938;
         double          fM0 = 0.0; // Real photon
         TLorentzVector  fp0 = {-0.01,0.0,0.02,TMath::Sqrt(0.01*0.01+0.02*0.02+fM0*fM0)};
         TLorentzVector  fk1 = {0.0     , 0.0, 3.0     , 3.0}; // incident electron
         TLorentzVector  fk2 = {0.353553, 0.0, 0.353553, 0.5}; // scattered electron
         TLorentzVector  fp1 = {0.0     , 0.0, -1.0    , TMath::Sqrt(1+fM1*fM1)}; // incident electron
         TLorentzVector  fp2 = {0.1, 0.0, 0.35, TMath::Sqrt(0.35*0.35+0.1*0.1+fM2*fM2)}; // scattered electron

      public:

         // Use these for setting values
         TLorentzVector&   Get_k1() { return fk1;}
         TLorentzVector&   Get_k2() { return fk2;}
         TLorentzVector&   Get_p0() { return fp0; }
         TLorentzVector&   Get_p1() { return fp1;}
         TLorentzVector&   Get_p2() { return fp2;}

         // Read only access 
         TLorentzVector k1() const { return fk1;}
         TLorentzVector k2() const { return fk2;}
         TLorentzVector p0() const { return fp0;}
         TLorentzVector p1() const { return fp1;}
         TLorentzVector p2() const { return fp2;}
         TLorentzVector q()  const { return (fk1-fk2);}

         double         Q2() const { return( -1.0*(fk1-fk2)*(fk1-fk2) ); }
         double         E1() const { return( fk1.E() ); }
         double         E2() const { return( fk2.E() ); }
         double         nu() const { return( E1()-E2() ); }

         double         s()  const { return( (fp1+fk1)*(fp1+fk1) ); }
         double         t()  const { return( (fp1-fp2)*(fp1-fp2) ); }
         double         Ep1()const { return( fp1.E() ); }
         double         Ep2()const { return( fp2.E() ); }
         double         M1() const { return( fM1 ); }
         double         M2() const { return( fM2 ); }

         TVector3       q_vector() const { return((fk1-fk2).Vect()); }
         double         theta_q()  const { return(q_vector().Theta()); }

         // target in moving frame
         double         x_true()  const  { return( Q2()/(2.0*(fp1*q())));}
         double         t_true()  const { return( (fp1-fp2)*(fp1-fp2) ); }
         double         t_q1q2()  const { return( (q()-fp0)*(q()-fp0) ); }

         // target in rest frame
         double         t_approx()  const { TLorentzVector p1_rest(fM1,0,0,0); return( (p1_rest-fp2)*(p1_rest-fp2) ); }
         //double         t_approx()  const { return( (q()-fp0)*(q()-fp0) ); }
         double         x()  const  { return( Q2()/(2.0*((0.938)*nu())) );}
         double         xA() const  { return( Q2()/(2.0*(fM1*nu())) );}
         double         y()  const  { return( nu()/E1() ) ;}
         double         W()  const  { return( TMath::Sqrt( (TLorentzVector(0,0,0,fM1)+q()).Mag2() ) ) ;}

         // Note: These return the velocity of the frames as viewed from the LAB 
         //       The TLorentzVector::Boost() goes backwards (active) hence the minus sign 
         TVector3       beta_CM_ep() const { return( -1.0*(k1() + p1()).BoostVector() ); }
         TVector3       beta_CM_qp() const { return( -1.0*(q() + p1()).BoostVector() ); }

         double         phi_dvcs() const {
            TVector3 n1 = fk1.Vect().Cross(fk2.Vect());
            TVector3 n2 = fp2.Vect().Cross(fp0.Vect());
            // positive if q2 projection along (k1xk2) is positive. Otherwise it is negative
            double sign = n1*(fp0.Vect());
            if(sign > 0.0 ){
               sign = 1.0;
            }else {
               sign = -1.0;
            }
            return( sign*(n1.Angle(n2)));
         }
         double         t_min() const { return(fM0*fM0 - Q2() + 2.0*E1()*nu() + - 2.0*(q().Vect()*fp0.Vect()));}
         double         t_ion() const { return( t() ); }
         double         t_max() const {
            double m  = M1();
            double v1LAB = nu();
            double k1LAB = k1().Vect().Mag();
            double inv_mass = W();
            double k1 = k1LAB*(m/inv_mass);
            double v1 = inv_mass - TMath::Sqrt(k1*k1 + m*m);
            double tmax    = -Q2() - 2.0*(v1 + k1)*(inv_mass*inv_mass - m*m)/(2.0*inv_mass);
            double minus_s = -s();
            double res = minus_s;
            if( res < minus_s ) {
               res = minus_s;
            }
            return res;
         }

         ClassDef(ElectronKinematics,2)
   };

} 

#endif

