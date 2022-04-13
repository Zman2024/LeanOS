OSNAME = LeanOS

GNUEFI = ../Bootloader
OVMFDIR = ../OVMFbin
LDS = kernel.ld
GC = gcc
LD = ld
ASMC = nasm
QEMU = qemu-system-x86_64

SRCDIR := src
INCLUDEDIR := src/include
OBJDIR := obj
BUILDDIR = bin

QEMUFLAGS = -device qemu-xhci -machine q35 -rtc base=localtime
QEMUFLAGS += -drive file=$(BUILDDIR)/$(OSNAME).img
QEMUFLAGS += -m 8G
QEMUFLAGS += -cpu qemu64,+sse2,+sse3,+sse4.1,+sse4.2,+rdrand,+xsave
QEMUFLAGS += -smp cores=4
QEMUFLAGS += -drive if=pflash,format=raw,unit=0,file=$(OVMFDIR)/OVMF_CODE-pure-efi.fd,readonly=on
QEMUFLAGS += -drive if=pflash,format=raw,unit=1,file=$(OVMFDIR)/OVMF_VARS-pure-efi.fd
QEMUFLAGS += -net none -vga virtio -smp 4 -soundhw pcspk 

CXXFLAGS = -g -ffreestanding -fshort-wchar -pipe -mno-red-zone -O0 -fno-exceptions -fno-rtti -masm=intel -fpermissive -w -I$(INCLUDEDIR) -c 
ASMFLAGS = -g -f elf64 
LDFLAGS = -T $(LDS) -static -Bsymbolic -nostdlib

BOOTEFI := $(GNUEFI)/x86_64/bootloader/main.efi

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRC = $(call rwildcard,$(SRCDIR),*.cpp)
# CSRC = $(call rwildcard,$(SRCDIR),*.c)
ASMSRC = $(call rwildcard,$(SRCDIR),*.asm)

OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.cppo, $(SRC))
OBJS += $(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%.asmo, $(ASMSRC))
DIRS = $(wildcard $(SRCDIR)/*)

all: setup kernel buildimg

kernel: $(OBJS) link
$(OBJDIR)/%.cppo: $(SRCDIR)/%.cpp
	@ echo ==================== Compiling $^ ====================
	@ mkdir -p $(@D)
	$(GC) $(CXXFLAGS) $^ -o $@

$(OBJDIR)/%.asmo: $(SRCDIR)/%.asm
	@ echo ==================== Compiling $^ ====================
	@ mkdir -p $(@D)
	$(ASMC) $(ASMFLAGS) $^ -o $@

	@ echo ==================== Done ====================

link:
	@ echo ==================== Linking ====================
	$(LD) $(LDFLAGS) -o $(BUILDDIR)/kernel.elf $(OBJS)
	@ echo ==================== Done ====================

clean:
	@ echo ==================== Cleaning Kernel ====================
	@ rm -rf $(OBJDIR)/*.*
	@ rm -rf $(BUILDDIR)/*.*
	@ rm -rf $(BUILDDIR)/dsk/*.*
	@ rm -rf $(BUILDDIR)/dsk/efi/*.*
	@ rm -rf $(BUILDDIR)/dsk/efi/boot/*.*
	@ echo ==================== Done ====================


setup:
	@ echo ==================== Setting up ====================
	@ mkdir -p $(BUILDDIR)
	@ mkdir -p $(BUILDDIR)/dsk
	@ mkdir -p $(BUILDDIR)/dsk/efi
	@ mkdir -p $(BUILDDIR)/dsk/efi/boot
	@ mkdir -p $(SRCDIR)
	@ mkdir -p $(OBJDIR)
	@ echo ==================== Done ====================

buildimg:
	@ echo ==================== Building Image ====================
	dd if=/dev/zero of=$(BUILDDIR)/$(OSNAME).img bs=512 count=93750
	mformat -i $(BUILDDIR)/$(OSNAME).img -f 1440 ::
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI
	mmd -i $(BUILDDIR)/$(OSNAME).img ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BOOTEFI) ::/EFI/BOOT
	mcopy -i $(BUILDDIR)/$(OSNAME).img startup.nsh ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img $(BUILDDIR)/kernel.elf ::
	mcopy -i $(BUILDDIR)/$(OSNAME).img zap-light16.psf ::

	cp $(BOOTEFI) $(BUILDDIR)/dsk/efi/boot
	cp $(BOOTEFI) $(BUILDDIR)/dsk/efi/boot/bootx64.efi
	cp $(BUILDDIR)/kernel.elf $(BUILDDIR)/dsk
	cp zap-light16.psf $(BUILDDIR)/dsk

	@ echo ==================== Done ====================

run:
	@ $(QEMU) $(QEMUFLAGS)
