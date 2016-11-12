OBJFILES = ./gr_sketch.o ./gr_common/intvect.o ./gr_common/lowlevel.o 
LIBFILES = ./gr_common/lib/libc.a ./gr_common/lib/libg.a ./gr_common/lib/libgcc.a ./gr_common/lib/libm.a ./gr_common/lib/librxduino.a ./gr_common/lib/libsim.a ./gr_common/lib/libstdc++.a ./gr_common/lib/libsupc++.a ./gr_common/lib/libtkdnhal.a 
CCINC = -I./gr_build -I./gr_common -I./gr_common/include -I./gr_common/include/rxduino -I./gr_common/include/tkdnhal -I./gr_common/lib 
HEADERFILES = ./gr_common/intvect.h ./gr_common/intvect63n.h ./gr_common/include/rxduino/analogio.h ./gr_common/include/rxduino/binary.h ./gr_common/include/rxduino/delay.h ./gr_common/include/rxduino/digitalio.h ./gr_common/include/rxduino/interrupt.h ./gr_common/include/rxduino/progmem.h ./gr_common/include/rxduino/random.h ./gr_common/include/rxduino/rtc.h ./gr_common/include/rxduino/rxduino.h ./gr_common/include/rxduino/rxstring.h ./gr_common/include/rxduino/serial.h ./gr_common/include/rxduino/shiftout.h ./gr_common/include/rxduino/tone.h ./gr_common/include/rxduino/wiring.h ./gr_common/include/tkdnhal/boarddef.h ./gr_common/include/tkdnhal/brd_grsakura.h ./gr_common/include/tkdnhal/brd_grume.h ./gr_common/include/tkdnhal/hwsetup.h ./gr_common/include/tkdnhal/iodefine_gcc62n.h ./gr_common/include/tkdnhal/iodefine_gcc63n.h ./gr_common/include/tkdnhal/misc.h ./gr_common/include/tkdnhal/tkdn_adc.h ./gr_common/include/tkdnhal/tkdn_dac.h ./gr_common/include/tkdnhal/tkdn_dflash.h ./gr_common/include/tkdnhal/tkdn_ether.h ./gr_common/include/tkdnhal/tkdn_gpio.h ./gr_common/include/tkdnhal/tkdn_hal.h ./gr_common/include/tkdnhal/tkdn_i2c.h ./gr_common/include/tkdnhal/tkdn_interrupt.h ./gr_common/include/tkdnhal/tkdn_pwm.h ./gr_common/include/tkdnhal/tkdn_rtc.h ./gr_common/include/tkdnhal/tkdn_sci.h ./gr_common/include/tkdnhal/tkdn_servo.h ./gr_common/include/tkdnhal/tkdn_spi.h ./gr_common/include/tkdnhal/tkdn_timer.h ./gr_common/include/tkdnhal/tkdn_tone.h ./gr_common/include/tkdnhal/tkdn_usb.h ./gr_common/include/tkdnhal/tkdn_version.h ./gr_common/include/tkdnhal/tkusbhost.h 
TARGET = sketch
GNU_PATH := 
CFLAGS :=-Wall -g -O2 -Wl,--no-flag-mismatch-warnings -fsigned-char
AFLAGS :=-Wall -g -O2 -Wl,--no-flag-mismatch-warnings -fsigned-char
SFLAGS :=--gdwarf2
CC  = rx-elf-gcc
CPP = rx-elf-gcc
AS  = rx-elf-as 
LNK = rx-elf-ld
CNVS = rx-elf-objcopy --srec-forceS3 --srec-len 32 -O srec
CNVB = rx-elf-objcopy -O binary
DMP = rx-elf-objdump
OBJS = ./gr_common/gstart.o $(OBJFILES) $(LIBFILES) 
LFLAGS = -Map ./gr_build/$(TARGET).map -L./gr_common/lib/ -lrxduino -lstdc++ -lsupc++ -lc -lsim -lgcc -lm -ltkdnhal -nostartfiles --no-flag-mismatch-warnings
MAKEFILE = makefile
ROMSCRIPT=./gr_common/gr_sakura.gsi

make = make --no-print-directory 

all:	rom

rom:	$(OBJS) $(MAKEFILE) $(ROMSCRIPT)
	$(LNK) $(OBJS) $(LFLAGS) -T $(ROMSCRIPT) -o ./gr_build/$(TARGET).x
	$(CNVB) ./gr_build/$(TARGET).x  $(TARGET).bin
	$(CNVS) ./gr_build/$(TARGET).x  ./gr_build/$(TARGET).mot
	rm -f *.o

%.o: %.s
	$(AS) $(SFLAGS) $(CCINC) $< -o $@

%.o: %.asm
	$(CC) $(AFLAGS) $(CCINC) -c -x assembler-with-cpp $< -o $@

%.o: %.c $(HEADERFILES)
	$(CC) $(CFLAGS) $(CCINC) -c -x c $< -o $@

%.o: %.cpp $(HEADERFILES)
	$(CPP) $(CFLAGS) $(CCINC) -c -x c++ $< -o $@
