#pragma once
#ifndef H_Memory
#define H_Memory
#include <Types.h>

// Defined in Memory.asm
global void memset64(vptr destination, uint64 value, nint numBytes);
global void memset32(vptr destination, uint32 value, nint numBytes);
global void memset16(vptr destination, uint16 value, nint numBytes);
global void memset8(vptr destination, uint8 value, nint numBytes);

#endif