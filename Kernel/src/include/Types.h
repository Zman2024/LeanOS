#pragma once
#ifndef H_Types
#define H_Types
#include <stddef.h>

// Typedefs //

typedef size_t nint; // Architecture native integer (native int)
typedef void* vptr;

typedef signed char sbyte;
typedef signed char int8;
typedef signed short int16;
typedef signed int int32;
typedef signed long long int64;

typedef unsigned char byte;
typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long long ulong;

typedef signed char  i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float fp32;
typedef double fp64;
typedef long double fp128; // sizeof(fp128) gives me 16 so... i guess?

typedef uint32 Color32;

// Global Constants //
constexpr auto PAGE_SIZE = 0x1000; // The size of a physical page

// Macros //
#ifdef VISUAL_STUDIO_EDITOR
#define attribute(x) 
#define forceinline
#define asm(x)
#define cli
#define sti
#define hlt
#define pause
#define intcall(x)
#define OS_HLT
#define halt
#define cpuid(level, a, b, c, d)
#define spin(x)
#define global extern "C"
#define fast
#else
#define attribute __attribute__
#define forceinline inline __attribute__((always_inline))

#define global extern "C"

#define asm __asm__ volatile 
#define cli asm ("cli");
#define sti asm ("sti");
#define hlt asm ("hlt");
#define pause asm ("pause");
#define intcall(x) { asm ("int %0" : : "byte"((byte)x)); }
#define OS_HLT asm ("cli"); while(true) asm ("hlt");
#define halt asm ("cli"); while(true) asm ("hlt");
#define cpuid(level, a, b, c, d)			\
  asm ("cpuid\n\t"					\
	   : "=a" (a), "=b" (b), "=c" (c), "=d" (d)	\
	   : "0" (level)	\
	   : "memory")

// #define cpuid(code, eax, ebx, ecx, edx) asm ("cpuid" : "=eax"(eax), "=ebx"(ebx), "=ecx"(ecx), "=edx"(edx) : "eax"(code) : "memory")
#define spin(x) for(volatile uint64 y = 0; x > y; y++)
#endif // VISUAL_STUDIO_EDITOR
#endif // H_Types