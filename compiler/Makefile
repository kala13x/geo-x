CXXFLAGS = -g -O2 -Wall -I../utils
LIB = ../utils/utils.a
OBJ = gx.o parser.o
INSTALL = ../bin

all: $(OBJ)
	$(CXX) $(CXXFLAGS) -o gx $(OBJ) $(LIB)
	@test -d $(INSTALL) || mkdir $(INSTALL)
	@install -m 0755 gx $(INSTALL)/

gx.o: parser.h mdefs.h stdinc.h
parser.o: parser.h stdinc.h

.PHONY: clean

clean:
	$(RM) gx $(OBJ)
