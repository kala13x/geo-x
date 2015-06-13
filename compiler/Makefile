CXXFLAGS = -g -O2 -Wall -I../utils
LIB = ../utils/utils.a
OBJ = gxx.o parser.o info.o

BUILD = ../bin
INSTALL = /usr/local/bin
INCLUDE = /usr/local/include

all: $(OBJ)
	$(CXX) $(CXXFLAGS) -o gxx $(OBJ) $(LIB)
	@test -d $(BUILD) || mkdir $(BUILD)
	@install -m 0755 gxx $(BUILD)/

install:
	@test -d $(INSTALL) || mkdir $(INSTALL)
	@test -d $(INCLUDE) || mkdir $(INCLUDE)
	@install -m 0755 gxx $(INSTALL)/
	@install -m 0755 standartebi.h $(INCLUDE)/

gxx.o: parser.h info.h mdefs.h stdinc.h
parser.o: parser.h mdefs.h stdinc.h 
info.o: info.h stdinc.h

.PHONY: clean

clean:
	$(RM) gxx $(OBJ)
