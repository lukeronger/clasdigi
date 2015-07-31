#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;

#pragma link C++ namespace clas12;
#pragma link C++ namespace clas12::DriftChamber;
#pragma link C++ namespace clas12::sigs;

#pragma link C++ class clas12::sigs::DigitizedSignal+;
#pragma link C++ class clas12::sigs::FlashADCSignal+;
#pragma link C++ class clas12::sigs::ADCSignal+;
#pragma link C++ class clas12::sigs::TDCSignal+;

#pragma link C++ class clas12::sigs::CLAS12SigsEvent+;
#pragma link C++ class clas12::sigs::HTCCSigsEvent+;
#pragma link C++ class clas12::sigs::DCSigsEvent+;

//#pragma link C++ function clas12::DriftChamber::P_j_ion_pair(double, int, double);
//
//#pragma link C++ class clas12::SimpleDriftChamberHit+;
//#pragma link C++ class clas12::DigitizedDriftChamberHit+;
//
//#pragma link C++ class CLAS12MagneticField+;

//#pragma link C++ class Event+;
//#pragma link C++ class HistogramManager+;
//#pragma link C++ class Track+;

#endif
