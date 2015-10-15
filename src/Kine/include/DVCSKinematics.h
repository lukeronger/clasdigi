#ifndef DVCSKinematics_HH
#define DVCSKinematics_HH 1

#include "TMath.h"
#include "TLorentzVector.h"

class DVCSKinematics {

   public:
      enum class ConstrainedVariable { kPhotonEnergy, kPhotonAngle };

   private:

      bool                 fSolved;
      ConstrainedVariable  fVariable;

      TLorentzVector  fe1; // incident electron
      TLorentzVector  fe2; // scattered electron
      TLorentzVector  fK1; // virtual photon
      TLorentzVector  fK2; // photon
      TLorentzVector  fP1; // target nucleon
      TLorentzVector  fP2; // nucleon

   public:
      DVCSKinematics();
      virtual ~DVCSKinematics();

      int  Solve();
      void Print();

      void  SetEEprimeTheta(double E0, double Eprime, double theta);
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

      double p2_case1();

      TLorentzVector K1() const {return fK1;}
      TLorentzVector K2() const {return fK2;}
      TLorentzVector P1() const {return fP1;}
      TLorentzVector P2() const {return fP2;}

      TLorentzVector GetK1() {return fK1;}
      TLorentzVector GetK2() {return fK2;}
      TLorentzVector GetP1() {return fP1;}
      TLorentzVector GetP2() {return fP2;}

      ClassDef(DVCSKinematics,1)
};


#endif
