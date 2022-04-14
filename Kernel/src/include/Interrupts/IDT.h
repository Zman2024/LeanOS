#pragma once
#ifndef H_IDT
#define H_IDT
#include <Types.h>

enum struct IdtType : byte
{
	InterruptGate = 0b10001110,
	TrapGate = 0b10001111,
};

struct IDTDescEntry
{
	uint16 Offset0;
	uint16 Selector; // Code segment selector in GTD / LDT

	byte IST;
	IdtType TypeAttribs;

	uint16 Offset1;

	uint32 Offset2;
	uint32 rsv0;

	forceinline void SetOffset(nint offset)
	{
		this->Offset0 = u16(offset & 0xFFFF);
		this->Offset1 = u16((offset & 0xFFFF0000) >> 16);
		this->Offset2 = u32((offset & 0xFFFFFFFF00000000) >> 32);
	}

	forceinline nint GetOffset()
	{
		nint value = (nint)(Offset0 & 0xFFFF);
		value |= ((nint)Offset1) << 16;
		value |= ((nint)Offset2) << 32;
		return value;
	}

};

struct IDTR
{
	uint16 Limit;
	uint64 Offset;
} attribute((packed));


global void LoadGIDT();

#endif