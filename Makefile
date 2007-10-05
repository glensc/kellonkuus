#CC := /usr/ppc/arm-wince-mingw32ce/bin/gcc
CC := i386-mingw32-gcc
LIBS := -lwinmm
CFLAGS := -Wall
EXE := .exe

all: kellonkuus$(EXE)

kellonkuus$(EXE): tellclock.o
	$(CC) $(LIBS) $(LDFLAGS) $< -o $@

clean:
	rm -f kellonkuus$(EXE) tellclock.o