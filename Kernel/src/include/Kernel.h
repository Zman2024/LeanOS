#pragma once
#ifndef H_Kernel
#define H_Kernel
#include <Types.h>
#include <Structs.h>
#include <PrimitiveConsole.h>
#include <Globals.h>
#include <Memory.h>
#include <String.h>
#include <Interrupts/GTD.h>
#include <Interrupts/IDT.h>
#include <Interrupts/Interrupts.h>


namespace Kernel
{
	// Calls the other initialize functions
	void InitializeKernel(const BootInfo& bootInfo);

	// Initializes the global descriptor table for interrupts
	void InitializeGDT();

	// Initializes interrupts (duh)
	void InitializeExceptions();

	// Initializes Paging and Memory Mapping
	void InitializePaging(const BootInfo& bootInfo);

	// Init ACPI
	void InitializeACPI(const BootInfo& bootInfo);

	// Use PIC / APIC
	void InitializeIRQ(bool forceUsePic = false);

}

#endif