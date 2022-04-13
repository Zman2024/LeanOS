

all:
	$(MAKE) -C Bootloader all
	$(MAKE) -C Kernel all

lean: clean
clean:
	$(MAKE) -C Bootloader clean
	$(MAKE) -C Kernel clean