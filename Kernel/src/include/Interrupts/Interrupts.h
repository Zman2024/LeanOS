#pragma once
#ifndef H_Interrupts
#define H_Interrupts
#include <Globals.h>

namespace Interrupts
{
	constexpr byte IRQ_OFFSET = 0x20;

	struct RegisterState
	{
		nint rax;
		nint rbx;
		nint rcx;
		nint rdx;

		nint rsi;
		nint rdi;

		nint r8;
		nint r9;
		nint r10;
		nint r11;
		nint r12;
		nint r13;
		nint r14;
		nint r15;

		nint rflags;
	};

	/* From: https://wiki.osdev.org/Interrupt_Vector_Table#CPU_Interrupt_Layout
	| INT #     | Description
	+-----------+-----------------------------------
	| 0x00      | Divide by 0
	| 0x01      | Reserved
	| 0x02      | NMI Interrupt
	| 0x03      | Breakpoint (INT3)
	| 0x04      | Overflow (INTO)
	| 0x05      | Bounds range exceeded (BOUND)
	| 0x06      | Invalid opcode (UD2)
	| 0x07      | Device not available (WAIT/FWAIT)
	| 0x08      | Double fault
	| 0x09      | Coprocessor segment overrun
	| 0x0A      | Invalid TSS
	| 0x0B      | Segment not present
	| 0x0C      | Stack-segment fault
	| 0x0D      | General protection fault
	| 0x0E      | Page fault
	| 0x0F      | Reserved
	| 0x10      | x87 FPU error
	| 0x11      | Alignment check
	| 0x12      | Machine check
	| 0x13      | SIMD Floating-Point Exception
	| 0x14-0x1F | Reserved
	| 0x20-0xFF | User definable (We will put the IRQs here)

	From: https://wiki.osdev.org/Interrupt_Vector_Table#Default_Hardware_Interrupt_Layout
	Master:
	| IRQ # | Description
	--------+------------------------------
	| 0     | PIT
	| 1     | Keyboard
	| 2     | 8259A slave controller
	| 3     | COM2 / COM4
	| 4     | COM1 / COM3
	| 5     | LPT2
	| 6     | Floppy controller
	| 7     | LPT1

	Slave:
	--------+------------------------------
	| 8     | RTC
	| 9     | Unassigned
	| 10    | Unassigned
	| 11    | Unassigned
	| 12    | Mouse controller
	| 13    | Math coprocessor
	| 14    | Hard disk controller 1
	| 15    | Hard disk controller 2
	*/
	namespace ISR
	{
		enum : byte
		{
			/* CPU Exception Table */
			DivideByZero = 0x00,
			Debug = 0x01,
			NonMaskable = 0x02,
			Breakpoint = 0x03,
			OverflowTrap = 0x04,
			BoundRangeExceeded = 0x05,
			InvalideOpcode = 0x06,
			CoprocessorNA = 0x07,
			DoubleFault = 0x08,
			CoprocessorSegmentOverrun = 0x09,
			InvalidStateSegment = 0x0A,
			SegmentMissing = 0x0B,
			StackException = 0x0C,
			GeneralProtection = 0x0D,
			PageFault = 0x0E,
			Reserved = 0x0F,
			CoprocessorError = 0x10,	//x87 FPU error
			AlignmentCheck = 0x11,
			MachineCheck = 0x12,
			SIMDException = 0x13,

			// Master
			PIT = IRQ_OFFSET, HPET0 = IRQ_OFFSET,
			Keyboard = IRQ_OFFSET + 1,
			SlaveEnabled = IRQ_OFFSET + 2,
			COM2 = IRQ_OFFSET + 3,
			COM1 = IRQ_OFFSET + 4,
			DataLPT2 = IRQ_OFFSET + 5,
			FloppyDisk = IRQ_OFFSET + 6,
			DataLPT1 = IRQ_OFFSET + 7,

			// Slave
			RTC = IRQ_OFFSET + 8, HPET1 = IRQ_OFFSET + 8,
			Redirect0 = IRQ_OFFSET + 9,
			Reserved1 = IRQ_OFFSET + 0xA,
			Reserved2 = IRQ_OFFSET + 0xB,
			Mouse = IRQ_OFFSET + 0xC,
			NumericCoprocessorError = IRQ_OFFSET + 0xD,
			FixedDiskController1 = IRQ_OFFSET + 0xE,
			FixedDiskController2 = IRQ_OFFSET + 0xF,

			SpuriousInterrupt = 0xFF,

		};
	};


	void InitializeStubs();
	void SetInterruptHandler(vptr handler, byte interrupt, IdtType type = IdtType::InterruptGate);

	void hDivideByZeroFault();
	void hDebug();
	void hNonMaskableFault();
	void hBreakpointFault();
	void hOverflowTrap();
	void hBoundRangeFault();
	void hInvalidOpcodeFault();
	void hCoprocessorNAFault();
	void hDoubleFault(nint intr, nint code);
	void hCoprocessorSegmentOverrunFault();
	void hInvalidStateSegmentFault(nint intr, nint code);
	void hSegmentMissingFault(nint intr, nint code);
	void hStackFault(nint intr, nint code);
	void hGeneralProtectionFault(nint intr, nint code);
	void hPageFault(nint intr, nint code);
	void hCoprocessorFault();
	void hAlignmentCheck(nint intr, nint code);
	void hMachineCheck();
	void hSIMDFault();
	void hKeyboardInt();
	void hPitTick();
	void hRtcTick();

	void hStub(nint interruptNum);
}

#endif