#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;

//#pragma link C++ defined_in "subdir/MyHeader.h";

#pragma link C++ namespace clas12;
#pragma link C++ namespace clas12::sim;

//#pragma link C++ namespace nlohmann;
//#pragma link C++ class nlohmann::json+;

#pragma link C++ class clas12::sim::ThrownEvent+;
#pragma link C++ class clas12::sim::RunConfiguration+;

#endif
