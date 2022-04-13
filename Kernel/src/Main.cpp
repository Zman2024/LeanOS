#include <Kernel.h>

namespace Kernel
{
	void ClearBSS(BootInfo& bootInfo)
	{

	}

	global void KernelMain(BootInfo bootInfo)
	{

		Console = PrimitiveConsole(bootInfo.Framebuffer, bootInfo.Font);
		Console.Clear();

		Console.WriteLine("LeanOS\nI LOVE LEAN!!!");

		InitializeKernel(bootInfo);

		// once we have irqs this will just be "while (true) hlt;" 
		// but we dont have that right now so we drinkin lean
		drinklean;
	}
}