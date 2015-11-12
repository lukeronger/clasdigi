clasdigi : Clas12 digitizer
===========================

Installing
----------

###Requirements

- Modern C++ compiler with c++11/14 support
- CLHEP
- ROOT6

###Building

```
git clone git@github.com:whit2333/clasdigi.git
mkdir clasdigi_build && cd clasdigi_build
cmake ../clasdigi/. -DCMAKE_INSTALL_PREFIX=$HOME
make install
```

###Using with root

To use these libraries seamlessly in root add this to your rootlogon.C
   gInterpreter->AddIncludePath("$HOME/include/ClasDigi");
   gSystem->AddIncludePath(" -I$HOME/include/ClasDigi");
   gSystem->Load("libClasGeo.so");
   gSystem->Load("libClasHits.so");
   gSystem->Load("libClasSim.so");
   gSystem->Load("libClasDAQ.so");
   gSystem->Load("libClasSigs.so");
   gSystem->Load("libClasKine.so");
   gSystem->Load("libClasMag.so");

Status
------

This project is very much in its infancy.

Send questions to Whitney Armstrong ( whit@jlab.org )

