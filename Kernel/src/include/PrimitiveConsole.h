#pragma once
#ifndef H_PrimitiveConsole
#define H_PrimitiveConsole
#include <Types.h>
#include <Structs.h>
/*
	Contains the primitive console that is used to debug information
	to the screen, as well as provide a bare-bones user interface.
*/


struct PrimitiveConsole
{
	// Contructs the PrimitiveConsole using a PSF1 Font and a GOP Framebuffer
	PrimitiveConsole(FrameBuffer* frameBuffer, Font* font);

	// Puts a character at the exact character position specified
	// using a foreground and background color. Does not modify
	// any members of PrimitiveConsole (aside from the framebuffer)
	void PutChar(char chr, Color32 fColor, Color32 bColor, int64 xOff, int64 yOff);

	// Writes a singular character with the specified foreground color
	// and advances the cursor's position by 1. If the cursor has
	// reached the edge of the screen it will advance the Y position by 1
	// and reset the X position to 0.
	// This method also recognizes escapes such as \n, \b and \t (WIP)
	void Write(char chr, Color32 foregroundColor);

	// Writes a zero-terminated string to the console with a specified color
	// and increases the cursor position. This method also recognizes escapes 
	// such as \n, \b and \t (WIP)
	void Write(const char* str, Color32 foregroundColor);

	// Advances the cursor's Y position by @numLines and 
	// set's the cursor's X position to 0
	void Newline(uint32 numLines = 1);

	// Clears the console with the specified color and
	// resets the cursor's position to [0, 0]
	void Clear(Color32 color);


	// Inline Methods //


	forceinline PrimitiveConsole() {}

	// calls Write(char, Color32) with mForegroundColor
	forceinline void Write(char chr) { Write(chr, mForegroundColor); }

	// calls Write(const char*, Color32) with mForegroundColor
	forceinline void Write(const char* str) { Write(str, mForegroundColor); }

	// Alias for Newline()
	forceinline void WriteLine() { Newline(); }

	// Calls WriteLine(const char*, Color32) with mForegroundColor
	forceinline void WriteLine(const char* str) { WriteLine(str, mForegroundColor); }

	// Writes a zero-terminated string to the console with the specified
	// foreground color then adds a new line, advancing the cursor position
	forceinline void WriteLine(const char* str, Color32 foregroundColor) { Write(str, foregroundColor); Newline(); }

	// Clears the console using the console's background color
	forceinline void Clear() { Clear(mBackgroundColor); }


	// Getters and Setters //


	forceinline void SetCursorPosition(int64 X, int64 Y) { mCursorPosition = sPoint(X, Y); }
	forceinline sPoint GetCursorPosition() { return mCursorPosition; }

	forceinline void SetForegroundColor(Color32 color) { mForegroundColor = color; }
	forceinline void SetBackgroundColor(Color32 color) { mBackgroundColor = color; }

	forceinline Color32 GetForegroundColor() { return mForegroundColor; }
	forceinline Color32 GetBackgroundColor() { return mBackgroundColor; }


private:

	// Private Members //

	Font* mFont;
	FrameBuffer* mFramebuffer;
	sPoint mCursorPosition;

	int64 mWidth;
	int64 mHeight;

	Color32 mForegroundColor;
	Color32 mBackgroundColor;

	// Private Methods //

	forceinline void WritePixel(int64 posX, int64 posY, Color32 color)
	{
		if ((posX >= mFramebuffer->Width) | (posX < 0)) return;
		if ((posY >= mFramebuffer->Height) | (posY < 0)) return;

		register Color32* buff = (Color32*)mFramebuffer->BaseAddress + posX + (posY * (mFramebuffer->BytesPerScanline >> 2));
		buff[0] = color;

	}

	forceinline Color32 ReadPixel(int64 posX, int64 posY)
	{
		if ((posX >= mFramebuffer->Width) | (posX < 0)) return Color::Black;
		if ((posY >= mFramebuffer->Height) | (posY < 0)) return Color::Black;
		register Color32* ptr = (Color32*)mFramebuffer->BaseAddress;
		return ptr[posX + (posY * (mFramebuffer->BytesPerScanline >> 2))];
	}

};

#endif // !H_PrimitiveConsole
