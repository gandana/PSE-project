//============================================================================
// Name        : DesignByContract.h
// Author      : Serge Demeyer, modified by Kasper Engelen
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : Declarations for design by contract in C++
//============================================================================

#include <iostream>
#include <cstdlib>

// We replaced the hidden __assert with a standard C++ crash (std::abort)
#define REQUIRE(assertion, what) \
if (!(assertion)) { std::cerr << "PRECONDITION FAILED: " << what << "\n"; std::abort(); }

#define ENSURE(assertion, what) \
if (!(assertion)) { std::cerr << "POSTCONDITION FAILED: " << what << "\n"; std::abort(); }
