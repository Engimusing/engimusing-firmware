####################################################################
# Makefile                                                         #
####################################################################

.SUFFIXES:				# ignore builtin rules
.PHONY: all debug release clean

####################################################################
# Definitions                                                      #
####################################################################

DEVICE = EFM32ZG222F32
PROJECTNAME = efmusb

OBJ_DIR = build
EXE_DIR = exe
LST_DIR = lst

####################################################################
# Definitions of toolchain.                                        #
# You might need to do changes to match your system setup          #
####################################################################

TOOLDIR    = ~/.arduino15/packages/engimusing/tools/arm-none-eabi-gcc/4.8.3-2014q1

RM         := rm -rf
NULLDEVICE := /dev/null
SHELLNAMES := $(ComSpec)$(COMSPEC)


# Create directories and do a clean which is compatible with parallell make
$(shell mkdir $(OBJ_DIR)>$(NULLDEVICE) 2>&1)
$(shell mkdir $(EXE_DIR)>$(NULLDEVICE) 2>&1)
$(shell mkdir $(LST_DIR)>$(NULLDEVICE) 2>&1)
ifeq (clean,$(findstring clean, $(MAKECMDGOALS)))
  ifneq ($(filter $(MAKECMDGOALS),all debug release),)
    $(shell $(RM) $(OBJ_DIR)/*>$(NULLDEVICE) 2>&1)
    $(shell $(RM) $(EXE_DIR)/*>$(NULLDEVICE) 2>&1)
    $(shell $(RM) $(LST_DIR)/*>$(NULLDEVICE) 2>&1)
  endif
endif

CC      = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-gcc$(QUOTE)
CPP     = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-g++$(QUOTE)
LD      = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-ld$(QUOTE)
AR      = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-ar$(QUOTE)
OBJCOPY = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-objcopy$(QUOTE)
DUMP    = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-objdump$(QUOTE)
SIZE    = $(QUOTE)$(TOOLDIR)/bin/arm-none-eabi-size$(QUOTE)

####################################################################
# Flags                                                            #
####################################################################

# -MMD : Don't generate dependencies on system header files.
# -MP  : Add phony targets, useful when a h-file is removed from a project.
# -MF  : Specify a file to write the dependencies to.
DEPFLAGS = -MMD -MP -MF $(@:.o=.d)

#
# Add -Wa,-ahld=$(LST_DIR)/$(@F:.o=.lst) to CFLAGS to produce assembly list files
#
override CFLAGS +=  -D$(DEVICE) -mcpu=cortex-m0 -mthumb -c -g -Os -w -std=gnu11 \
-ffunction-sections -fdata-sections \
-nostdlib --param max-inline-insns-single=500 -fno-rtti -fno-exceptions -MMD \
-fno-rtti -fno-exceptions

override CPPFLAGS +=  -D$(DEVICE) -mcpu=cortex-m0 -mthumb -c -g -Os -w -std=gnu++11 \
-ffunction-sections -fdata-sections -fno-threadsafe-statics \
-nostdlib --param max-inline-insns-single=500 -MMD \
-fno-rtti -fno-exceptions

override ASMFLAGS += -x assembler-with-cpp -D$(DEVICE) -Wall -Wextra -mcpu=cortex-m0 -mthumb

#
# NOTE: The -Wl,--gc-sections flag may interfere with debugging using gdb.
#
override LDFLAGS += -Xlinker -Map=$(LST_DIR)/$(PROJECTNAME).map \
-mcpu=cortex-m0 -mthumb \
-T../cores/cortex-m0plus/device/efm32zg.ld \
-Wl,--gc-sections --specs=nano.specs --specs=nosys.specs 

LIBS = -Wl,--start-group -lm ../cores/cortex-m0plus/core.a -Wl,--end-group \
-Wl,--start-group -lgcc -lc -Wl,--end-group \

INCLUDEPATHS += \
-I.. \
-I../cores/cortex-m0plus/ \
-I../cores/cortex-m0plus/device/inc/ \
-I../cores/cortex-m0plus/cmsis/ \
-I../cores/cortex-m0plus/em_lib/inc/ \
-I../cores/cortex-m0plus/efm_lib/inc/ \
-I../variants/EFMUSB/ \
-I.

####################################################################
# Files                                                            #
####################################################################

C_SRC += 

CPP_SRC += \
../variants/EFMUSB/variant.cpp \
$(wildcard *.cpp)

s_SRC += 


S_SRC += 

####################################################################
# Rules                                                            #
####################################################################

C_FILES = $(notdir $(C_SRC) )
CPP_FILES = $(notdir $(CPP_SRC) )
S_FILES = $(notdir $(S_SRC) $(s_SRC) )

#make list of source paths, sort also removes duplicates
C_PATHS = $(sort $(dir $(C_SRC) ) )
CPP_PATHS = $(sort $(dir $(CPP_SRC) ) )
S_PATHS = $(sort $(dir $(S_SRC) $(s_SRC) ) )

C_OBJS = $(addprefix $(OBJ_DIR)/, $(C_FILES:.c=.o))
CPP_OBJS = $(addprefix $(OBJ_DIR)/, $(CPP_FILES:.cpp=.o))
S_OBJS = $(if $(S_SRC), $(addprefix $(OBJ_DIR)/, $(S_FILES:.S=.o)))
s_OBJS = $(if $(s_SRC), $(addprefix $(OBJ_DIR)/, $(S_FILES:.s=.o)))
C_DEPS = $(addprefix $(OBJ_DIR)/, $(C_FILES:.c=.d))
OBJS = $(C_OBJS) $(CPP_OBJS) $(S_OBJS) $(s_OBJS)

vpath %.c $(C_PATHS)
vpath %.cpp $(CPP_PATHS)
vpath %.s $(S_PATHS)
vpath %.S $(S_PATHS)

# Default build is debug build
all:      release corelib

corelib:
	make -C ../cores/cortex-m0plus/

release:  $(EXE_DIR)/$(PROJECTNAME).bin


# Create objects from C SRC files
$(OBJ_DIR)/%.o: %.c
	@echo "Building file: $<"
	$(CC) $(CFLAGS) $(INCLUDEPATHS) -c -o $@ $<

# Create objects from cpp files
$(OBJ_DIR)/%.o: %.cpp
	@echo "Building file: $<"
	$(CPP) $(CPPFLAGS) $(INCLUDEPATHS) -c -o $@ $<

# Assemble .s/.S files
$(OBJ_DIR)/%.o: %.s
	@echo "Assembling $<"
	$(CC) $(ASMFLAGS) $(INCLUDEPATHS) -c -o $@ $<

$(OBJ_DIR)/%.o: %.S
	@echo "Assembling $<"
	$(CC) $(ASMFLAGS) $(INCLUDEPATHS) -c -o $@ $<

# Link
$(EXE_DIR)/$(PROJECTNAME).out: $(OBJS) corelib
	@echo "Linking target: $@"
	$(CC) $(LDFLAGS) $(OBJS) $(LIBS) -o $(EXE_DIR)/$(PROJECTNAME).out

# Create binary file
$(EXE_DIR)/$(PROJECTNAME).bin: $(EXE_DIR)/$(PROJECTNAME).out
	@echo "Creating binary file"
	$(OBJCOPY) -O binary $(EXE_DIR)/$(PROJECTNAME).out $(EXE_DIR)/$(PROJECTNAME).bin
# Uncomment next line to produce assembly listing of entire program
	$(DUMP) -h -S -C $(EXE_DIR)/$(PROJECTNAME).out>$(LST_DIR)/$(PROJECTNAME)out.lst
# Print the size
	$(SIZE) $(EXE_DIR)/$(PROJECTNAME).out

prog:
	~/Documents/Silabs/eACommander/start-eACommander.sh --verify --address 0x2000 --flash exe/efmusb.bin --reset
clean:
ifeq ($(filter $(MAKECMDGOALS),all debug release),)
	$(RM) $(OBJ_DIR) $(LST_DIR) $(EXE_DIR)
endif

# include auto-generated dependency files (explicit rules)
ifneq (clean,$(findstring clean, $(MAKECMDGOALS)))
-include $(C_DEPS)
endif

