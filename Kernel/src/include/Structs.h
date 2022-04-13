#pragma once
#ifndef H_Structs
#define H_Structs
#include <Types.h>
/*
	Contains data structures which have
	little to no executable code
*/

struct FontHeader
{
	byte magic[2];
	byte mode;
	byte charsize;
};

struct PSF1Font
{
	FontHeader* Header;
	vptr GlyphBuffer;
};

struct FrameBuffer
{
	vptr BaseAddress;
	nint BufferSize;
	uint32 Width;  // the number of pixels on the x axis
	uint32 Height; // the number of pixels on the y axis
	uint32 BytesPerScanline; // the total number of bytes per scanline
};

struct BootInfo
{
	FrameBuffer* Framebuffer;
	PSF1Font* Font;
	vptr MemoryMap;
	uint64 MapSize;
	uint64 MapDescriptorSize;
	vptr RSDP;
	vptr LoadingImage;
};

struct sPoint
{
	inline sPoint() 
	{
		this->X = 0;
		this->Y = 0;
	}

	inline sPoint(int64 x, int64 y)
	{
		this->X = x;
		this->Y = y;
	}

	int64 X;
	int64 Y;
};

struct uPoint
{
	inline uPoint() 
	{
		this->X = 0;
		this->Y = 0;
	}

	inline uPoint(uint64 x, uint64 y)
	{
		this->X = x;
		this->Y = y;
	}
	
	uint64 X;
	uint64 Y;
};

namespace Color
{
	enum : Color32
	{
		White = 0xFFFFFFFF,
		Black = 0xFF000000,

		Red = 0xFFFF0000,
		Green = 0xFF00FF00,
		Blue = 0xFF0000FF,

		Cyan = 0xFF00FFFF,
		Yellow = 0xFFFFFF00,
		Purple = 0xFFFF00FF,
		Lean = Purple,

		DarkGray = 0xFF101010,
		VeryDarkGray = 0xFF080808,
		DarkRed = 0xFF900000,

	};
}

#endif