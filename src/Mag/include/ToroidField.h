#ifndef clas12_hits_ToroidField_HH
#define clas12_hits_ToroidField_HH 1

#include <vector>
#include <fstream>
#include <string>

//#include "TObject.h"
#include "TVector3.h"

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

            std::string          fMapFileName;
            std::ifstream        fMapFile;

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

            //void CheckMap();

            //ClassDef(ToroidField,1)
      };

   }

}

#endif

