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
#define attribute __attribute__
#define forceinline inline __attribute__((always_inline))

#define global extern "C"

#define asm __asm__ volatile 
#define cli asm ("cli");
#define sti asm ("sti");
#define hlt asm ("hlt");
#define pause asm ("pause");
#define os_stop asm ("cli"); while(true) asm ("hlt");

// #define cpuid(code, eax, ebx, ecx, edx) asm ("cpuid" : "=eax"(eax), "=ebx"(ebx), "=ecx"(ecx), "=edx"(edx) : "eax"(code) : "memory")
#define spin(x) for(volatile uint64 y = 0; x > y; y++)
#endif // H_Types