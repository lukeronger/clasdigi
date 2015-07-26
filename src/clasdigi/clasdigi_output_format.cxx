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
#include "evioFileChannel.hxx"
#include "evioChannel.hxx"


int main( int argc, char **argv )
{
   using namespace clas12::DAQ;
   using namespace clas12::hits;
   using namespace clas12::sigs;
   using namespace evio;

   //std::random_device rd;
   //std::mt19937 gen(rd());
   //std::uniform_int_distribution<> dis(0, 5);

   try {
      evioFileChannel chan(argv[1], "r");
      // open the file
      chan.open();

      evioFileChannel chan_out("evio_output_0.evio", "w");
      // open the file
      chan_out.open();

      TFile * fin = new TFile("test_output_0.root","READ");
      fin->ls();

      TTree * t = (TTree*)fin->FindObjectAny("digiSigs");
      if(!t) {
         std::cout << " Tree not found\n";
         exit(-123);
      }

      TClonesArray * tdc_sigs = 0;
      TClonesArray * adc_sigs = 0;

      t->SetBranchAddress("tdcSigs",&tdc_sigs);
      t->SetBranchAddress("adcSigs",&adc_sigs);

      unsigned short tag;
      unsigned char num;

      vector<int> tdc_chan;
      vector<int> tdc_value;
      vector<int> adc_chan;
      vector<int> adc_value;

      int Nevents = t->GetEntries();

      // first event has parameters... not a real event
      chan.read();

      for(int ievent = 0; ievent<Nevents; ievent++) {

         if( !(chan.read()) ) break;
         t->GetEntry(ievent);

         evioDOMTree tree(chan);

         int ntdc = tdc_sigs->GetEntries();
         int nadc = adc_sigs->GetEntries();

         tdc_chan.clear();
         tdc_value.clear();
         adc_chan.clear();
         adc_value.clear();

         for(int i = 0; i< ntdc; i++) {
            TDCSignal    * ahit = (TDCSignal*)(*(tdc_sigs))[i];
            tdc_chan.push_back(ahit->fChannel);
            tdc_value.push_back(ahit->fValue);
         }

         for(int i = 0; i< nadc; i++) {
            ADCSignal    * ahit = (ADCSignal*)((*adc_sigs)[i]);
            adc_chan.push_back(ahit->fChannel);
            adc_value.push_back(ahit->fValue);
         }

         //evioDOMNodeP evioDOMNodeP::createEvioDOMNode(111,222)

         //evioDOMTree evio_event(1,0);
         //evio_event.addBank(111,222,tdc_chan);
         //evio_event.addBank(111,221,tdc_value);
         //std::string new_node = "clasdigi";
         //anode->tag = 605;
         //anode->tag = 200;


         evioDOMNodeP cn = evioDOMNode::createEvioDOMNode(605,200);//tree.createNode(605,200);
         tree.root->addNode(cn);
         cn->addNode( evioDOMNode::createEvioDOMNode(605,201,adc_chan));
         cn->addNode( evioDOMNode::createEvioDOMNode(605,202,adc_value));
         cn->addNode( evioDOMNode::createEvioDOMNode(605,203,tdc_chan));
         cn->addNode( evioDOMNode::createEvioDOMNode(605,204,tdc_value));

         //evioDOMNodeListP pList = tree.getNodeList( [](const evioDOMNodeP node){return (node->tag==600);} );
         //std::cout << pMyList << std::endl;
         //for_each(pList->begin(), pList->end(), toCout());

         chan_out.write(tree);

         //tout->Fill();
      }

      chan.close();
      chan_out.close();

   } catch (evioException e) {
      std::cerr << std::endl << e.toString() << std::endl << std::endl;
      exit(EXIT_FAILURE);
   }

   return 0;
}

