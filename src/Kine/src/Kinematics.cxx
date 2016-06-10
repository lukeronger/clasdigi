#include "Kinematics.h"

namespace kinematics {

   double Offshellness(double Q2, double nu1, double nu2, double P1, double thetaq1q2, double thetaP1q1, double thetaP1q2)
   {
      using namespace TMath;
      double A1 = (P1*(-1.0 + Cos(thetaP1q2)) + Sqrt(Power(nu1,2.0) + Q2)*Cos(thetaq1q2));
      double B1 = (P1 + P1*Cos(thetaP1q2) + Sqrt(Power(nu1,2.0) + Q2)*Cos(thetaq1q2));
      double A  = (2.0*nu1*(nu2 - P1) + Q2 + 2.0*P1*Sqrt(Power(nu1,2.0) + Q2)*Cos(thetaP1q1) - 2.0*nu2*A1);
      double B  = (2.0*nu1*(nu2 + P1) + Q2 + 2.0*P1*Sqrt(Power(nu1,2.0) + Q2)*Cos(thetaP1q1) - 2.0*nu2*B1);
      double res = Sqrt(A*B)/(2.0*(nu1 - nu2));
      return res;
   }

}


