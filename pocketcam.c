/*
 * Copyright © 2009–2011 Anthony J. Bentley <anthonyjbentley@gmail.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED “AS IS” AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <math.h>
#include <png.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char* argv[])
{
	FILE *sav;

	if (argc > 1) {
		sav = fopen(argv[argc - 1], "r");

		if (sav == NULL) {
			perror("Error opening save file");
			exit(1);
		}
	} else {
		printf("usage: pocketcam savefile\n");
		exit(0);
	}

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

		char filename[12];
		snprintf(filename, 12, "image%02d.png", picNumber + 1);
		FILE *f  = fopen(filename, "wb");

		if (f == NULL) {
			fprintf(stderr, "Error creating file '%s': ", filename);
			perror(NULL);
			exit(1);
		}

		png_structp png_ptr =
		    png_create_write_struct(PNG_LIBPNG_VER_STRING,
		    (png_voidp)NULL, NULL, NULL);
		if (png_ptr == NULL) {
			fprintf(stderr, "Could not create PNG write struct\n");
			exit(1);
		}

		png_infop info_ptr = png_create_info_struct(png_ptr);
		if (info_ptr == NULL) {
			png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
			fprintf(stderr, "Could not create PNG info struct\n");
			exit(1);
		}

		if (setjmp(png_jmpbuf(png_ptr))) {
			png_destroy_write_struct(&png_ptr, &info_ptr);
			fclose(f);
			fprintf(stderr, "Internal PNG error\n");
			exit(1);
		}

		png_init_io(png_ptr, f);

		png_set_IHDR(png_ptr, info_ptr, 128, 112, 2,
		    PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE,
		    PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

		png_write_info(png_ptr, info_ptr);

		png_byte *row_pointers[112];

		uint8_t row[112][32];

		for (int y = 112; y >= 0; --y)
			for (int x = 0; x < 128; ++x) {
				row[y][x / 4] = 0;
				for (int i = 0; i < 4; ++i)
					row[y][x / 4] |= (~pixels[y][x - i] & 3)
					    << (2 * i);
			}

		for (int i = 0; i < 112; ++i)
			row_pointers[i] = &row[i];

		png_write_image(png_ptr, row_pointers);

		png_write_end(png_ptr, NULL);
		png_destroy_write_struct(&png_ptr, &info_ptr);

		fclose(f);
	}

	fclose(sav);

	exit(0);
}
