#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;

#pragma link C++ namespace clas12;
#pragma link C++ namespace clas12::geo;
#pragma link C++ namespace clas12::geo::DC;

#pragma link C++ class clas12::geo::DCWire+;
#pragma link C++ class clas12::geo::DCSuperLayer+;

#pragma link C++ class std::map<clas12::geo::DCSuperLayer, TH2Poly*>+;
#pragma link C++ class std::unordered_map<clas12::geo::DCSuperLayer, TH2Poly*>+;

#pragma link C++ function clas12::geo::CosAngle2( double , double , double , double , double , double );

#pragma link C++ class clas12::geo::RCWire+;


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
