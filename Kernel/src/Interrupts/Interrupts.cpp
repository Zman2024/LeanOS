#include <Interrupts/Interrupts.h>

nint GlobalInterruptTable[256];

namespace Interrupts
{
	global RegisterState* GetRegisterDump();

	forceinline void TooMuchLean()
	{
		Console.SetBackgroundColor(Color::BetterLean);
		Console.SetForegroundColor(Color::White);
		Console.Clear();
	}

	void InitializeStubs()
	{
		IDTDescEntry* entry = (IDTDescEntry*)(GlobalIDTR.Offset);
		for (nint x = 0; x < 0xFF; x++)
		{
			entry[x].SetOffset(GlobalHandlerStubTable[x]);
			entry[x].TypeAttribs = IdtType::InterruptGate;
			entry[x].Selector = 0x08;

			GlobalInterruptTable[x] = (nint)hStub;
		}
	}

	void SetInterruptHandler(vptr handler, byte interrupt, IdtType type)
	{
		IDTDescEntry* base = (IDTDescEntry*)(GlobalIDTR.Offset);
		base[interrupt].TypeAttribs = type;
		GlobalInterruptTable[interrupt] = (nint)handler;
	}

	void hDivideByZeroFault()
	{
		// Dont know if it is necessary to halt operation for all
		// divide by zero exceptions
		warn("Divided by zero!");
	}

	void hDebug()
	{
		warn("Debug");
	}

	void hNonMaskableFault()
	{
		warn("Non Maskable Interrupt");
		drinklean;
	}

	void hBreakpointFault()
	{
		TooMuchLean();
		kprintf("Breakpoint Fault");
		drinklean;
	}
	
	void hOverflowTrap()
	{
		TooMuchLean();
		warn("Overflow Trap");
		drinklean
	}

	void hBoundRangeFault()
	{
		TooMuchLean();
		kprintf("Bound Range Exceeded");
		drinklean;
	}

	void hInvalidOpcodeFault()
	{
		TooMuchLean();
		kprintf("PROCESSOR COULD NOT FIND THE LEAN CUP!!!!!");
		drinklean;
	}

	void hCoprocessorNAFault()
	{
		TooMuchLean();
		kprintf("Coprocessor NA");
		drinklean;
	}

	void hDoubleFault(nint intr, nint code)
	
	{
		TooMuchLean();
		kprintf("DOUBLE FAULT! LEAN WAS TOO DRIPPY!!!");
		drinklean;
	}

	void hCoprocessorSegmentOverrunFault()
	{
		TooMuchLean();
		kprintf("Coprocessor Segment Overrun");	
		drinklean;
	}

	void hInvalidStateSegmentFault(nint intr, nint code)
	{
		TooMuchLean();
		kprintf("State Segment Not Present\nCode: %x0", code);
	}

	void hSegmentMissingFault(nint intr, nint code)
	{
		TooMuchLean();
		kprintf("Segment Not Present\nCode: %x0", code);
		drinklean;
	}

	void hStackFault(nint intr, nint code)
	{
		TooMuchLean();
		warn("Stack-Segment Fault\nCode: %x0", code);
		drinklean;
	}

	void hGeneralProtectionFault(nint intr, nint code)
	{
		TooMuchLean();
		kprintf("General Protection Fault");
		drinklean;
	}

	void hPageFault(nint intr, nint code)
	{
		TooMuchLean();
		kprintf("Page Fault");
		drinklean;
	}

	void hCoprocessorFault()
	{
		TooMuchLean();
		kprintf("Coprocessor Fault");
		drinklean;
	}

	void hAlignmentCheck(nint intr, nint code)
	{
		TooMuchLean();
		kprintf("Alignment check\nCode: %x0", code);
		drinklean;
	}

	void hMachineCheck()
	{
		TooMuchLean();
		kprintf("DRIP CHECK (Machine Check)");
		drinklean;
	}

	void hSIMDFault()
	{
		TooMuchLean();
		kprintf("SIMD Fault");
		drinklean;
	}

	void hKeyboardInt()
	{

	}

	void hPitTick()
	{

	}

	void hRtcTick()
	{

	}

	void hStub(nint interruptNum)
	{
		TooMuchLean();
		kprintln("An interrupt without a handler was called (int %x0)", interruptNum);
		drinklean;
	}
}
