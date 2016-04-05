#ifndef IonKinematics_HH
#define IonKinematics_HH 1

#include <iostream>
#include <iomanip>
#include <tuple>
#include "CLHEP/Units/SystemOfUnits.h"

#include "TMath.h"
#include "TLorentzVector.h"
#include "BaseKinematics.h"

namespace Jambo {

   namespace Kinematics {

      class IonKinematics : public BaseKinematics<IonKinematics>
      {
         protected :
            double fM1 = 0.938;
            double fM2 = 0.938;
            TLorentzVector  fp1 = {0.0     , 0.0, -1.0    , TMath::Sqrt(1+fM1*fM1)}; // incident electron
            TLorentzVector  fp2 = {0.1, 0.0, 0.35, TMath::Sqrt(0.35*0.35+0.1*0.1+fM2*fM2)}; // scattered electron

         public:

            // Use these for setting values
            TLorentzVector&   Get_p1() { return fp1;}
            TLorentzVector&   Get_p2() { return fp2;}

            double         t()  const { return( (fp1-fp2)*(fp1-fp2) ); }
            double         E1() const { return( fp1.E() ); }
            double         E2() const { return( fp2.E() ); }
            double         M1() const { return( fM1 ); }
            double         M2() const { return( fM2 ); }
            TLorentzVector p1() const { return fp1;}
            TLorentzVector p2() const { return fp2;}

            void Print_imp() const
            {
               using namespace std;
               cout << "ion Kinematics implementation\n";
               cout << right << "   M1 = " << left << setw(10) << M1() << right << " GeV/c^2\n";
               cout << right << "   E1 = " << left << setw(10) << E1() << right << " GeV\n";
               cout << right << "   p1 = " << left << setw(10) << fp1.Vect().Mag() << right << " GeV/c\n";
               cout << right << "  th1 = " << left << setw(10) << fp1.Theta()/CLHEP::degree << right << " degrees\n";
               cout << right << " phi1 = " << left << setw(10) << fp1.Phi()/CLHEP::degree << right << " degrees\n";
               cout << right << "   M2 = " << left << setw(10) << M2() << right << " GeV/c^2\n";
               cout << right << "   E2 = " << left << setw(10) << E2() << right << " GeV\n";
               cout << right << "   p2 = " << left << setw(10) << fp2.Vect().Mag() << right << " GeV/c\n";
               cout << right << "  th2 = " << left << setw(10) << fp2.Theta()/CLHEP::degree << right << " degrees\n";
               cout << right << " phi2 = " << left << setw(10) << fp2.Phi()/CLHEP::degree << right << " degrees\n";
               cout << right << "    t = " << left << setw(10) << t() << right << " GeV^2\n";
            }
      };
   }
}


#endif

