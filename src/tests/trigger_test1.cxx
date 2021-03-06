#include <iostream>
#include <random>
#include "DigitizedSignal.h"
#include "FlashADCSignal.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"

unsigned int Factorial( unsigned int number ) {
   return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
   REQUIRE( Factorial(1) == 1 );
   REQUIRE( Factorial(2) == 2 );
   REQUIRE( Factorial(3) == 6 );
   REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE( "vectors can be sized and resized", "[vector]" ) {

   std::vector<int> v( 5 );

   REQUIRE( v.size() == 5 );
   REQUIRE( v.capacity() >= 5 );

   SECTION( "resizing bigger changes size and capacity" ) {
      v.resize( 10 );

      REQUIRE( v.size() == 10 );
      REQUIRE( v.capacity() >= 10 );
   }
   SECTION( "resizing smaller changes size but not capacity" ) {
      v.resize( 0 );

      REQUIRE( v.size() == 0 );
      REQUIRE( v.capacity() >= 5 );
   }
   SECTION( "reserving bigger changes capacity but not size" ) {
      v.reserve( 10 );

      REQUIRE( v.size() == 5 );
      REQUIRE( v.capacity() >= 10 );
   }
   SECTION( "reserving smaller does not change size or capacity" ) {
      v.reserve( 0 );

      REQUIRE( v.size() == 5 );
      REQUIRE( v.capacity() >= 5 );
   }
}

//int main( int argc, char **argv )
//{
//
//   clas12::sigs::DigitizedSignal sig0(8);
//
//   sig0.fCrate = 1;
//   sig0.fSlot  = 3;
//
//   sig0.fTag = 100;
//   sig0.fNum = 12;
//
//   sig0.Print();
//
//
//   std::cout << "derp\n";
//
//   return 0;
//}

