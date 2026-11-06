
TARGET := VirusMetamorphose
BUILD := build
SOURCES := source

CC := arm-none-eabi-gcc

ARCH := -march=armv5te -mtune=arm946e-s -mthumb-interwork
CFLAGS := -O2 -Wall $(ARCH) -DARM9

INCLUDES := -I$(DEVKITPRO)/libnds/include
LIBS := -L$(DEVKITPRO)/libnds/lib -lnds9

all:
	mkdir -p $(BUILD)
	$(CC) $(CFLAGS) $(INCLUDES) \
		-specs=ds_arm9.specs \
		$(SOURCES)/main.c \
		$(LIBS) \
		-o $(BUILD)/VirusMetamorphose.elf
	ndstool -c $(TARGET).nds \
		-9 $(BUILD)/VirusMetamorphose.elf

clean:
	rm -rf $(BUILD) $(TARGET).nds
