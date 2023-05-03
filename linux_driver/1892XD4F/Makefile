BINARY		:= test_driver
OBJECTS	:= \
		main.o \
		sull.o \
		
obj-m += $(BINARY).o

$(BINARY)-y := $(OBJECTS)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
