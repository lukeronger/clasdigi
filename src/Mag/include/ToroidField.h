#ifndef clas12_mag_ToroidField_HH
#define clas12_mag_ToroidField_HH 1

#include <vector>
#include <fstream>
#include <string>

//#include "TObject.h"
#include "TVector3.h"

// with gzstream
//real    0m23.287s
//user    0m22.932s
//sys     0m0.372s

// without gzstream
//real    0m25.139s
//user    0m24.660s
//sys     0m0.472s


namespace clas12 {

   namespace mag {

      class ToroidField  {


         protected :
            double fDelta_phi; // deg
            double fDelta_r;   // cm
            double fDelta_z;   // cm

            double fphi_min; // deg
            double fphi_max; // deg
            double fr_min;   // cm
            double fr_max;   // cm
            double fz_min;   // cm
            double fz_max;   // cm

            int    fStride_phi;
            int    fStride_r;
            int    fStride_z;

            double fphi_offset; // m offset added to get: index = (r+r_offset)/delta_r
            double fr_offset; // m offset added to get: index = (r+r_offset)/delta_r
            double fz_offset; // m

            std::string          fMapFileName;
            std::ifstream        fMapFile;

         private:
            std::vector<double>  fphi;
            std::vector<double>  fr;
            std::vector<double>  fz;
            std::vector<double>  fBphi;
            std::vector<double>  fBr;
            std::vector<double>  fBz;


         public :
            ToroidField();
            ~ToroidField();

            void Print(const char * opt = "") const;
            void Clear(const char * opt = "") ;

            void ReadMap();

            TVector3 GetField(double x, double y, double z) const ;
            TVector3 GetField(const TVector3& v) const ;

            //void CheckMap();

            //TVector3 GetField(double x, double y, double z) const ;

            //ClassDef(ToroidField,1)
      };

   }

}

#endif

