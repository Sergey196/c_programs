BINARY		:= tai_pci
OBJECTS	:= \
		main.o \
		sull.o \
		
obj-m += $(BINARY).o
ccflags-y := -std=gnu99

$(BINARY)-y := $(OBJECTS)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
