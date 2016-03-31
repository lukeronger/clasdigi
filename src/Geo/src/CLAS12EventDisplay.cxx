#include "CLAS12EventDisplay.h"
#include <iostream>

#include "TGTab.h"
#include "TGButton.h"
#include "TGeoManager.h"

#include "TEveGeoShapeExtract.h"
#include "TEveGeoNode.h"

#include "EventNavHandler.h"

CLAS12EventDisplay::CLAS12EventDisplay()
{ }
//______________________________________________________________________________

CLAS12EventDisplay::~CLAS12EventDisplay()
{ } 
//______________________________________________________________________________

void CLAS12EventDisplay::run_alice_esd()
{
   // Main function, initializes the application.
   //
   // 1. Load the auto-generated library holding ESD classes and
   //    ESD dictionaries.
   // 2. Open ESD data-files.
   // 3. Load cartoon geometry.
   // 4. Spawn simple GUI.
   // 5. Load first event.

   //const TString weh("alice_esd()");

   //TFile::SetCacheFileDir(".");

   //printf("*** Opening ESD ***\n");
   //esd_file = TFile::Open(esd_file_name, "CACHEREAD");
   //if (!esd_file)
   //   return;

   //esd_tree = (TTree*)       esd_file->Get("esdTree");
   //esd      = (AliESDEvent*) esd_tree->GetUserInfo()->FindObject("AliESDEvent");
   //esd_objs = esd->fESDObjects;

   //if (esd_friends_file_name != 0)
   //{
   //   printf("*** Opening ESD-friends ***\n");
   //   esd_friends_file = TFile::Open(esd_friends_file_name, "CACHEREAD");
   //   if (!esd_friends_file)
   //      return;

   //   esd_tree->SetBranchStatus ("ESDfriend*", 1);
   //}

   // Set the branch addresses.
   //{
   //   TIter next(esd_objs);
   //   TObject *el;
   //   while ((el = (TNamed*)next()))
   //   {
   //      TString bname(el->GetName());
   //      if (bname == "AliESDfriend")
   //      {
   //         // AliESDfriend needs special treatment.
   //         TBranch *br = esd_tree->GetBranch("ESDfriend.");
   //         br->SetAddress(esd_objs->GetObjectRef(el));
   //      }
   //      else
   //      {
   //         TBranch *br = esd_tree->GetBranch(bname);
   //         if (br)
   //         {
   //            br->SetAddress(esd_objs->GetObjectRef(el));
   //         }
   //         else
   //         {
   //            br = esd_tree->GetBranch(bname + ".");
   //            if (br)
   //            {
   //               br->SetAddress(esd_objs->GetObjectRef(el));
   //            }
   //            else
   //            {
   //               Warning("AliESDEvent::ReadFromTree() "
   //                     "No Branch found with Name '%s' or '%s.'.",
   //                     bname.Data(),bname.Data());
   //            }
   //         }
   //      }
   //   }
   //}


   TEveManager::Create();

   TGeoManager::Import(esd_geom_file_name);
   //gGeoManager->DefaultColors();

   TGeoNode* node1 = gGeoManager->GetTopNode();
   node1->Print();
   TEveGeoTopNode * anode = new TEveGeoTopNode(gGeoManager, node1);
   gEve->AddGlobalElement(anode);

   gMultiView = new MultiView;

   TList * derp_list = new TList();
   //node1->GetVolume()->PrintNodes();
   TEveElementListProjected * an_element_list = new TEveElementListProjected();
   for(int iNode = 0; iNode<node1->GetNdaughters(); iNode++) {
      if( std::string(node1->GetDaughter(iNode)->GetName()).find("fScint") == std::string::npos ) {
         TEveGeoShapeExtract* gse = new TEveGeoShapeExtract( node1->GetDaughter(iNode)->GetName() );
         gse->SetShape(node1->GetDaughter(iNode)->GetVolume()->GetShape());
         TEveGeoShape * aGeo = TEveGeoShape::ImportShapeExtract(gse, 0);
         aGeo->SetMainColor(2+iNode);
         aGeo->SetMainTransparency(50);
         an_element_list->AddElement(aGeo);
         derp_list->Add(aGeo);
      }
   }

   TFile geo_out("geometry/alert_projection.root","RECREATE");
   geo_out.cd();
   geo_out.WriteObject(derp_list,"alert",0);
   //derp_list->Write("alert");
   geo_out.Close();

   // Simple geometry
   //TFile* geom =  TFile::Open("geometry/alert_projection.root");
   //if (!geom)
   //   return;
   //TEveGeoShapeExtract* gse = (TEveGeoShapeExtract*) geom->Get("alert");
   //gGeomGentle = TEveGeoShape::ImportShapeExtract(gse, 0);
   //gEve->AddGlobalElement(gGeomGentle);
   //geom->Close();

   //gEve->AddGlobalElement(an_element_list);
   gMultiView->f3DGeomScene->AddElement(an_element_list);
   gMultiView->ImportGeomRPhi(an_element_list);
   gMultiView->ImportGeomRhoZ(an_element_list);


   // HTML summary view
   //===================

   fgHtmlSummary = new HtmlSummary("Alice Event Display Summary Table");
   TEveWindowSlot * slot = TEveWindow::CreateWindowInTab(gEve->GetBrowser()->GetTabRight());
   fgHtml = new TGHtml(0, 100, 100);
   TEveWindowFrame *wf = slot->MakeFrame(fgHtml);
   fgHtml->MapSubwindows();
   wf->SetElementName("Summary");


   // Final stuff
   //=============

   gEve->GetBrowser()->GetTabRight()->SetTab(1);

   make_gui();

   load_event();
   gEve->GetEventScene(); 

   gEve->Redraw3D(kTRUE); // Reset camera after the first event has been shown.
}

//______________________________________________________________________________
void CLAS12EventDisplay::load_event()
{
   // Load event specified in global esd_event_id.
   // The contents of previous event are removed.

   printf("Loading event %d.\n", esd_event_id);

   gEve->GetViewers()->DeleteAnnotations();

   if (gTrackList)
      gTrackList->DestroyElements();

   //esd_tree->GetEntry(esd_event_id);
   // esd_tree->Show();

   alice_esd_read();

   TEveElement* top = gEve->GetCurrentEvent();

   //gMultiView->DestroyEventRPhi();
   //gMultiView->ImportEventRPhi(top);

   //gMultiView->DestroyEventRhoZ();
   //gMultiView->ImportEventRhoZ(top);

   update_html_summary();

   gEve->FullRedraw3D(kFALSE, kTRUE);
}


/******************************************************************************/
// GUI
/******************************************************************************/

//______________________________________________________________________________
void CLAS12EventDisplay::update_html_summary()
{
   // Update summary of current event.

   TEveElement::List_i i;
   TEveElement::List_i j;
   Int_t k;
   TEveElement *el;
   HtmlObjTable *table;
   TEveEventManager *mgr = gEve ? gEve->GetCurrentEvent() : 0;
   if (mgr) {
      fgHtmlSummary->Clear("D");
      for (i=mgr->BeginChildren(); i!=mgr->EndChildren(); ++i) {
         el = ((TEveElement*)(*i));
         if (el->IsA() == TEvePointSet::Class()) {
            TEvePointSet *ps = (TEvePointSet *)el;
            TString ename  = ps->GetElementName();
            TString etitle = ps->GetElementTitle();
            if (ename.First('\'') != kNPOS)
               ename.Remove(ename.First('\''));
            etitle.Remove(0, 2);
            Int_t nel = atoi(etitle.Data());
            table = fgHtmlSummary->AddTable(ename, 0, nel);
         }
         else if (el->IsA() == TEveTrackList::Class()) {
            TEveTrackList *tracks = (TEveTrackList *)el;
            TString ename  = tracks->GetElementName();
            if (ename.First('\'') != kNPOS)
               ename.Remove(ename.First('\''));
            table = fgHtmlSummary->AddTable(ename.Data(), 5,
                  tracks->NumChildren(), kTRUE, "first");
            table->SetLabel(0, "Momentum");
            table->SetLabel(1, "P_t");
            table->SetLabel(2, "Phi");
            table->SetLabel(3, "Theta");
            table->SetLabel(4, "Eta");
            k=0;
            for (j=tracks->BeginChildren(); j!=tracks->EndChildren(); ++j) {
               Float_t p     = ((TEveTrack*)(*j))->GetMomentum().Mag();
               table->SetValue(0, k, p);
               Float_t pt    = ((TEveTrack*)(*j))->GetMomentum().Perp();
               table->SetValue(1, k, pt);
               Float_t phi   = ((TEveTrack*)(*j))->GetMomentum().Phi();
               table->SetValue(2, k, phi);
               Float_t theta = ((TEveTrack*)(*j))->GetMomentum().Theta();
               table->SetValue(3, k, theta);
               Float_t eta   = ((TEveTrack*)(*j))->GetMomentum().Eta();
               table->SetValue(4, k, eta);
               ++k;
            }
         }
      }
      fgHtmlSummary->Build();
      fgHtml->Clear();
      fgHtml->ParseText((char*)fgHtmlSummary->Html().Data());
      fgHtml->Layout();
   }
}

//______________________________________________________________________________
void CLAS12EventDisplay::make_gui()
{
   // Create minimal GUI for event navigation.

   TEveBrowser* browser = gEve->GetBrowser();
   browser->StartEmbedding(TRootBrowser::kLeft);

   TGMainFrame* frmMain = new TGMainFrame(gClient->GetRoot(), 1000, 600);
   frmMain->SetWindowName("XX GUI");
   frmMain->SetCleanup(kDeepCleanup);

   TGHorizontalFrame* hf = new TGHorizontalFrame(frmMain);
   {

      TString icondir( Form("%s/icons/", gSystem->Getenv("ROOTSYS")) );
      TGPictureButton* b = 0;
      EventNavHandler    *fh = new EventNavHandler(this);

      b = new TGPictureButton(hf, gClient->GetPicture(icondir+"GoBack.gif"));
      hf->AddFrame(b);
      b->Connect("Clicked()", "EventNavHandler", fh, "Bck()");

      b = new TGPictureButton(hf, gClient->GetPicture(icondir+"GoForward.gif"));
      hf->AddFrame(b);
      b->Connect("Clicked()", "EventNavHandler", fh, "Fwd()");
   }
   frmMain->AddFrame(hf);

   frmMain->MapSubwindows();
   frmMain->Resize();
   frmMain->MapWindow();

   browser->StopEmbedding();
   browser->SetTabTitle("Event Control", 0);
}


/******************************************************************************/
// Code for reading AliESD and creating visualization objects
/******************************************************************************/

//enum ESDTrackFlags {
//   kITSin=0x0001,kITSout=0x0002,kITSrefit=0x0004,kITSpid=0x0008,
//   kTPCin=0x0010,kTPCout=0x0020,kTPCrefit=0x0040,kTPCpid=0x0080,
//   kTRDin=0x0100,kTRDout=0x0200,kTRDrefit=0x0400,kTRDpid=0x0800,
//   kTOFin=0x1000,kTOFout=0x2000,kTOFrefit=0x4000,kTOFpid=0x8000,
//   kHMPIDpid=0x20000,
//   kEMCALmatch=0x40000,
//   kTRDbackup=0x80000,
//   kTRDStop=0x20000000,
//   kESDpid=0x40000000,
//   kTIME=0x80000000
//};

//______________________________________________________________________________
void CLAS12EventDisplay::alice_esd_read()
{
   // Read tracks and associated clusters from current event.

   //AliESDRun    *esdrun = (AliESDRun*)    esd_objs->FindObject("AliESDRun");
   //TClonesArray *tracks = (TClonesArray*) esd_objs->FindObject("Tracks");

   //// This needs further investigation. Clusters not shown.
   //// esd_friend = (AliESDfriend*) esd_objs->FindObject("AliESDfriend");
   //// printf("Friend %p, n_tracks:%d\n",
   ////        esd_friend,
   ////        esd_friend->fTracks.GetEntries());

   //if (gTrackList == 0)
   //{
   //   gTrackList = new TEveTrackList("ESD Tracks");
   //   gTrackList->SetMainColor(6);
   //   gTrackList->SetMarkerColor(kYellow);
   //   gTrackList->SetMarkerStyle(4);
   //   gTrackList->SetMarkerSize(0.5);

   //   gEve->AddElement(gTrackList);
   //}

   //TEveTrackPropagator* trkProp = gTrackList->GetPropagator();
   //trkProp->SetMagField( 0.1 * esdrun->fMagneticField ); // kGaus to Tesla

   //for (Int_t n=0; n<tracks->GetEntriesFast(); ++n)
   //{
   //   AliESDtrack* at = (AliESDtrack*) tracks->At(n);

   //   // If ITS refit failed, take track parameters at inner TPC radius.
   //   AliExternalTrackParam* tp = at;
   //   if (! trackIsOn(at, kITSrefit)) {
   //      tp = at->fIp;
   //   }

   //   TEveTrack* track = esd_make_track(trkProp, n, at, tp);
   //   track->SetAttLineAttMarker(gTrackList);
   //   gTrackList->AddElement(track);

   //   // This needs further investigation. Clusters not shown.
   //   // if (frnd)
   //   // {
   //   //     AliESDfriendTrack* ft = (AliESDfriendTrack*) frnd->fTracks->At(n);
   //   //     printf("%d friend = %p\n", ft);
   //   // }
   //}

   //gTrackList->MakeTracks();
}

//______________________________________________________________________________
//TEveTrack* esd_make_track(TEveTrackPropagator*   trkProp,
//      Int_t                  index,
//      AliESDtrack*           at,
//      AliExternalTrackParam* tp)
//{
//   // Helper function creating TEveTrack from AliESDtrack.
//   //
//   // Optionally specific track-parameters (e.g. at TPC entry point)
//   // can be specified via the tp argument.

//   Double_t      pbuf[3], vbuf[3];
//   TEveRecTrack  rt;

//   if (tp == 0) tp = at;

//   rt.fLabel  = at->fLabel;
//   rt.fIndex  = index;
//   rt.fStatus = (Int_t) at->fFlags;
//   rt.fSign   = (tp->fP[4] > 0) ? 1 : -1;

//   trackGetPos(tp, vbuf);      rt.fV.Set(vbuf);
//   trackGetMomentum(tp, pbuf); rt.fP.Set(pbuf);

//   Double_t ep = trackGetP(at);
//   Double_t mc = 0.138; // at->GetMass(); - Complicated function, requiring PID.

//   rt.fBeta = ep/TMath::Sqrt(ep*ep + mc*mc);

//   TEveTrack* track = new TEveTrack(&rt, trkProp);
//   track->SetName(Form("TEveTrack %d", rt.fIndex));
//   track->SetStdTitle();

//   return track;
//}

////______________________________________________________________________________
//Bool_t trackIsOn(AliESDtrack* t, Int_t mask)
//{
//   // Check is track-flag specified by mask are set.

//   return (t->fFlags & mask) > 0;
//}

////______________________________________________________________________________
//void trackGetPos(AliExternalTrackParam* tp, Double_t r[3])
//{
//   // Get global position of starting point of tp.

//   r[0] = tp->fX; r[1] = tp->fP[0]; r[2] = tp->fP[1];

//   Double_t cs=TMath::Cos(tp->fAlpha), sn=TMath::Sin(tp->fAlpha), x=r[0];
//   r[0] = x*cs - r[1]*sn; r[1] = x*sn + r[1]*cs;
//}

////______________________________________________________________________________
//void trackGetMomentum(AliExternalTrackParam* tp, Double_t p[3])
//{
//   // Return global momentum vector of starting point of tp.

//   p[0] = tp->fP[4]; p[1] = tp->fP[2]; p[2] = tp->fP[3];

//   Double_t pt=1./TMath::Abs(p[0]);
//   Double_t cs=TMath::Cos(tp->fAlpha), sn=TMath::Sin(tp->fAlpha);
//   Double_t r=TMath::Sqrt(1 - p[1]*p[1]);
//   p[0]=pt*(r*cs - p[1]*sn); p[1]=pt*(p[1]*cs + r*sn); p[2]=pt*p[2];
//}

////______________________________________________________________________________
//Double_t trackGetP(AliExternalTrackParam* tp)
//{
//   // Return magnitude of momentum of tp.

//   return TMath::Sqrt(1.+ tp->fP[3]*tp->fP[3])/TMath::Abs(tp->fP[4]);
//}
/******************************************************************************/
// Code for reading AliESD and creating visualization objects
/******************************************************************************/

//enum ESDTrackFlags {
//   kITSin=0x0001,kITSout=0x0002,kITSrefit=0x0004,kITSpid=0x0008,
//   kTPCin=0x0010,kTPCout=0x0020,kTPCrefit=0x0040,kTPCpid=0x0080,
//   kTRDin=0x0100,kTRDout=0x0200,kTRDrefit=0x0400,kTRDpid=0x0800,
//   kTOFin=0x1000,kTOFout=0x2000,kTOFrefit=0x4000,kTOFpid=0x8000,
//   kHMPIDpid=0x20000,
//   kEMCALmatch=0x40000,
//   kTRDbackup=0x80000,
//   kTRDStop=0x20000000,
//   kESDpid=0x40000000,
//   kTIME=0x80000000
//};


//______________________________________________________________________________
//TEveTrack* esd_make_track(TEveTrackPropagator*   trkProp,
//      Int_t                  index,
//      AliESDtrack*           at,
//      AliExternalTrackParam* tp)
//{
//   // Helper function creating TEveTrack from AliESDtrack.
//   //
//   // Optionally specific track-parameters (e.g. at TPC entry point)
//   // can be specified via the tp argument.

//   Double_t      pbuf[3], vbuf[3];
//   TEveRecTrack  rt;

//   if (tp == 0) tp = at;

//   rt.fLabel  = at->fLabel;
//   rt.fIndex  = index;
//   rt.fStatus = (Int_t) at->fFlags;
//   rt.fSign   = (tp->fP[4] > 0) ? 1 : -1;

//   trackGetPos(tp, vbuf);      rt.fV.Set(vbuf);
//   trackGetMomentum(tp, pbuf); rt.fP.Set(pbuf);

//   Double_t ep = trackGetP(at);
//   Double_t mc = 0.138; // at->GetMass(); - Complicated function, requiring PID.

//   rt.fBeta = ep/TMath::Sqrt(ep*ep + mc*mc);

//   TEveTrack* track = new TEveTrack(&rt, trkProp);
//   track->SetName(Form("TEveTrack %d", rt.fIndex));
//   track->SetStdTitle();

//   return track;
//}

////______________________________________________________________________________
//Bool_t trackIsOn(AliESDtrack* t, Int_t mask)
//{
//   // Check is track-flag specified by mask are set.

//   return (t->fFlags & mask) > 0;
//}

////______________________________________________________________________________
//void trackGetPos(AliExternalTrackParam* tp, Double_t r[3])
//{
//   // Get global position of starting point of tp.

//   r[0] = tp->fX; r[1] = tp->fP[0]; r[2] = tp->fP[1];

//   Double_t cs=TMath::Cos(tp->fAlpha), sn=TMath::Sin(tp->fAlpha), x=r[0];
//   r[0] = x*cs - r[1]*sn; r[1] = x*sn + r[1]*cs;
//}

////______________________________________________________________________________
//void trackGetMomentum(AliExternalTrackParam* tp, Double_t p[3])
//{
//   // Return global momentum vector of starting point of tp.

//   p[0] = tp->fP[4]; p[1] = tp->fP[2]; p[2] = tp->fP[3];

//   Double_t pt=1./TMath::Abs(p[0]);
//   Double_t cs=TMath::Cos(tp->fAlpha), sn=TMath::Sin(tp->fAlpha);
//   Double_t r=TMath::Sqrt(1 - p[1]*p[1]);
//   p[0]=pt*(r*cs - p[1]*sn); p[1]=pt*(p[1]*cs + r*sn); p[2]=pt*p[2];
//}

////______________________________________________________________________________
//Double_t trackGetP(AliExternalTrackParam* tp)
//{
//   // Return magnitude of momentum of tp.

//   return TMath::Sqrt(1.+ tp->fP[3]*tp->fP[3])/TMath::Abs(tp->fP[4]);
//}
