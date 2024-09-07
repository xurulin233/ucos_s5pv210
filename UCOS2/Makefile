include $(ECOS_PRODUCT_DIR)/config.mk
EXECUTABLE   := UCOS210.elf

INCLUDEDIR 	:=  -I./include -I./S5PV210/include -I./UCOS -I./ucosspv210


LINKERSCRIPT := map.lds

INIT_DRAM = S5PV210/source/start.S

CFLAGS 		:= -Wall -O2 -fno-builtin
CPPFLAGS   	:= -nostdinc $(INCLUDEDIR)


#export 	CC AR LD OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS

SOURCE := \
		ucosspv210/os_cpu_a.S \
		ucosspv210/os_cpu_c.c \
		S5PV210/source/main.c \
		S5PV210/source/led.c \
		S5PV210/source/uart.c \
		S5PV210/source/int.c \
		S5PV210/source/ucos_ii.c 


objs := \
	$(patsubst %.c, %.o, $(filter %.c, $(SOURCE))) \
	$(patsubst %.cpp, %.o, $(filter %.cpp, $(SOURCE))) \
	$(patsubst %.S, %.o, $(filter %.S, $(SOURCE)))

all:$(EXECUTABLE)
	${OBJCOPY} -O binary -S $(EXECUTABLE) $(patsubst %.elf,%.bin,$(EXECUTABLE))
	${OBJDUMP} -D UCOS210.elf >$(patsubst %.elf,%.dis,$(EXECUTABLE))

$(EXECUTABLE):  $(INIT_DRAM:.S=.o) $(objs)
	${LD} -T$(LINKERSCRIPT) -o $(EXECUTABLE) $^
	
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.bin *.elf *.dis  *~  $(objs) $(INIT_DRAM:.S=.o) 
