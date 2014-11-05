.POSIX:

all: pocketcam

pocketcam: pocketcam.c
	${CC} ${CFLAGS} -std=c99 `pkg-config --cflags --libs libpng` -o $@ $<

clean:
	rm -f pocketcam
