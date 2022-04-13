#pragma once
#ifndef H_Globals
#define H_Globals
#include <Types.h>
#include <PrimitiveConsole.h>
/*
	Contains global variables and symbols used throughout the kernel
*/

extern PrimitiveConsole Console;

// Use &_KernelStart to get the kernel's start address
global byte _KernelStart;

// Use &_BssDataStart to get the start of the bss section
global byte _BssDataStart;

// Use &_BssDataEnd to get the end of the bss section
global byte _BssDataEnd;

// Use &_KernelStart to get the kernel's end address
global byte _KernelEnd;

#endif