#ifndef clas12_DAQ_SubSystemProcessor_H
#define clas12_DAQ_SubSystemProcessor_H 1

#include "TObject.h"

namespace clas12 {

   namespace DAQ {

      class SubSystemProcessor : public TObject {

         public: 
            SubSystemProcessor();
            virtual ~SubSystemProcessor();

            ClassDef(SubSystemProcessor,1)
      };

   }

}

#endif

