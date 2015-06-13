CXXFLAGS = -g -O2 -Wall -I../utils
LIB = ../utils/utils.a
OBJ = gxx.o parser.o
INSTALL = ../bin

all: $(OBJ)
	$(CXX) $(CXXFLAGS) -o gxx $(OBJ) $(LIB)
	@test -d $(INSTALL) || mkdir $(INSTALL)
	@install -m 0755 gxx $(INSTALL)/

gxx.o: parser.h mdefs.h stdinc.h
parser.o: parser.h mdefs.h stdinc.h 

.PHONY: clean

clean:
	$(RM) gxx $(OBJ)
