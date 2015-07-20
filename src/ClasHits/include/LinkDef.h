#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;

#pragma link C++ namespace clas12;
#pragma link C++ namespace clas12::DriftChamber;
#pragma link C++ namespace clas12::hits;

#pragma link C++ class clas12::hits::ADCHit+;
#pragma link C++ class clas12::hits::TDCHit+;

#pragma link C++ function clas12::DriftChamber::P_j_ion_pair(double, int, double);

#pragma link C++ class clas12::SimpleDriftChamberHit+;
#pragma link C++ class clas12::DigitizedDriftChamberHit+;

#pragma link C++ class CLAS12MagneticField+;

//#pragma link C++ class Event+;
//#pragma link C++ class HistogramManager+;
//#pragma link C++ class Track+;

#endif
