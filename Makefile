ROOT=..
PLATFORM=$(shell $(ROOT)/systype.sh)
include $(ROOT)/Make.defines.$(PLATFORM)

EXE=myShell
OBJ=myShell.o prompt.o splitCmdStr.o export.o innerCmd.o redirect.o

$(EXE):$(OBJ)
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)
 
clean:
	rm $(EXE) $(OBJ) -f
