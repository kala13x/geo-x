CFLAGS = -g -O2 -Wall -I../utils -Wno-unused-result -Wno-unused-but-set-variable
LIB = ../utils/utils.a
OBJ = gxx.o parser.o info.o

BUILD = ../bin
INSTALL = /usr/local/bin

all: $(OBJ)
	$(CC) $(CFLAGS) -o gxx $(OBJ) $(LIB)
	@test -d $(BUILD) || mkdir $(BUILD)
	@install -m 0755 gxx $(BUILD)/

install:
	@test -d $(INSTALL) || mkdir $(INSTALL)
	@install -m 0755 gxx $(INSTALL)/

gxx.o: parser.h info.h mdefs.h stdinc.h
parser.o: parser.h mdefs.h stdinc.h 
info.o: info.h stdinc.h

.PHONY: clean

clean:
	$(RM) gxx $(OBJ)
