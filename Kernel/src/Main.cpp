#include <Kernel.h>

namespace Kernel
{
	extern "C" void KernelMain(BootInfo bootInfo)
	{
		InitializeKernel(bootInfo);
		while (1) ;
	}
}