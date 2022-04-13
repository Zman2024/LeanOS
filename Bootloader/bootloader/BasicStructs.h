#ifndef H_BasicStructs
#define H_BasicStructs

#include <efi.h>
#include <efilib.h>
#include <elf.h>

typedef unsigned char byte;
typedef unsigned long long size_t;

typedef unsigned int uint;

#define PSF_MAGIC0 0x36
#define PSF_MAGIC1 0x04

typedef struct PSF1Header 
{
	byte magic[2];
	byte mode;
	byte charsize;
} PSF1Header;

typedef struct PSF1Font 
{
	PSF1Header* Header;
	void* GlyphBuffer;

} PSF1Font;

typedef struct Framebuffer
{
	void* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int BytesPerScanline;

} Framebuffer;

typedef struct BootInfo
{
	Framebuffer* Framebuffer;
	PSF1Font* Font;
	EFI_MEMORY_DESCRIPTOR* MemoryMap;
	uint64_t MapSize;
	uint64_t DescriptorSize;
	void* RSDP;
	void* LoadingImage;
} BootInfo;

#endif