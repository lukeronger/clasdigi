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

int main( int argc, char **argv )
{
   using namespace clas12::DAQ;
   using namespace clas12::hits;
   using namespace clas12::sigs;

   //std::random_device rd;
   //std::mt19937 gen(rd());
   //std::uniform_int_distribution<> dis(0, 5);

   TFile * fin = new TFile("test_0.root","READ");
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

   TFile * fout = new TFile("test_output_0.root","UPDATE");
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

