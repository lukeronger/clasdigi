#ifndef clas12_hits_SolenoidField_HH
#define clas12_hits_SolenoidField_HH 1

#include <vector>
#include <fstream>
#include <string>

//#include "TObject.h"
#include "TVector3.h"

namespace clas12 {

   namespace mag {

      class SolenoidField {

         protected :
            double fDelta_r;   // m
            double fDelta_z;   // m
            double fr_min;     // m
            double fr_max;     // m
            double fz_min;     // m
            double fz_max;     // m

            int    fStride_r;
            int    fStride_z;

            double fr_offset; // m offset added to get: index = (r+r_offset)/delta_r
            double fz_offset; // m

            std::string          fMapFileName;
            std::ifstream        fMapFile;
            std::vector<double>  fr;
            std::vector<double>  fz;
            std::vector<double>  fBr;
            std::vector<double>  fBz;

         public :
            SolenoidField();
            ~SolenoidField();

            void Print(const char * opt = "") const;
            void Clear(const char * opt = "");

            void ReadMap();

            TVector3 GetField(double x, double y, double z);

            //ClassDef(SolenoidField,1)
      };

   }

}

#endif

