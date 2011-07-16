CFLAGS += -std=c99

all: pocketcam

pocketcam: pocketcam.c
	${CC} ${CFLAGS} -o $@ $>

clean:
	rm -f pocketcam
