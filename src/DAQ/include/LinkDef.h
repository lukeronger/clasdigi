#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;

#pragma link C++ namespace clas12;
#pragma link C++ namespace clas12::DAQ;

#pragma link C++ enum clas12::Detector;
#pragma link C++ function clas12::ToString(clas12::Detector);

#pragma link C++ class clas12::DAQ::DAQManager+;
#pragma link C++ class clas12::DAQ::Crate+;
#pragma link C++ class clas12::DAQ::CrateModule+;
#pragma link C++ class clas12::DAQ::Trigger+;
#pragma link C++ class clas12::DAQ::TriggerSupervisor+;
#pragma link C++ class clas12::DAQ::TriggerInterface+;
#pragma link C++ class clas12::DAQ::TriggerDistribution+;
#pragma link C++ class clas12::DAQ::SignalDistribution+;
#pragma link C++ class clas12::DAQ::SubSystemProcessor+;

#pragma link C++ class clas12::DAQ::ModuleChannel+;
#pragma link C++ class clas12::DAQ::Discriminator+;
#pragma link C++ class clas12::DAQ::Scaler+;
#pragma link C++ class clas12::DAQ::TDC+;
#pragma link C++ class clas12::DAQ::ADC+;
#pragma link C++ class clas12::DAQ::FlashADC+;

#pragma link C++ class clas12::DAQ::Module<clas12::DAQ::TDC>+;
#pragma link C++ class clas12::DAQ::Module<clas12::DAQ::ADC>+;
#pragma link C++ class clas12::DAQ::Module<clas12::DAQ::Scaler>+;
#pragma link C++ class clas12::DAQ::Module<clas12::DAQ::FlashADC>+;
#pragma link C++ class clas12::DAQ::Module<clas12::DAQ::Discriminator>+;


//#pragma link C++ function clas12::DriftChamber::P_j_ion_pair(double, int, double);
//#pragma link C++ class clas12::SimpleDriftChamberHit+;
//#pragma link C++ class clas12::DigitizedDriftChamberHit+;
//
//#pragma link C++ class CLAS12MagneticField+;

//#pragma link C++ class Event+;
//#pragma link C++ class HistogramManager+;
//#pragma link C++ class Track+;

#endif
