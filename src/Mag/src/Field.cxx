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

