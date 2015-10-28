#ifndef clas12_mag_SolenoidField_HH
#define clas12_mag_SolenoidField_HH 1

#include <array>

namespace clas12 {

   namespace mag {

      double BilinearInterpolation(double * cornerDataPoints, double * corners, double x, double y);

      double TrilinearInterpolation(const std::array<double,8>& cornerValues, const std::array<double,6>& corners, double x, double y, double z);

   }

}
#endif
