ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

LIBPROMPT = libprompt.a
COMM_OBJ = prompt.o

ifeq "$(PLATFORM)" "solaris"
  LDCMD=$(LD) -64 -G -Bdynamic -R/lib/64:/usr/ucblib/sparcv9 -o libapue_db.so.1 -L/lib/64 -L/usr/ucblib/sparcv9 -L$(ROOT)/lib -lapue db.o
  EXTRALD=-m64 -R.
else
  LDCMD=$(CC) -shared -Wl,-dylib -o libprompt.so.1 -L$(ROOT)/lib -lapue -lc prompt.o
endif
ifeq "$(PLATFORM)" "linux"
  EXTRALD=-Wl,-rpath=.
endif
ifeq "$(PLATFORM)" "freebsd"
  EXTRALD=-R.
endif
ifeq "$(PLATFORM)" "macos"
  EXTRALD=-R.
endif

all: libprompt.so.1 myShell $(LIBPROMPT)

$(LIBPROMPT):	$(COMM_OBJ) $(LIBAPUE)
		$(AR) rsv $(LIBPROMPT) $(COMM_OBJ)
		$(RANLIB) $(LIBPROMPT)

libprompt.so.1:	prompt.c $(LIBAPUE)
		$(CC) -fPIC $(CFLAGS) -c prompt.c
		$(LDCMD)
		ln -s libprompt.so.1 libprompt.so

myShell:	$(LIBAPUE)
		$(CC) $(CFLAGS) -c -I. myShell.c
		$(CC) $(EXTRALD) -o myShell myShell.o -L$(ROOT)/lib -L. -lprompt -lapue

clean:
	rm -f *.o a.out core temp.* $(LIBPROMPT) myShell libprompt.so.* *.dat *.idx libprompt.so

include $(ROOT)/Make.libapue.inc
