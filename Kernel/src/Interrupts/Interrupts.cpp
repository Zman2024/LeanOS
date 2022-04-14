#include <Interrupts/Interrupts.h>

nint GlobalInterruptTable[256];

namespace Interrupts
{
	global RegisterState* GetRegisterDump();

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

	void hDivideByZero()
	{
		warn("Divided by zero!");
	}

	void hStub(nint interruptNum)
	{
		warn("An interrupt without a handler was called (int %x0)", interruptNum);
	}
}
