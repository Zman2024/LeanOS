#include <Kernel.h>

namespace Kernel
{
    void InitializeKernel(const BootInfo& bootInfo)
    {
		InitializeGDT();

		InitializeExceptions();

		InitializePaging(bootInfo);

		InitializeACPI(bootInfo);

		InitializeIRQ();
    }

	void InitializeIRQ(bool forceUsePic)
	{
	}

	void InitializeACPI(const BootInfo & bootInfo)
	{
	}

	void InitializePaging(const BootInfo & bootInfo)
	{
	}

	void InitializeExceptions()
	{
	}

	void InitializeGDT()
	{
	}

}
