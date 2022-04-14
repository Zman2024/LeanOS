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

		SetInterruptHandler((vptr)hDivideByZeroFault, ISR::DivideByZero);
		SetInterruptHandler((vptr)hDebug, ISR::Debug);
		SetInterruptHandler((vptr)hNonMaskableFault, ISR::NonMaskable);
		SetInterruptHandler((vptr)hBreakpointFault, ISR::Breakpoint);
		SetInterruptHandler((vptr)hOverflowTrap, ISR::OverflowTrap);
		SetInterruptHandler((vptr)hBoundRangeFault, ISR::BoundRangeExceeded);
		SetInterruptHandler((vptr)hInvalidOpcodeFault, ISR::InvalideOpcode);
		SetInterruptHandler((vptr)hCoprocessorNAFault, ISR::CoprocessorNA);
		SetInterruptHandler((vptr)hDoubleFault, ISR::DoubleFault);
		SetInterruptHandler((vptr)hCoprocessorSegmentOverrunFault, ISR::CoprocessorSegmentOverrun);
		SetInterruptHandler((vptr)hInvalidStateSegmentFault, ISR::InvalidStateSegment);
		SetInterruptHandler((vptr)hSegmentMissingFault, ISR::SegmentMissing);
		SetInterruptHandler((vptr)hStackFault, ISR::StackException);
		SetInterruptHandler((vptr)hGeneralProtectionFault, ISR::GeneralProtection);
		SetInterruptHandler((vptr)hPageFault, ISR::PageFault);
		SetInterruptHandler((vptr)hCoprocessorFault, ISR::CoprocessorError);
		SetInterruptHandler((vptr)hAlignmentCheck, ISR::AlignmentCheck);
		SetInterruptHandler((vptr)hMachineCheck, ISR::MachineCheck);
		SetInterruptHandler((vptr)hSIMDFault, ISR::SIMDException);
		SetInterruptHandler((vptr)hKeyboardInt, ISR::Keyboard);
		SetInterruptHandler((vptr)hPitTick, ISR::PIT);
		SetInterruptHandler((vptr)hRtcTick, ISR::RTC);

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
