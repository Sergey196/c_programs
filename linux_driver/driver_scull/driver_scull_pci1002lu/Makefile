BINARY		:= pci1002lu
OBJECTS	:= \
		main.o \
		scull.o \
		device.o \
		
obj-m += $(BINARY).o
ccflags-y := -std=gnu99

$(BINARY)-y := $(OBJECTS)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
