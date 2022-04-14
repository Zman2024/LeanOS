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

	void InitializeGDT()
	{
		kprintln("Loading Global Descriptor Table (GDT)...");
		// Create and load GDT
		GDTDescriptor desc{};
		desc.Size = sizeof(GDT) - 1;
		desc.Offset = (u64)&GlobalGDT;
		Interrupts::LoadGDT(&desc);
	}

	void InitializeExceptions()
	{
		using namespace Interrupts;

		kprintln("Loading Interrupt Vector Table (IDTR)...");

		// Initialize IDTR
		GlobalIDTR.Limit = 0x1FF;
		GlobalIDTR.Offset = (nint)GlobalIDTROffset;
		memset64(GlobalIDTROffset, 0x00, PAGE_SIZE);

		// Load stubs into IDTR
		InitializeStubs();

		// Load the interrupt table
		LoadGIDT();

		kprintln("Registering Fault / Interrupt Handlers...");

		SetInterruptHandler((vptr)hDivideByZero, ISR::DivideByZero);
		SetInterruptHandler((vptr)hDoubleFault, ISR::DoubleFault);

		asm("int 0x08");

	}

	void InitializePaging(const BootInfo & bootInfo)
	{
	}

	void InitializeACPI(const BootInfo & bootInfo)
	{
	}

	void InitializeIRQ(bool forceUsePic)
	{
	}

}
