#include <Kernel.h>

namespace Kernel
{
    void InitializeKernel(BootInfo& bootInfo)
    {
        uint32* ptr = (uint32*)bootInfo.Framebuffer->BaseAddress;
        for (nint x = 0; x < 1000; x++)
        {
            ptr[x] = 0xCCCCCC;
        }
        
    }
}
