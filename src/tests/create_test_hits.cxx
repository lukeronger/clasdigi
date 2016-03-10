#include <iostream>
#include <random>
#include "getopt.h"
#include <string>
#include <fstream>
#include "DigitizedSignal.h"
#include "FlashADCSignal.h"
#include "CLAS12HitsEvent.h"
#include "CLAS12DAQ.h"
#include "TDC.h"
#include "CrateModule.h"
#include "Discriminator.h"
#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "Module.h"


bool fexists(const std::string& filename) {
   std::ifstream ifile(filename.c_str());
   if( ifile ) return true;
   return false;
}


int main( int argc, char **argv )
{

   std::string output_file_name = "test_hits.root";

   int n_events                  = 10;
   int run_number                = 1;

   const struct option longopts[] =
   {
      {"output",    required_argument,  0, 'o'},
      {"nevent",    required_argument,  0, 'n'},
      {"run",       required_argument,  0, 'r'},
      {"help",      no_argument,        0, 'h'},
      {0,0,0,0}
   };

   int index = 0;
   int iarg  = 0;
   opterr    = 1; //turn off getopt error message


   //while(iarg != -1) {
   //   iarg = getopt_long(argc, argv, "n:r:o:h", longopts, &index);

   //   switch (iarg)
   //   {
   //      case 'n':
   //         n_events =  atoi(optarg);
   //         break;

   //      case 'r':
   //         run_number =  atoi(optarg);
   //         break;

   //      case 'o':
   //         output_file_name = optarg;
   //         if( fexists(output_file_name) ) {
   //            std::cout << "Error : " << output_file_name << " already exist"  << std::endl;
   //         }
   //         exit(EXIT_FAILURE);
   //         break;

   //      case 'h':
   //         //print_usage();
   //         std::cout << " todo: implement print help " << std::endl;
   //         exit(0);
   //         break;
   //   }
   //}

   std::string theRest  = "";
   //for (int i = optind; i < argc; i++) {
   //   theRest        += argv[i];
   //}
   std::cout << " the rest of the arguments: " << theRest << std::endl;
   std::cout << "output : " << output_file_name << std::endl;

   using namespace clas12::DAQ;
   using namespace clas12::hits;
   using namespace clas12::sigs;

   // --------------------------------------------------------------
   CLAS12HitsEvent * events = new CLAS12HitsEvent();

   events->fDCEvent.Dump();

   return 0;

   TFile * fout = new TFile(output_file_name.c_str(),"RECREATE");
   fout->cd();
   TTree * tree = new TTree("clasdidig","test data");


   tree->Branch("HitsEvent","clas12::hits::CLAS12HitsEvent",&events);

   HTCCHitsEvent * htcc_event    = &(events->fHTCCEvent);
   TClonesArray&   htcc_tdc_hits = *(htcc_event->fTDCHits);

   events->fRunNumber   = run_number;

   // --------------------------------------------------------------
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_int_distribution<> dis(0, 5);
   std::cout << dis(gen) << "\n";
   std::exponential_distribution<double> start_distribution(0.5);
   std::exponential_distribution<double> stop_distribution(4.5);

   // --------------------------------------------------------------

   Module<TDC>             tdc_module("tdc module");
   Module<Discriminator>   disc_module("disc module");

   // ------------------------------------------------------------
   //Discriminator * disc_ch0 = disc_module->GetDiscriminator(0);
   //Discriminator * disc_ch1 = disc_module->GetDiscriminator(1);
   //Discriminator * disc_ch2 = disc_module->GetDiscriminator(2);
   //TDC * tdc_ch0 = tdc_module->GetTDC(0);
   //TDC * tdc_ch1 = tdc_module->GetTDC(1);
   // ------------------------------------------------------------

   Discriminator& d0   = disc_module.GetChannel(0);
   Discriminator& d1   = disc_module.GetChannel(1);
   Discriminator& d2   = disc_module.GetChannel(2);

   TDC&           tdc0 = tdc_module.GetChannel(0);
   TDC&           tdc1 = tdc_module.GetChannel(1);

   // ------------------------------------------------------------

   d1 >> tdc0 << d0;
   d2 >> tdc1 << d0;

   // ------------------------------------------------------------

   for(int i = 0; i< n_events; i++) {

      events->fEventNumber   = i;

      d0.Clear();
      d1.Clear();
      d2.Clear();
      tdc0.Clear();
      tdc1.Clear();

      d0.Count( stop_distribution(gen)  );
      d1.Count( start_distribution(gen) );
      d2.Count( start_distribution(gen) );

      TDCHit * ahit = new (htcc_tdc_hits[0]) TDCHit();
      ahit->fChannel = 0;
      ahit->fValue   = tdc0.Readout();
      ahit->fTime    = tdc0.TimeDifference();

      TDCHit * bhit = new (htcc_tdc_hits[1]) TDCHit();
      bhit->fChannel = 1;
      bhit->fValue   = tdc1.Readout();
      bhit->fTime    = tdc1.TimeDifference();

      //int nhits = dis(gen);
      //for(int j = 0; j< ; j++) {
      //}

      tree->Fill();
   }

   // --------------------------------------------------------------
   tdc_module.Print("v");
   disc_module.Print("v");

   tree->Write();

   fout->Write();
   fout->Close();


   //std::cout << "derp\n";

   return 0;
}

