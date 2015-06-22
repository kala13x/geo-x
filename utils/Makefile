LIB = -lnsl
CFLAGS = -g -O2 -Wall

OBJS = systime.o color.o errex.o \
	files.o strops.o slog.o

.c.o:
	$(CC) $(CFLAGS) -c $< $(LIB)

utils.a: $(OBJS)
	$(AR) rcs utils.a $(OBJS)
	@echo [-] Syncing static library
	sync

errex.o: errex.h slog.h color.h stdinc.h
systime.o: systime.h stdinc.h
strops.o: strops.h stdinc.h
color.o: color.h stdinc.h
files.o: files.h stdinc.h
slog.o: slog.h systime.h stdinc.h

.PHONY: clean
clean:
	$(RM) utils.a $(OBJS)
