include $(ECOS_PRODUCT_DIR)/config.mk

BL1.bin: start.o mem_setup.o mmc_relocate.o
	$(LD) -TBL1.lds -o BL1.elf $^
	$(OBJCOPY) -O binary BL1.elf BL1.bin
	$(OBJDUMP) -D BL1.elf > BL1_elf.dis
	gcc mkv210_image.c -o mkmini210
	./mkmini210 BL1.bin bootloader.bin
	
%.o : %.S
	echo "$(CC)"
	$(CC) -o $@ $< -c 

%.o : %.c
	$(CC) -o $@ $< -c 

clean:
	rm *.o *.elf *.bin *.dis mkmini210 -f
