clasdigi
========

Basic Design Idea
-----------------

clasdigi is an attempt to isolate and simplify the steps required to go from 
simulation to realistic digitized data that is ready for reconstruction. These 
steps are

1. Event/Hit extraction from Geant4 simulation 

2. Realistic digitization of hits

3. Output formating 

The "hits library" will define and provide the means to **efficiently** extract 
information from geant4. The "DAQ library" provide utilities that are used in 
said hit extraction as well in a separate step/program aimed at providing a 
realistic digitized signal. 

The hits library uses the ROOT io facilities. Mostly hits will be held in the 
TClonesArray class which is created as instances in a tree branch or event 
class data member.

The "DAQ library" is designed to emulate the actual Data acquisition system. It 
has TDC, ADC, and discriminator modules. These can be used in the




