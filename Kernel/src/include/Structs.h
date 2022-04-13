#pragma once
#ifndef H_Structs
#define H_Structs
#include <Types.h>

struct FontHeader
{
	byte magic[2];
	byte mode;
	byte charsize;
};

struct Font
{
	FontHeader* Header;
	vptr GlyphBuffer;
};

struct FrameBuffer
{
	vptr BaseAddress;
	size_t BufferSize;
	uint32 Width;
	uint32 Height;
	uint32 PixelsPerScanline;
};

struct BootInfo
{
	FrameBuffer* Framebuffer;
	Font* font;
	vptr MemoryMap;
	uint64 MapSize;
	uint64 MapDescriptorSize;
	vptr RSDP;
	vptr LoadingImage;
};

#endif