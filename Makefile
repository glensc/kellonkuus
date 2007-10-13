CC := /usr/ppc/arm-wince-mingw32ce/bin/gcc
#CC := i386-mingw32-gcc
#LIBS := -lwinmm
CFLAGS := -Wall
EXE := .exe
PACKAGE := kellonkuus
VERSION := 0.2

all: $(PACKAGE)$(EXE)

$(PACKAGE)$(EXE): $(PACKAGE).o
	$(CC) $(LIBS) $(LDFLAGS) $< -o $@

clean:
	rm -f $(PACKAGE)$(EXE) $(PACKAGE).o


dist:
	rm -rf $(PACKAGE)-$(VERSION)
	mkdir $(PACKAGE)-$(VERSION)
	cp -a Makefile $(PACKAGE).c $(PACKAGE)-$(VERSION)
	tar cjf $(PACKAGE)-$(VERSION).tar.bz2 $(PACKAGE)-$(VERSION)
	rm -rf $(PACKAGE)-$(VERSION)
