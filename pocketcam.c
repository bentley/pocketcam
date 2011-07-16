/* This program is in the public domain. */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int
main(int argc, char* argv[])
{
	FILE* sav;

	if (argc > 1) {
		sav = fopen(argv[argc - 1], "r");

		if (sav == NULL) {
			perror("Error opening save file");
			exit(1);
		}
	} else {
		printf("usage: pocketcam [savefile]\n");
		exit(0);
	}

	unsigned char bitmapHeader[0x436] =
		{ 'B', 'M', /* magic number */
			0x36, 0x3C, 0, 0, /* filesize */
			0, 0, 0, 0, /* unused */
			0x36, 4, 0, 0, /* offset of bitmap data */
			0x28, 0, 0, 0, /* header size */
			0x80, 0, 0, 0, /* image width */
			0x70, 0, 0, 0, /* image height */
			1, 0, /* color planes used */
			8, 0, /* 256color */
			0, 0, 0, 0, /* no compression */
			0x00, 0x38, 0, 0, /* 0x3800 bytes */
			0xC4, 0x0E, 0, 0, /* horizontal res */
			0xC4, 0x0E, 0, 0, /* vertical res */
			0, 0, 0, 0, /* number of colors in palette */
			0, 0, 0, 0, /* important colors */
0,0,0,0,0,0,0x80,0,0,0x80,0,0,0,0x80,0x80,0,
0x80,0,0,0,0x80,0,0x80,0,0x80,0x80,0,0,0xC0,0xC0,0xC0,0,
0xC0,0xDC,0xC0,0,0xF0,0xCA,0xA6,0,0,0x20,0x40,0,0,0x20,0x60,0,
0,0x20,0x80,0,0,0x20,0xA0,0,0,0x20,0xC0,0,0,0x20,0xE0,0,
0,0x40,0,0,0,0x40,0x20,0,0,0x40,0x40,0,0,0x40,0x60,0,
0,0x40,0x80,0,0,0x40,0xA0,0,0,0x40,0xC0,0,0,0x40,0xE0,0,
0,0x60,0,0,0,0x60,0x20,0,0,0x60,0x40,0,0,0x60,0x60,0,
0,0x60,0x80,0,0,0x60,0xA0,0,0,0x60,0xC0,0,0,0x60,0xE0,0,
0,0x80,0,0,0,0x80,0x20,0,0,0x80,0x40,0,0,0x80,0x60,0,
0,0x80,0x80,0,0,0x80,0xA0,0,0,0x80,0xC0,0,0,0x80,0xE0,0,
0,0xA0,0,0,0,0xA0,0x20,0,0,0xA0,0x40,0,0,0xA0,0x60,0,
0,0xA0,0x80,0,0,0xA0,0xA0,0,0,0xA0,0xC0,0,0,0xA0,0xE0,0,
0,0xC0,0,0,0,0xC0,0x20,0,0,0xC0,0x40,0,0,0xC0,0x60,0,
0,0xC0,0x80,0,0,0xC0,0xA0,0,0,0xC0,0xC0,0,0,0xC0,0xE0,0,
0,0xE0,0,0,0,0xE0,0x20,0,0,0xE0,0x40,0,0,0xE0,0x60,0,
0,0xE0,0x80,0,0,0xE0,0xA0,0,0,0xE0,0xC0,0,0,0xE0,0xE0,0,
0x40,0,0,0,0x40,0,0x20,0,0x40,0,0x40,0,0x40,0,0x60,0,
0x40,0,0x80,0,0x40,0,0xA0,0,0x40,0,0xC0,0,0x40,0,0xE0,0,
0x40,0x20,0,0,0x40,0x20,0x20,0,0x40,0x20,0x40,0,0x40,0x20,0x60,0,
0x40,0x20,0x80,0,0x40,0x20,0xA0,0,0x40,0x20,0xC0,0,0x40,0x20,0xE0,0,
0x40,0x40,0,0,0x40,0x40,0x20,0,0x40,0x40,0x40,0,0x40,0x40,0x60,0,
0x40,0x40,0x80,0,0x40,0x40,0xA0,0,0x40,0x40,0xC0,0,0x40,0x40,0xE0,0,
0x40,0x60,0,0,0x40,0x60,0x20,0,0x40,0x60,0x40,0,0x40,0x60,0x60,0,
0x40,0x60,0x80,0,0x40,0x60,0xA0,0,0x40,0x60,0xC0,0,0x40,0x60,0xE0,0,
0x40,0x80,0,0,0x40,0x80,0x20,0,0x40,0x80,0x40,0,0x40,0x80,0x60,0,
0x40,0x80,0x80,0,0x40,0x80,0xA0,0,0x40,0x80,0xC0,0,0x40,0x80,0xE0,0,
0x40,0xA0,0,0,0x40,0xA0,0x20,0,0x40,0xA0,0x40,0,0x40,0xA0,0x60,0,
0x40,0xA0,0x80,0,0x40,0xA0,0xA0,0,0x40,0xA0,0xC0,0,0x40,0xA0,0xE0,0,
0x40,0xC0,0,0,0x40,0xC0,0x20,0,0x40,0xC0,0x40,0,0x40,0xC0,0x60,0,
0x40,0xC0,0x80,0,0x40,0xC0,0xA0,0,0x40,0xC0,0xC0,0,0x40,0xC0,0xE0,0,
0x40,0xE0,0,0,0x40,0xE0,0x20,0,0x40,0xE0,0x40,0,0x40,0xE0,0x60,0,
0x40,0xE0,0x80,0,0x40,0xE0,0xA0,0,0x40,0xE0,0xC0,0,0x40,0xE0,0xE0,0,
0x80,0,0,0,0x80,0,0x20,0,0x80,0,0x40,0,0x80,0,0x60,0,
0x80,0,0x80,0,0x80,0,0xA0,0,0x80,0,0xC0,0,0x80,0,0xE0,0,
0x80,0x20,0,0,0x80,0x20,0x20,0,0x80,0x20,0x40,0,0x80,0x20,0x60,0,
0x80,0x20,0x80,0,0x80,0x20,0xA0,0,0x80,0x20,0xC0,0,0x80,0x20,0xE0,0,
0x80,0x40,0,0,0x80,0x40,0x20,0,0x80,0x40,0x40,0,0x80,0x40,0x60,0,
0x80,0x40,0x80,0,0x80,0x40,0xA0,0,0x80,0x40,0xC0,0,0x80,0x40,0xE0,0,
0x80,0x60,0,0,0x80,0x60,0x20,0,0x80,0x60,0x40,0,0x80,0x60,0x60,0,
0x80,0x60,0x80,0,0x80,0x60,0xA0,0,0x80,0x60,0xC0,0,0x80,0x60,0xE0,0,
0x80,0x80,0,0,0x80,0x80,0x20,0,0x80,0x80,0x40,0,0x80,0x80,0x60,0,
0x80,0x80,0x80,0,0x80,0x80,0xA0,0,0x80,0x80,0xC0,0,0x80,0x80,0xE0,0,
0x80,0xA0,0,0,0x80,0xA0,0x20,0,0x80,0xA0,0x40,0,0x80,0xA0,0x60,0,
0x80,0xA0,0x80,0,0x80,0xA0,0xA0,0,0x80,0xA0,0xC0,0,0x80,0xA0,0xE0,0,
0x80,0xC0,0,0,0x80,0xC0,0x20,0,0x80,0xC0,0x40,0,0x80,0xC0,0x60,0,
0x80,0xC0,0x80,0,0x80,0xC0,0xA0,0,0x80,0xC0,0xC0,0,0x80,0xC0,0xE0,0,
0x80,0xE0,0,0,0x80,0xE0,0x20,0,0x80,0xE0,0x40,0,0x80,0xE0,0x60,0,
0x80,0xE0,0x80,0,0x80,0xE0,0xA0,0,0x80,0xE0,0xC0,0,0x80,0xE0,0xE0,0,
0xC0,0,0,0,0xC0,0,0x20,0,0xC0,0,0x40,0,0xC0,0,0x60,0,
0xC0,0,0x80,0,0xC0,0,0xA0,0,0xC0,0,0xC0,0,0xC0,0,0xE0,0,
0xC0,0x20,0,0,0xC0,0x20,0x20,0,0xC0,0x20,0x40,0,0xC0,0x20,0x60,0,
0xC0,0x20,0x80,0,0xC0,0x20,0xA0,0,0xC0,0x20,0xC0,0,0xC0,0x20,0xE0,0,
0xC0,0x40,0,0,0xC0,0x40,0x20,0,0xC0,0x40,0x40,0,0xC0,0x40,0x60,0,
0xC0,0x40,0x80,0,0xC0,0x40,0xA0,0,0xC0,0x40,0xC0,0,0xC0,0x40,0xE0,0,
0xC0,0x60,0,0,0xC0,0x60,0x20,0,0xC0,0x60,0x40,0,0xC0,0x60,0x60,0,
0xC0,0x60,0x80,0,0xC0,0x60,0xA0,0,0xC0,0x60,0xC0,0,0xC0,0x60,0xE0,0,
0xC0,0x80,0,0,0xC0,0x80,0x20,0,0xC0,0x80,0x40,0,0xC0,0x80,0x60,0,
0xC0,0x80,0x80,0,0xC0,0x80,0xA0,0,0xC0,0x80,0xC0,0,0xC0,0x80,0xE0,0,
0xC0,0xA0,0,0,0xC0,0xA0,0x20,0,0xC0,0xA0,0x40,0,0xC0,0xA0,0x60,0,
0xC0,0xA0,0x80,0,0xC0,0xA0,0xA0,0,0xC0,0xA0,0xC0,0,0xC0,0xA0,0xE0,0,
0xC0,0xC0,0,0,0xC0,0xC0,0x20,0,0xC0,0xC0,0x40,0,0xC0,0xC0,0x60,0,
0xC0,0xC0,0x80,0,0xC0,0xC0,0xA0,0,0xF0,0xFB,0xFF,0,0xA4,0xA0,0xA0,0,
0x80,0x80,0x80,0,0,0,0xFF,0,0,0xFF,0,0,0,0xFF,0xFF,0,
0xFF,0,0,0,0xFF,0,0xFF,0,0xFF,0xFF,0,0,0xFF,0xFF,0xFF,0
};

	for (int picNumber = 0; picNumber < 30; ++picNumber) {
		/* copy image to memory */

		fseek(sav, 0x2000 + picNumber * 0x1000, SEEK_SET);

		unsigned short int pixels[112][128];

		for (int y = 0; y < 14; ++y) {
			for (int x = 0; x < 16; ++x) {
				for (int i = 0; i < 8; ++i) {
					int byte1, byte2;
					byte1 = fgetc(sav);
					byte2 = fgetc(sav);
					for (int j = 0; j < 8; ++j) {
						pixels[y * 8 + i][x * 8 + j] =
						    (((byte2 >> (7 - j) & 1))
						    << 1 | ((byte1 >> (7 - j)
						    & 1)));
					}
				}
			}
		}

		char filename[13];
		snprintf(filename, 13, "bitmap%02d.bmp", picNumber);
		FILE* bitmap = fopen(filename, "w");

		if (bitmap == NULL) {
			perror("Error creating new bitmap file");
			exit(1);
		}

		for (int i = 0; i < 0x436; ++i)
			fputc(bitmapHeader[i],bitmap);

		for (int i = 112; i >= 0; --i)
			for (int j = 0; j < 128; ++j) {
				int byte;
				switch (pixels[i][j]) {
				case 0:
					byte = 0xFF;
					break;
				case 1:
					byte = 0xED;
					break;
				case 2:
					byte = 0x9B;
					break;
				case 3:
					byte = 0x49;
				}
				fputc(byte, bitmap);
			}

		fclose(bitmap);
	}

	fclose(sav);

	exit(0);
}
