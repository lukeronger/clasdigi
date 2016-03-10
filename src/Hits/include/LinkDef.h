#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass;

#pragma link C++ namespace clas12;
#pragma link C++ namespace clas12::hits;

#pragma link C++ class clas12::hits::TriggerEvent+;
#pragma link C++ class clas12::hits::CLAS12HitsEvent+;
#pragma link C++ class clas12::hits::HTCCHitsEvent+;
#pragma link C++ class clas12::hits::ECHitsEvent+;
#pragma link C++ class clas12::hits::DCHitsEvent+;
#pragma link C++ class clas12::hits::RCHitsEvent+;
#pragma link C++ class clas12::hits::ForwardHitMask+;

#pragma link C++ class clas12::hits::RecoilScintHit+;
#pragma link C++ class clas12::hits::PhotonHit+;
#pragma link C++ class clas12::hits::RecoilScintEvent+;

#pragma link C++ class clas12::hits::ADCHit+;
#pragma link C++ class clas12::hits::TDCHit+;
#pragma link C++ class clas12::hits::FlashADCHit+;

#pragma link C++ function clas12::hits::P_j_ion_pair(double, int, double);
#pragma link C++ function clas12::hits::does_step_create_ion_pair(double, int, double);

#pragma link C++ class clas12::hits::DriftChamberIonPairHit+;
#pragma link C++ class clas12::hits::DriftChamberParticleHit+;
#pragma link C++ class clas12::hits::RecoilChamberParticleHit+;
#pragma link C++ class clas12::hits::ParticleHit+;

//#pragma link C++ class clas12::DriftChamberIonPairHit+;

//#pragma link C++ class Event+;
//#pragma link C++ class HistogramManager+;
//#pragma link C++ class Track+;

#endif
