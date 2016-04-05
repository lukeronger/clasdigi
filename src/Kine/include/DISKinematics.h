#ifndef DISKinematics_HH
#define DISKinematics_HH 1

#include <iostream>
#include <tuple>
#include "CLHEP/Units/SystemOfUnits.h"

#include "TMath.h"
#include "TLorentzVector.h"
#include "BaseKinematics.h"
#include "ElectronKinematics.h"
#include "IonKinematics.h"


namespace Jambo {

   namespace Kinematics {

      class DISKinematics : public BaseKinematics<DISKinematics> {

         protected :
            ElectronKinematics fElectronKine;
            IonKinematics      fIonKine;

         public:


            // Use these for setting values
            TLorentzVector&     Get_k1() { return fElectronKine.Get_k1();}
            TLorentzVector&     Get_k2() { return fElectronKine.Get_k2();}
            TLorentzVector&     Get_p1() { return fIonKine.Get_p1();}

            ElectronKinematics& GetElectronKinematics() { return fElectronKine; }
            IonKinematics&      GetIonKinematics(){ return fIonKine; }

            // Read only access 
            double         Q2() const { return( fElectronKine.Q2() ); }
            double         x()  const  { return( Q2()/(2.0*(fIonKine.p1()*fElectronKine.q())) );}
            double         y()  const  { return( (fIonKine.p1()*fElectronKine.q())/(fIonKine.p1()*fElectronKine.k1()) ) ;}
            double         s()  const  { return( (fIonKine.p1()+fElectronKine.k1()).Mag2() ) ;}
            double         W()  const  { return( TMath::Sqrt( (fIonKine.p1()+fElectronKine.q()).Mag2() ) ) ;}

            void Print_imp() const
            {
               std::cout << "DISKinematics implementation\n";
               std::cout << "Q2       : " << Q2() << std::endl;
               std::cout << "x        : " << x() << std::endl;
               std::cout << "y        : " << y() << std::endl;
               std::cout << "s        : " << s() << std::endl;
               std::cout << "W        : " << W() << std::endl;
            }
      };

   }

}
#endif

