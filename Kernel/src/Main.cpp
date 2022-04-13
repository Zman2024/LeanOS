#include <Kernel.h>

namespace Kernel
{
	void ClearBSS()
	{
		nint bssLength = nint(&_BssDataEnd) - nint(&_BssDataStart);
		memset64(&_BssDataStart, 0x00, bssLength);
	}

	global void KernelMain(BootInfo bootInfo)
	{
		ClearBSS();

		Console = PrimitiveConsole(bootInfo.Framebuffer, bootInfo.Font);
		Console.Clear();

		Console.WriteLine("LeanOS\nI LOVE LEAN!!!");

		InitializeKernel(bootInfo);

		// once we have irqs this will just be "while (true) hlt;" 
		// but we dont have that right now so we drinkin lean
		drinklean;
	}
}