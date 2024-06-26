ROOT=.

# Common make definitions, customized for each platform

# Definitions required in all program directories to compile and link
# C programs using gcc.

CC=gcc
COMPILE.c=$(CC) $(CFLAGS) $(CPPFLAGS) -c
LINK.c=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LDFLAGS=
LDDIR=-L$(ROOT)/lib
LDLIBS=$(LDDIR) -lapue $(EXTRALIBS)
CFLAGS=-ansi -I$(ROOT)/include -Wall -DLINUX -D_GNU_SOURCE $(EXTRA)
RANLIB=echo
AR=ar
AWK=awk
LIBAPUE=$(ROOT)/lib/libapue.a

# Common temp files to delete from each directory.
TEMPFILES=core core.* *.o temp.* *.out

EXE=myShell
OBJ=myShell.o prompt.o splitCmdStr.o export.o innerCmd.o redirect.o

$(EXE):$(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)
 
clean:
	rm $(EXE) $(OBJ) -f
