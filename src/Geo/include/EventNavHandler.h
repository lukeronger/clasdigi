#ifndef  EventNavHandler_HH
#define  EventNavHandler_HH

#include "CLAS12EventDisplay.h"

class EventNavHandler {
   protected:
      CLAS12EventDisplay  * fDisplay;

   public:
      EventNavHandler(CLAS12EventDisplay * display);
      void Fwd();
      void Bck();
      
};

#endif
