GCC_BIN = ~/gcc-arm-none-eabi-4_7-2012q4/bin/
PROJECT = Quadcopter
OBJECTS_2 = $(wildcard src/*.cpp src/*.c)
OBJECTS_1 = $(OBJECTS_2:.cpp=.o)
OBJECTS = $(OBJECTS_1:.c=.o)
MBED = ./mbed2
SYS_OBJECTS = $(MBED)/LPC1768/GCC_CS/sys.o $(MBED)/LPC1768/GCC_CS/cmsis_nvic.o $(MBED)/LPC1768/GCC_CS/system_LPC17xx.o $(MBED)/LPC1768/GCC_CS/core_cm3.o $(MBED)/LPC1768/GCC_CS/startup_LPC17xx.o
INCLUDE_PATHS = -I. -I$(MBED) -I$(MBED)/LPC1768 -I$(MBED)/LPC1768/GCC_CS -I./include
LIBRARY_PATHS = -L$(MBED)/LPC1768/GCC_CS
LIBRARIES = -lmbed -lcapi
LINKER_SCRIPT = $(MBED)/LPC1768/GCC_CS/LPC1768.ld

###############################################################################
CC = $(GCC_BIN)arm-none-eabi-gcc
CPP = $(GCC_BIN)arm-none-eabi-g++
CC_FLAGS = -c -Os -fno-common -fmessage-length=0 -Wall -fno-exceptions -mcpu=cortex-m3 -mthumb -ffunction-sections -fdata-sections
ONLY_C_FLAGS = -std=gnu99
ONLY_CPP_FLAGS = -std=gnu++11
CC_SYMBOLS = -DTARGET_LPC1768 -DTARGET_M3 -DTARGET_NXP -DTARGET_LPC176X -DTOOLCHAIN_GCC_CS -DTOOLCHAIN_GCC -D__CORTEX_M3 -DARM_MATH_CM3


AS = $(GCC_BIN)arm-none-eabi-as

LD = $(GCC_BIN)arm-none-eabi-gcc
LD_FLAGS = -mcpu=cortex-m3 -mthumb -Wl,--gc-sections
LD_SYS_LIBS = -lstdc++ -lsupc++ -lm -lc -lgcc

OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy

Debug: all

Release: all

all: clean $(PROJECT).bin
	bash -c "cp -v $(PROJECT).bin /media/MBED 2>&1"

clean:
	rm -f $(PROJECT).bin $(PROJECT).elf $(OBJECTS)

.s.o:
	$(AS)  $(CC_FLAGS) $(CC_SYMBOLS) -o $@ $<

.c.o:
	$(CC)  $(CC_FLAGS) $(CC_SYMBOLS) $(ONLY_C_FLAGS)   $(INCLUDE_PATHS) -o $@ $<

.cpp.o:
	$(CPP) $(CC_FLAGS) $(CC_SYMBOLS) $(ONLY_CPP_FLAGS) $(INCLUDE_PATHS) -o $@ $<


$(PROJECT).elf: $(OBJECTS) $(SYS_OBJECTS)
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $^ $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)

$(PROJECT).bin: $(PROJECT).elf
	$(OBJCOPY) -O binary $< $@
