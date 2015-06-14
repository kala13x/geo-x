OBJ = 
INCLUDE = /usr/local/include

all:

install:
	@test -d $(INCLUDE) || mkdir $(INCLUDE)
	@install -m 0755 standartebi.h $(INCLUDE)/


.PHONY: clean

clean:
	$(RM) $(OBJ)
