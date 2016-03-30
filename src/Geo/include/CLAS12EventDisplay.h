#ifndef CLAS12EventDisplay_HH
#define CLAS12EventDisplay_HH 1

#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"

#include "TEveTrack.h"
#include "TEveGeoShape.h"
#include "TEveGeoNode.h"
#include "TEveManager.h"
#include "TEveEventManager.h"

//#include "TGTab.h"
//#include "TGButton.h"

#include "MultiView.h"
#include "HtmlSummary.h"

//class EventNavHandler;

// Forward declarations.
//class AliESDEvent;
//class AliESDfriend;
//class AliESDtrack;
//class AliExternalTrackParam;


class CLAS12EventDisplay {

   public :
      CLAS12EventDisplay();
      ~CLAS12EventDisplay();

      // Configuration and global variables.

      const char * esd_file_name         = "http://root.cern.ch/files/alice_ESDs.root";
      const char * esd_friends_file_name = 0;
      const char * esd_geom_file_name    = "geometry/alert_geometry_simple.gdml";

      // For testing
      // const char* esd_file_name         = "AliESDs.root";
      // const char* esd_friends_file_name = "AliESDfriends.root";

      TFile *esd_file          = 0;
      TFile *esd_friends_file  = 0;

      TTree *esd_tree          = 0;

      //AliESDEvent  *esd        = 0;
      TList        *esd_objs   = 0;
      //AliESDfriend *esd_friend = 0;

      Int_t esd_event_id       = 0; // Current event id.

      TEveTrackList *gTrackList = 0;

      TEveGeoShape *gGeomGentle = 0;

      MultiView* gMultiView = 0;

      HtmlSummary *fgHtmlSummary = 0;
      TGHtml      *fgHtml        = 0;

      void run_alice_esd();
      void load_event();
      void update_html_summary();
      void make_gui();
      void alice_esd_read();

      ClassDef(CLAS12EventDisplay,1)

};

#endif

