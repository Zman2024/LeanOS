#pragma once
#ifndef H_Globals
#define H_Globals
#include <Types.h>
#include <PrimitiveConsole.h>
#include <String.h>
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

forceinline void kprintf(const char* fstr, nint p0 = 0, nint p1 = 0, nint p2 = 0, nint p3 = 0, nint p4 = 0, nint p5 = 0, nint p6 = 0, nint p7 = 0, nint p8 = 0, nint p9 = 0)
{
	Console.Write(format(fstr, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9));
}

forceinline void kprintlnf(const char* fstr, nint p0 = 0, nint p1 = 0, nint p2 = 0, nint p3 = 0, nint p4 = 0, nint p5 = 0, nint p6 = 0, nint p7 = 0, nint p8 = 0, nint p9 = 0)
{
	Console.WriteLine(format(fstr, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9));
}

forceinline void debug(const char* fstr, nint p0 = 0, nint p1 = 0, nint p2 = 0, nint p3 = 0, nint p4 = 0, nint p5 = 0, nint p6 = 0, nint p7 = 0, nint p8 = 0, nint p9 = 0)
{
	Console.WriteLine(format(fstr, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9), 0x00303030);
}

forceinline void warn(const char* fstr, nint p0 = 0, nint p1 = 0, nint p2 = 0, nint p3 = 0, nint p4 = 0, nint p5 = 0, nint p6 = 0, nint p7 = 0, nint p8 = 0, nint p9 = 0)
{
	Console.WriteLine(format(fstr, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9), Color::Yellow);
}

forceinline void error(const char* fstr, nint p0 = 0, nint p1 = 0, nint p2 = 0, nint p3 = 0, nint p4 = 0, nint p5 = 0, nint p6 = 0, nint p7 = 0, nint p8 = 0, nint p9 = 0)
{
	Console.WriteLine(format(fstr, p0, p1, p2, p3, p4, p5, p6, p7, p8, p9), Color::Red);
}

#endif