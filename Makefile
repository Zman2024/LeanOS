

all:
	$(MAKE) -C Bootloader all
	$(MAKE) -C Kernel all

clean:
	$(MAKE) -C Bootloader clean
	$(MAKE) -C Kernel clean