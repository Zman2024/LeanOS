#pragma once
#ifndef H_Kernel
#define H_Kernel
#include <Types.h>
#include <Structs.h>
#include <PrimitiveConsole.h>
#include <Globals.h>
#include <Externs.h>

namespace Kernel
{
	void InitializeKernel(const BootInfo& bootInfo);
}

#endif