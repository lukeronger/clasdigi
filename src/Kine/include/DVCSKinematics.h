#ifndef DVCSKinematics_HH
#define DVCSKinematics_HH 1

#include "TMath.h"
#include "TLorentzVector.h"

// Fixing the virtual photon four vector k1 for all cases below, we will
// solve the kinematics for the outgoing real photon four vector, k2,
// the initial nucleon, P1, and the outgoing nucleon, P2.
//
// Notation
// --------
// Four vectors:
// K1(nu1,|k1|=k1)
// K2(nu2,|k2|=k2)
// P1(E1, |P1|=p1)
// P2(E2, |P2|=p2)
// 
// Q^2= K1^2 = k1^2-nu1^2
// 
//  There are a few options for which variables to solve for:
//  1) P1 is fixed, p2 direction is fixed. Solve for E2  then K2
//  2) P2 is fixed, p1 direction is fixed. Solve for E1  then K2 
//  3) P2 is fixed, k2 direction is fixed. Solve for nu2 then P1
//  4) K2 is fixed, p2 direction is fixed. Solve for E2  then P1
//  5) P1 is fixed, k2 direction is fixed. Solve for nu2 then P2
//  6) K2 is fixed, p1 direction is fixed. Solve for E1  then P2
// 
//  Cases 1, 2, 4, and 6 have two possible outcomes because t is not 
//  uniquely determined, however, cases 3 and 5 have only one possible 
//  solution. This is becuase we are solving for the energy and momentum of a real photon.
//

class DVCSKinematics {

   public:
      enum class ConstrainedVariable { kCase1, kCase2, kCase3, kCase4, kCase5, kCase6, kNucleonMomentum, kPhotonAngle };

   private:

      bool                 fSolved;
      ConstrainedVariable  fVariable;

      TLorentzVector  fe1; // incident electron
      TLorentzVector  fe2; // scattered electron
      TLorentzVector  fK1; // virtual photon
      TLorentzVector  fK2; // photon
      TLorentzVector  fP1; // target nucleon
      TLorentzVector  fP2; // nucleon

   protected:
      double p2_case1(bool high_t = false);
      double p1_case2(bool high_t = false);
      double k2_case3();
      double p2_case4(bool high_t = false);
      double k2_case5();
      double p1_case6(bool high_t = false);

   public:
      DVCSKinematics();
      virtual ~DVCSKinematics();

      int  Solve();
      void Print();

      void SetConstraint(ConstrainedVariable t) { fVariable = t; }

      void  SetEEprimeTheta(double E0, double Eprime, double theta);
      void  SetK2_PThetaPhi(double k, double theta, double phi = 0);
      void  SetP1_PThetaPhi(double p, double theta, double phi = 0);
      void  SetP2_PThetaPhi(double p, double theta, double phi = 0);

      double GetM1() const { return 0.938 ;}
      double GetM2() const { return 0.938 ;}
      double Gett_min() const;

      void   SetQ2(double Q2);
      double GetQ2() const ;

      void   Setnu(double nu, bool Q2fixed = true);
      double Getnu() const ;

      double Getx()const { return( GetQ2()/(2.0*GetM1()*Getnu()) ); }
      double Gett() const { return( (fP1-fP2)*(fP1-fP2) ); }

      void   SetQ2nu(double Q2,double nu);

      void SetK1(const TLorentzVector& v);
      void SetK2(const TLorentzVector& v);
      void SetP1(const TLorentzVector& v);
      void SetP2(const TLorentzVector& v);


      TLorentzVector e1() const {return fK1;}
      TLorentzVector e2() const {return fK2;}
      TLorentzVector K1() const {return fK1;}
      TLorentzVector K2() const {return fK2;}
      TLorentzVector P1() const {return fP1;}
      TLorentzVector P2() const {return fP2;}

      TLorentzVector Gete1() {return fe1;}
      TLorentzVector Gete2() {return fe2;}
      TLorentzVector GetK1() {return fK1;}
      TLorentzVector GetK2() {return fK2;}
      TLorentzVector GetP1() {return fP1;}
      TLorentzVector GetP2() {return fP2;}

      ClassDef(DVCSKinematics,1)
};


#endif
