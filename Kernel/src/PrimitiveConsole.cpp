#include <PrimitiveConsole.h>
#include <Memory.h>

PrimitiveConsole::PrimitiveConsole(FrameBuffer* frameBuffer, Font* font)
{
    this->mFont = font;
    this->mFramebuffer = frameBuffer;
    this->mCursorPosition = sPoint(0, 0);

    this->mBackgroundColor = Color::VeryDarkGray;
    this->mForegroundColor = Color::Lean;

    this->mHeight = frameBuffer->Height / font->Header->charsize;
    this->mWidth = frameBuffer->Width / font->Header->charsize >> 1;

}

void PrimitiveConsole::PutChar(char chr, Color32 fColor, Color32 bColor, int64 xOff, int64 yOff)
{
    register byte* fontptr = (byte*)mFont->GlyphBuffer + (chr * mFont->Header->charsize);

    register byte charszY = mFont->Header->charsize;
    register byte charszX = charszY >> 1;

    register nint pixelY = yOff * charszY;
    register nint pixelX = xOff * charszX;

    for (nint y = pixelY; y < pixelY + charszY; y++)
    {
        for (nint x = pixelX; x < pixelX + charszY; x++)
        {
            WritePixel(x, y, bColor);
            if (fontptr[0] & (0b10000000 >> (x - pixelX)))
            {
                WritePixel(x, y, fColor);
            }
        }
        fontptr++;
    }
    

}

void PrimitiveConsole::Write(char chr, Color32 fg)
{
    switch (chr)
    {
        case '\n':
			Newline();
            return;

		case '\b':
			// Backspace();
			return;

		case '\0':
			// could do nothing or print a space
			return;

		case '\t':
			Write("    ", fg);
			return;
    }

	PutChar(chr, fg, mBackgroundColor, mCursorPosition.X, mCursorPosition.Y);

	mCursorPosition.X++;
	if (mCursorPosition.X >= mWidth)
	{
		Newline();
	}

}

void PrimitiveConsole::Write(const char* str, Color32 color)
{
	for (nint x = 0; str[x]; x++)
	{
		Write(str[x], color);
	}
}

void PrimitiveConsole::Newline(uint32 numLines)
{
	mCursorPosition.Y += numLines;
	mCursorPosition.X = 0;
	if (mCursorPosition.Y >= mHeight)
	{
		// this is where we should scroll
		mCursorPosition.Y = mHeight - 1;
	}
}

void PrimitiveConsole::Clear(Color32 color)
{
    register uint32 height = mFramebuffer->Height;
    register uint32 bpsl = mFramebuffer->BytesPerScanline;
    register nint fbBase = (nint)mFramebuffer->BaseAddress;
    register nint color64 = nint(color) | (nint(color) << 32) ;
    register nint numBytes = mFramebuffer->Width << 2;

    for (register int64 y = 0; y < height; y++)
    {
        memset64((vptr)fbBase, color64, numBytes);
        fbBase += bpsl; 
    }
    
	mCursorPosition = sPoint(0, 0);
}
