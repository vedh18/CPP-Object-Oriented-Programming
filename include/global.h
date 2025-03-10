#ifndef GLOBAL_H
#define GLOBAL_H

#include "library.h"  // Contains the definition of the Library class

// Declare the global Library object.
// This tells the compiler that the Library instance exists somewhere.
extern const int timeUnit;
extern Library library;

#endif // GLOBAL_H