#include "EventNavHandler.h"

#include "CLAS12EventDisplay.h"

EventNavHandler::EventNavHandler(CLAS12EventDisplay * display) 
{ fDisplay = display;}

void EventNavHandler::Fwd()
{
   if(fDisplay) {
      if( fDisplay->esd_tree ) {
         if (fDisplay->esd_event_id < fDisplay->esd_tree->GetEntries() - 1) {
            ++fDisplay->esd_event_id;
            fDisplay->load_event();
         } else {
            printf("Already at last event.\n");
         }
      }
   }
}
void EventNavHandler::Bck()
{
   if(fDisplay) {
      if (fDisplay->esd_event_id > 0) {
         --fDisplay->esd_event_id;
         fDisplay->load_event();
      } else {
         printf("Already at first event.\n");
      }
   }
}
