#include <Kernel.h>

namespace Kernel
{
	global void KernelMain(BootInfo bootInfo)
	{
		InitializeKernel(bootInfo);

		OS_HLT;
	}
}