#include <iostream>
#include <random>
#include "TriggerSupervisor.h"
#include "Discriminator.h"
#include "TFile.h"
#include "TTree.h"
#include "TDCHit.h"
#include "ADCHit.h"
#include "TDCSignal.h"
#include "ADCSignal.h"
#include "TClonesArray.h"
#include "TROOT.h"
#include "getopt.h"
#include <string>
#include <fstream>

bool fexists(const std::string& filename) {
   std::ifstream ifile(filename.c_str());
   if( ifile ) return true;
   return false;
}


int main( int argc, char **argv )
{

   std::string input_file_name  = "";
   std::string output_file_name = "";


   const struct option longopts[] =
   {
      {"input",     required_argument,  0, 'i'},
      {"output",    required_argument,  0, 'o'},
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
            }

            break;

         case 'o':
            output_file_name = optarg;
            if( fexists(output_file_name) ) {
               std::cout << "Error : " << output_file_name << " already exist"  << std::endl;
            }
            exit(EXIT_FAILURE);
            break;

      }
   }

   std::string theRest  = "";
   for (int i = optind; i < argc; i++) {
      //is_interactive  = false;
      theRest        += argv[i];
   }
   std::cout << " the rest of the arguments: " << theRest << std::endl;
   std::cout << " input : " << input_file_name << std::endl;
   std::cout << "output : " << output_file_name << std::endl;

   using namespace clas12::DAQ;
   using namespace clas12::hits;
   using namespace clas12::sigs;

   //std::random_device rd;
   //std::mt19937 gen(rd());
   //std::uniform_int_distribution<> dis(0, 5);

   TFile * fin = new TFile(input_file_name.c_str(),"READ");
   fin->ls();

   TTree * t = (TTree*)fin->FindObjectAny("clasdigi_gemc");
   if(!t) {
      std::cout << " Tree not found\n";
      exit(-123);
   }

   TClonesArray * tdc_hits = 0;
   TClonesArray * adc_hits = 0;

   t->SetBranchAddress("tdcHits",&tdc_hits);
   t->SetBranchAddress("adcHits",&adc_hits);

   int Nevents = t->GetEntries();

   TFile * fout = new TFile(output_file_name.c_str(),"UPDATE");
   fout->cd();

   TTree * tout = new TTree("digiSigs","Digitized signals"); 

   TClonesArray * fTDCSigs = new TClonesArray("clas12::sigs::TDCSignal",10);
   TClonesArray * fADCSigs = new TClonesArray("clas12::sigs::ADCSignal",10);
   TClonesArray& tdc_sigs = (*fTDCSigs);
   TClonesArray& adc_sigs = (*fADCSigs);

   tout->Branch("tdcSigs","TClonesArray",&fTDCSigs);
   tout->Branch("adcSigs","TClonesArray",&fADCSigs);

   for(int ievent = 0; ievent<Nevents; ievent++) {

      t->GetEntry(ievent);
      
      int ntdc = tdc_hits->GetEntries();
      int nadc = adc_hits->GetEntries();
      for(int i = 0; i< ntdc; i++) {
         TDCHit    * ahit = (TDCHit*)(*(tdc_hits))[i];
         TDCSignal * asig = new(tdc_sigs[i]) TDCSignal(ahit->fChannel,ahit->fValue);
      }
      for(int i = 0; i< nadc; i++) {
         ADCHit    * ahit = (ADCHit*)((*adc_hits)[i]);
         ADCSignal * asig = new(adc_sigs[i]) ADCSignal(ahit->fChannel,ahit->fValue);
      }

      tout->Fill();
   }

   tout->Write();
   fout->Flush();
   fout->Close();

   //fOutputTree = new TTree("clasdigi_gemc","Clas12 gemc output");
   //for(auto t : TS.Triggers() ) t.Print();
   return 0;
}

