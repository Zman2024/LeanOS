#pragma once
#ifndef H_String
#define H_String
#include <Types.h>
#include <Memory.h>

// Defined in Memory.asm
// returns the number of characters in a string (excluding '\0')
// eg: "hi\0" returns 2
global nint strlen(const char* str);

// reverses the string (in place-ish)
void reverse(char* str);

// converts a signed / unsigned number into a string
const char* tostr(int64 value, bool sign = true);

// converts an unsigned number into an hstring
const char* tohex(uint64 value);

// oh god oh hell
const char* format(const char* fstring, nint p0 = 0, nint p1 = 0, nint p2 = 0, nint p3 = 0, nint p4 = 0, nint p5 = 0, 
					nint p6 = 0, nint p7 = 0, nint p8 = 0, nint p9 = 0);

#endif