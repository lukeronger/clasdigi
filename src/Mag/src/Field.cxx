#include "Field.h"

double clas12::mag::BilinearInterpolation(double * cornerDataPoints, double * corners, double x, double y)
{
   /// Z -> i, R -> j
   double Q11 = cornerDataPoints[0];
   double Q21 = cornerDataPoints[1];
   double Q12 = cornerDataPoints[2];
   double Q22 = cornerDataPoints[3];
   double x1 = corners[0];
   double x2 = corners[1];
   double y1 = corners[2];
   double y2 = corners[3];
   double dxdy = (x2 - x1) * (y2 - y1);
   double result  = Q11 * (x2 - x) * (y2 - y) / dxdy +
                      Q21 * (x - x1) * (y2 - y) / dxdy +
                      Q12 * (x2 - x) * (y - y1) / dxdy +
                      Q22 * (x - x1) * (y - y1) / dxdy  ;
   return(result);
}
//______________________________________________________________________________

double clas12::mag::TrilinearInterpolation(
      const std::array<double,8>& cornerValues, 
      const std::array<double,6>& corners, 
      double x, double y, double z)
{
   double x0 = corners.at(0);
   double x1 = corners.at(1);
   double y0 = corners.at(2);
   double y1 = corners.at(3);
   double z0 = corners.at(4);
   double z1 = corners.at(5);
   double V000 = cornerValues.at(0);
   double V100 = cornerValues.at(1);
   double V110 = cornerValues.at(2);
   double V010 = cornerValues.at(3);
   double V001 = cornerValues.at(4);
   double V101 = cornerValues.at(5);
   double V111 = cornerValues.at(6);
   double V011 = cornerValues.at(7);

   double xd = (x - x0)/(x1-x0);
   double yd = (y - y0)/(y1-y0);
   double zd = (z - z0)/(z1-z0);

   double c00 = V000*(1.0-xd) + V100*xd;
   double c10 = V010*(1.0-xd) + V110*xd;
   double c01 = V001*(1.0-xd) + V101*xd;
   double c11 = V011*(1.0-xd) + V111*xd;

   double c0 = c00*(1.0-yd)+c10*yd;
   double c1 = c01*(1.0-yd)+c11*yd;
   double c = c0*(1.0-zd)+c1*zd; 

   return(c);
}
//______________________________________________________________________________

