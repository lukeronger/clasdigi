#ifndef clas12_Detectors_HH
#define clas12_Detectors_HH

namespace clas12 {

   enum class Detector { NONE, HTCC, LTCC, DC, FTOF, EC };

   inline const char* ToString(Detector v)
   {
      switch (v)
      {
         case Detector::NONE:   return "NONE";
         case Detector::HTCC:   return "HTCC";
         case Detector::LTCC:   return "LTCC";
         case Detector::FTOF:   return "FTOF";
         case Detector::EC:     return "EC";
         case Detector::DC:     return "DC";
         default:     return nullptr;
      }
   }
}


#endif

