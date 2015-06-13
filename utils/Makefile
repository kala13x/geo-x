LIB = -lnsl -lcrypt -lssl -lcrypto
CFLAGS = -g -O2 -Wall -fPIC -D_OPENSSL_MD5_=1

OBJS = systime.o color.o socks.o errex.o \
	files.o strops.o slog.o crypt.o

.c.o:
	$(CC) $(CFLAGS) -c $< $(LIB)

utils.a: $(OBJS)
	$(AR) rcs utils.a $(OBJS)
	@echo [-] Syncing static library
	sync

socks.o: socks.h slog.h errex.h color.h stdinc.h
errex.o: errex.h slog.h color.h stdinc.h
systime.o: systime.h stdinc.h
strops.o: strops.h stdinc.h
crypt.o: crypt.h stdinc.h
color.o: color.h stdinc.h
files.o: files.h stdinc.h
slog.o: slog.h systime.h stdinc.h

.PHONY: clean
clean:
	$(RM) utils.a $(OBJS)
