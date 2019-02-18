// DISCLAIMER: These files are only for studying and teaching purposes!
// They are not intendet to be a direct example of good coding practices 
// or C expert usage.
//

/*
	Copyright 2019 Desislav Andreev: desislav.andreev@gmail.com
	Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
	to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute,
	sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
	The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
	DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
	ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TITLE_STRING  "title"
#define ARTIST_STRING "artist"
#define ALBUM_STRING  "album"
#define YEAR_STRING   "year"

typedef enum Sizes
{
	TAG_SIZE    = 3,
	YEAR_SIZE   = 4,
	ARTIST_SIZE = 30,
	TITLE_SIZE  = 30,
	ALBUM_SIZE  = 30,
	eMaxSize    = 31
} eSizes;

typedef enum Offsets
{
	TAG_OFFSET    = -128,
	YEAR_OFFSET   = -35,
	TITLE_OFFSET  = -125,
	ARTIST_OFFSET = -95,
	ALBUM_OFFSET  = -65,
	eMaxOffset    = 0
} eOffsets;

void getTitle(const int);
void getArtist(const int);
void getAlbum(const int);
void getYear(const int);

static char buffer[eMaxSize] = {0};

int main(int argc, char **argv)
{
	if (argc >= 1)
	{
		int fd = open(argv[1], O_RDONLY);

		if (0 <= fd)
		{
			int i = 0;

			for (i = 2; i < argc; i++)
			{
				// If input parameters for the metadata are provided:
				if (strcmp(argv[i], TITLE_STRING) == 0)
				{
					getTitle(fd);	
				}
				else if (strcmp(argv[i], ARTIST_STRING) == 0)
				{
					getArtist(fd);
				}
				else if (strcmp(argv[i], ALBUM_STRING) == 0)
				{
					getAlbum(fd);
				}
				else if (strcmp(argv[i], YEAR_STRING) == 0)
				{
					getYear(fd);
				}
				else
				{
					(void) printf("Parameter %d is unknown\n", i);
				}

				// Print the content.
				(void) printf("%s\n", buffer);

				// Reinitialize the buffer to 0.
				memset(buffer, 0, sizeof(buffer));
			}

			(void) close(fd);
		}
	}
	else
	{
		(void) printf("Insufficient number of parameters\n");
	}
	return 0;
}

void getTitle(const int fd)
{
	// Get the offset byte.
	(void) lseek(fd, TITLE_OFFSET, SEEK_END);

	// Read the data and put into buffer.
	(void) read(fd, buffer, sizeof(char) * TITLE_SIZE);

	// Remove the white-space characters.
	(void) strtok(buffer, " ");
}

void getArtist(const int fd)
{
	// Get the offset byte.
	(void) lseek(fd, ARTIST_OFFSET, SEEK_END);

	// Read the data and put into buffer.
	(void) read(fd, buffer, sizeof(char) * ARTIST_SIZE);

	// Remove the white-space characters.
	(void) strtok(buffer, " ");
}

void getAlbum(const int fd)
{
	// Get the offset byte.
	(void) lseek(fd, ALBUM_OFFSET, SEEK_END);

	// Read the data and put into buffer.
	(void) read(fd, buffer, sizeof(char) * ALBUM_SIZE);

	// Remove the white-space characters.
	(void) strtok(buffer, " ");
}

void getYear(const int fd)
{
	// Get the offset byte.
	(void) lseek(fd, YEAR_OFFSET, SEEK_END);

	// Read the data and put into buffer.
	(void) read(fd, buffer, sizeof(char) * YEAR_SIZE);

	// Remove the white-space characters.
	(void) strtok(buffer, " ");
}
