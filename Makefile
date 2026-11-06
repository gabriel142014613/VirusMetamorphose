
.SUFFIXES:

ifeq ($(strip $(DEVKITPRO)),)
$(error DEVKITPRO is not set)
endif

ifeq ($(strip $(DEVKITARM)),)
$(error DEVKITARM is not set)
endif

TARGET := VirusMetamorphose
BUILD := build
SOURCES := source
DATA :=
INCLUDES :=

ARCH := -march=armv5te -mtune=arm946e-s
CFLAGS := -g -Wall -O2 $(ARCH) -DARM9
CXXFLAGS := $(CFLAGS) -fno-rtti -fno-exceptions
ASFLAGS := -g $(ARCH)

LIBS := -lnds9
LIBDIRS := $(LIBNDS)

include $(DEVKITPRO)/libnds/default_ds_rules
