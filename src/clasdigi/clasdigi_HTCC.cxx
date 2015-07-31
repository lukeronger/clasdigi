#include <iostream>
#include <random>
#include <string>
#include <fstream>
#include "getopt.h"

#include "CLAS12HitsEvent.h"
#include "CLAS12SigsEvent.h"
#include "HTCCHitsEvent.h"
#include "HTCCSigsEvent.h"
#include "DCHitsEvent.h"
#include "DCSigsEvent.h"
#include "TDCHit.h"
#include "ADCHit.h"
#include "TDCSignal.h"
#include "ADCSignal.h"

#include "TClonesArray.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"


void process_HTCC_sigs(
      clas12::hits::HTCCHitsEvent& hits_event,
      clas12::sigs::HTCCSigsEvent& sigs_event);

void process_DC_sigs(
      clas12::hits::DCHitsEvent& hits_event,
      clas12::sigs::DCSigsEvent& sigs_event);

bool fexists(const std::string& filename) {
   std::ifstream ifile(filename.c_str());
   if( ifile ) return true;
   return false;
}

int main( int argc, char **argv )
{

   std::string input_file_name  = "";
   std::string output_file_name = "";
   std::string input_tree_name  = "clasdigi_hits";
   std::string output_tree_name = "clasdigi_sigs";

   const struct option longopts[] =
   {
      {"input",     required_argument,  0, 'i'},
      {"output",    required_argument,  0, 'o'},
      {"tree",      required_argument,  0, 't'},
      {"help",      no_argument,        0, 'h'},
      {0,0,0,0}
   };

   int index = 0;
   int iarg  = 0;
   opterr    = 1; //turn off getopt error message

   while(iarg != -1) {
      iarg = getopt_long(argc, argv, "i:o:h", longopts, &index);

      switch (iarg)
      {
         case 'i':
            input_file_name = optarg;
            if( !fexists(input_file_name) ) {
               std::cout << input_file_name << " does not exist"  << std::endl;
            exit(EXIT_FAILURE);
            }

            break;

         case 't':
            output_tree_name = optarg;
            break;

         case 'o':
            output_file_name = optarg;
            if( fexists(output_file_name) ) {
               std::cout << "Error : " << output_file_name << " already exist"  << std::endl;
            exit(EXIT_FAILURE);
            }
            break;

      }
   }

   //std::string theRest  = "";
   //for (int i = optind; i < argc; i++) {
   //   theRest        += argv[i];
   //}
   //std::cout << " the rest of the arguments: " << theRest << std::endl;

   std::cout << " input : " << input_file_name << std::endl;
   std::cout << "  tree : " << input_tree_name << std::endl;
   std::cout << "output : " << output_file_name << std::endl;
   std::cout << "  tree : " << output_tree_name << std::endl;

   //using namespace clas12::DAQ;
   using namespace clas12::hits;
   using namespace clas12::sigs;

   //std::random_device rd;
   //std::mt19937 gen(rd());
   //std::uniform_int_distribution<> dis(0, 5);

   // -----------------------------------------------------------
   CLAS12HitsEvent * event = 0;

   TFile * fin = new TFile(input_file_name.c_str(),"READ");
   fin->ls();
   TTree * t = (TTree*)fin->FindObjectAny(input_tree_name.c_str());
   if(!t) {
      std::cout << "Input tree, " 
         << input_tree_name 
         << " not found in file "
         << input_file_name 
         << "\n";
      return(EXIT_FAILURE);
   }

   t->SetBranchAddress("HitsEvent",&event);
   int Nevents = t->GetEntries();

   // -----------------------------------------------------------

   CLAS12SigsEvent * sigs_event = 0;

   TFile * fout = new TFile(output_file_name.c_str(),"UPDATE");
   fout->cd();

   TTree * tout = new TTree(output_tree_name.c_str(),"Digitized signals"); 
   tout->Branch("SigsEvent","clas12::sigs::CLAS12SigsEvent",&sigs_event);

   for(int ievent = 0; ievent<Nevents; ievent++) {

      sigs_event->Clear();

      t->GetEntry(ievent);

      process_HTCC_sigs(event->fHTCCEvent, sigs_event->fHTCCEvent);

      tout->Fill();
   }

   tout->FlushBaskets();

   fout->Write();
   fout->Close();

   return 0;
}
//______________________________________________________________________________

void process_HTCC_sigs(
      clas12::hits::HTCCHitsEvent& hits_event,
      clas12::sigs::HTCCSigsEvent& sigs_event   )
{
   using namespace clas12::hits;
   using namespace clas12::sigs;
   int ntdc = hits_event.fNTDCHits;
   int nadc = hits_event.fNADCHits;
   for(int i = 0; i< ntdc; i++) {
      TDCHit    * ahit = (TDCHit*)(*(hits_event.fTDCHits))[i];
      TDCSignal * asig = sigs_event.AddTDCSignal(ahit->fChannel,ahit->fValue);
   }
   for(int i = 0; i< nadc; i++) {
      ADCHit    * ahit = (ADCHit*)((*hits_event.fADCHits)[i]);
      ADCSignal * asig = sigs_event.AddADCSignal(ahit->fChannel,ahit->fValue);
   }
}
//______________________________________________________________________________

void process_DC_sigs(
      clas12::hits::DCHitsEvent& hits_event,
      clas12::sigs::DCSigsEvent& sigs_event   )
{
   using namespace clas12::hits;
   using namespace clas12::sigs;
   //int ntdc = hits_event.fNTDCHits;
   //int nadc = hits_event.fNADCHits;
   //for(int i = 0; i< ntdc; i++) {
   //   TDCHit    * ahit = (TDCHit*)(*(hits_event.fTDCHits))[i];
   //   TDCSignal * asig = sigs_event.AddTDCSignal(ahit->fChannel,ahit->fValue);
   //}
   //for(int i = 0; i< nadc; i++) {
   //   ADCHit    * ahit = (ADCHit*)((*hits_event.fADCHits)[i]);
   //   ADCSignal * asig = sigs_event.AddADCSignal(ahit->fChannel,ahit->fValue);
   //}
}
//______________________________________________________________________________

