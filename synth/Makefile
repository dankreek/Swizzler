# Swizzler Makefile by Justin May derived from:
# Arduino 0015 Makefile
# Arduino adaptation by mellis, eighthave, oli.keller
#
# This makefile allows you to build full C++ programs from the command line
# without the Arduino environment (or Java). It
#
# Detailed instructions for using the makefile:
#
#  1. Copy this file into the folder with your sketch. There should be a
#     file with the same name as the folder and with the extension .cpp
#     (e.g. foo.cpp in the foo/ folder). It should also have a main() function
#     in it.
#
#  2. Modify the line containg "INSTALL_DIR" to point to the directory that
#     contains the Arduino installation (for example, under Mac OS X, this
#     might be /Applications/arduino-0012).
#
#  3. Modify the line containing "PORT" to refer to the filename
#     representing the USB or serial connection to your Arduino board
#     (e.g. PORT = /dev/tty.USB0).  If the exact name of this file
#     changes, you can use * as a wildcard (e.g. PORT = /dev/tty.usb*).
#
#  4. Set the line containing "MCU" to match your board's processor. 
#     Older one's are atmega8 based, newer ones like Arduino Mini, Bluetooth
#     or Diecimila have the atmega168.  If you're using a LilyPad Arduino,
#     change F_CPU to 8000000.
#
#  5. At the command line, change to the directory containing your
#     program's file and the makefile.
#
#  6. Type "make" and press enter to compile/verify your program.
#
#  7. Type "make upload", reset your Arduino board, and press enter to
#     upload your program to the Arduino board.
#
# $Id$

TARGET = main
PORT = usb
#UPLOAD_RATE = 19200
AVRDUDE_PROGRAMMER = dragon_isp
BITCLOCK_DELAY = 2
MCU = atmega328p
F_CPU = 16000000
ARDUINO = ./arduino

############################################################################
# Below here nothing should be changed...

BIN = ./bin
SRC = twi.c  
#$(ARDUINO)/pins_arduino.c $(ARDUINO)/wiring.c \
#$(ARDUINO)/wiring_analog.c $(ARDUINO)/wiring_digital.c \
#$(ARDUINO)/wiring_pulse.c \
#$(ARDUINO)/wiring_shift.c $(ARDUINO)/WInterrupts.c $(wildcard *.c) $(ARDUINO)/twi.c
CXXSRC = $(wildcard *.cpp)
FORMAT = ihex

# Name of this Makefile (used for "make depend").
MAKEFILE = Makefile

# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
DEBUG = stabs

OPT = s

# Place -D or -U options here
CDEFS = -DF_CPU=$(F_CPU)
CXXDEFS = -DF_CPU=$(F_CPU)

# Place -I options here
CINCS = #-I$(ARDUINO)
CXXINCS = #-I$(ARDUINO)

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CSTANDARD = -std=gnu99
CDEBUG = -g$(DEBUG)
CWARN = -Wall -Wstrict-prototypes
CTUNING = -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
#CEXTRA = -Wa,-adhlns=$(<:.c=.lst)

CFLAGS = $(CDEBUG) $(CDEFS) $(CINCS) -O$(OPT) $(CWARN) $(CSTANDARD) $(CEXTRA)
CXXFLAGS = $(CDEFS) $(CINCS) -O$(OPT)
#ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs 
LDFLAGS = -lm


# Programming support using avrdude. Settings and variables.
AVRDUDE_PORT = $(PORT)
AVRDUDE_WRITE_FLASH = -U flash:w:$(BIN)/$(TARGET).hex
AVRDUDE_WRITE_EEPROM = -U eeprom:w:$(BIN)/$(TARGET).eep:i
AVRDUDE_VERIFY_EEPROM = -U eeprom:v:$(BIN)/$(TARGET).eep:i
AVRDUDE_FLAGS = -V -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER) -B $(BITCLOCK_DELAY)
#-b $(UPLOAD_RATE)

# Program settings
CC = avr-gcc
CXX = avr-g++
OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
AR  = avr-ar
SIZE = avr-size
NM = avr-nm
#AVRDUDE = $(AVR_TOOLS_PATH)/avrdude
AVRDUDE = avrdude
REMOVE = rm -rf
MV = mv -f

# Define all object files.
OBJ = $(SRC:.c=.o) $(CXXSRC:.cpp=.o) $(ASRC:.S=.o) 

# Define all listing files.
LST = $(ASRC:.S=.lst) $(CXXSRC:.cpp=.lst) $(SRC:.c=.lst)

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS = -mmcu=$(MCU) -I. $(CFLAGS)
ALL_CXXFLAGS = -mmcu=$(MCU) -I. $(CXXFLAGS)
ALL_ASFLAGS = -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)


# Default target.
all: bin_dir build sizeafter

build: elf hex eep

bin_dir:
	# Make the bin dir if it doesn't exist yet 
	test -d $(BIN) || mkdir $(BIN)

elf: $(BIN)/$(TARGET).elf
hex: $(BIN)/$(TARGET).hex
eep: $(BIN)/$(TARGET).eep
lss: $(BIN)/$(TARGET).lss 
sym: $(BIN)/$(TARGET).sym

# Program the device.
upload: upload_flash upload_eeprom
  
upload_flash: $(BIN)/$(TARGET).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH)
	
upload_eeprom: $(BIN)/$(TARGET).eep
	sleep 2
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_EEPROM)
	
verify_eeprom: $(BIN)/$(TARGET).eep	
	$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_VERIFY_EEPROM)

	# Display size of file.
HEXSIZE = $(SIZE) --target=$(FORMAT) $(BIN)/$(TARGET).hex
ELFSIZE = $(SIZE)  $(BIN)/$(TARGET).elf
sizebefore:
	@if [ -f $(BIN)/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_BEFORE); $(HEXSIZE); echo; fi

sizeafter:
	@if [ -f $(BIN)/$(TARGET).elf ]; then echo; echo $(MSG_SIZE_AFTER); $(HEXSIZE); echo; fi


# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000 


coff: $(BIN)/$(TARGET).elf
	$(COFFCONVERT) -O coff-avr $(BIN)/$(TARGET).elf $(TARGET).cof


extcoff: $(TARGET).elf
	$(COFFCONVERT) -O coff-ext-avr $(BIN)/$(TARGET).elf $(TARGET).cof


.SUFFIXES: .elf .hex .eep .lss .sym

.elf.hex:
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

.elf.eep:
	-$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--change-section-lma .eeprom=0 -O $(FORMAT) $< $@

# Create extended listing file from ELF output file.
.elf.lss:
	$(OBJDUMP) -h -S $< > $@

# Create a symbol table from ELF output file.
.elf.sym:
	$(NM) -n $< > $@

# Link: create ELF output file from library.
$(BIN)/$(TARGET).elf: $(TARGET).cpp $(BIN)/core.a 
	$(CC) $(ALL_CXXFLAGS) -o $@ -L. $(BIN)/core.a $(LDFLAGS)

$(BIN)/core.a: $(OBJ)
	@for i in $(OBJ); do echo $(AR) rcs $(BIN)/core.a $$i; $(AR) rcs $(BIN)/core.a $$i; done



# Compile: create object files from C++ source files.
.cpp.o:
	$(CXX) -c $(ALL_CXXFLAGS) $< -o $@ 

# Compile: create object files from C source files.
.c.o:
	$(CC) -c $(ALL_CFLAGS) $< -o $@ 


# Compile: create assembler files from C source files.
.c.s:
	$(CC) -S $(ALL_CFLAGS) $< -o $@


# Assemble: create object files from assembler source files.
.S.o:
	$(CC) -c $(ALL_ASFLAGS) $< -o $@


# Automatic dependencies
%.d: %.c
	$(CC) -M $(ALL_CFLAGS) $< | sed "s;$(notdir $*).o:;$*.o $*.d:;" > $@

%.d: %.cpp
	$(CXX) -M $(ALL_CXXFLAGS) $< | sed "s;$(notdir $*).o:;$*.o $*.d:;" > $@


# Target: clean project.
clean:
	$(REMOVE) $(BIN)/$(TARGET).hex $(BIN)/$(TARGET).eep $(BIN)/$(TARGET).cof $(BIN)/$(TARGET).elf \
	$(BIN)/$(TARGET).map i$(BIN)/$(TARGET).sym $(BIN)/$(TARGET).lss $(BIN)/core.a \
	$(OBJ) $(LST) $(SRC:.c=.s) $(SRC:.c=.d) $(CXXSRC:.cpp=.s) $(CXXSRC:.cpp=.d) ./html

.PHONY:	all build elf hex eep lss sym program coff extcoff clean bin_dir sizebefore sizeafter
