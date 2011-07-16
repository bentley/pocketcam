CFLAGS += -std=c99 -I/usr/local/include/libpng
LDFLAGS += -L/usr/local/lib -lm -lpng -lz

all: pocketcam

pocketcam: pocketcam.c
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $>

clean:
	rm -f pocketcam
