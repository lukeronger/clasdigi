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

      TLorentzVector  fK1; // virtual photon
      TLorentzVector  fK2; // photon
      TLorentzVector  fP1; // target nucleon
      TLorentzVector  fP2; // nucleon

   public:
      DVCSKinematics();
      virtual ~DVCSKinematics();

      int  Solve();

      void   SetQ2nu(double Q2,double nu);
      void   SetQ2(double Q2);
      double GetQ2() const ;

      void   Setnu(double nu, bool Q2fixed = true);
      double Getnu() const ;

      void SetK1(const TLorentzVector& v);
      void SetK2(const TLorentzVector& v);
      void SetP1(const TLorentzVector& v);
      void SetP2(const TLorentzVector& v);

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
