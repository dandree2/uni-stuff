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
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHAN    ILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
    DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
    ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

/* Define valid parameters */
#define TITLE_STRING  "title"
#define ARTIST_STRING "artist"
#define ALBUM_STRING  "album"
#define YEAR_STRING   "year"

/* Define basic sizes */
#define NMR_METADATA_FIELDS ((size_t) 5)
#define METADATA_SIZE       NMR_METADATA_FIELDS * (size_t) eMaxSize
#define FIFO_NAME           "metadata_fifo"
#define RESPONSE_LEN        ((size_t) 30)

typedef int  int32_t;
typedef long int64_t;

typedef unsigned char byte;
typedef unsigned int  uint32_t;
typedef unsigned long uint64_t;

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

typedef struct Message
{
    byte flag;
    byte msg_buf[eMaxSize];
} sPackage;

/* Define function prototypes */
byte *getTitle(const uint32_t);
byte *getArtist(const uint32_t);
byte *getAlbum(const uint32_t);
byte *getYear(const uint32_t);

/* Define arrays in the Data segment */
static byte buffer[eMaxSize]          = {0};
static byte mp3_data[METADATA_SIZE]   = {0};
static byte reponse_buf[RESPONSE_LEN] = {0};
static const byte response_msg[]      = "Information printed!\n";

/* TODO: Split to additional functions */
int32_t main(int argc, char **argv) //Must remain int
{   
    pid_t childId = 0;

    /* Create the FIFO (named pipe) - it will be executed
    for child and parent - the first one, who executes this
    code will create it. The second one will fail, but this
    is not an issue, because it's already in the file system.
    */
    (void) mkfifo(FIFO_NAME, 0666);

    childId = fork();

    if (0 == childId)
    {
        /* Creates a named pipe */
        int32_t named_pipe = open(FIFO_NAME, O_RDWR);

        /* Initialize the message var */
        sPackage message = {0};

        /* Endless loop */
        for(;;)
        {
            /* TODO: Check the returned values */
            (void) read(named_pipe, &message, sizeof(message));
            (void) strcat(mp3_data, message.msg_buf);

            if (1 == message.flag)
            {
                /* TODO: Check read's output */
                (void) printf("\n %s \n", mp3_data);
                (void) write(named_pipe, response_msg, sizeof(response_msg));
                break;
            }
        }

        /* What happens to the pipe? */
        close(named_pipe);
    }
    else if (0 < childId)
    {
        if (argc >= 1)
        {
            int32_t fd = open(argv[1], O_RDONLY);

            if (0 <= fd)
            {
                uint32_t iterator   = 0;
                int32_t  named_pipe = open(FIFO_NAME, O_RDWR);
                sPackage message    = {0};

                for (iterator = 2; iterator < argc; iterator++)
                {
                    // If input parameters for the metadata are provided:
                    if (strcmp(argv[iterator], TITLE_STRING) == 0)
                    {
                        (void) strncpy(message.msg_buf, getTitle(fd), TITLE_SIZE);  
                    }
                    else if (strcmp(argv[iterator], ARTIST_STRING) == 0)
                    {
                        (void) strncpy(message.msg_buf, getArtist(fd), ARTIST_SIZE);
                    }
                    else if (strcmp(argv[iterator], ALBUM_STRING) == 0)
                    {
                        (void) strncpy(message.msg_buf, getAlbum(fd), ALBUM_SIZE);
                    }
                    else if (strcmp(argv[iterator], YEAR_STRING) == 0)
                    {
                        (void) strncpy(message.msg_buf, getYear(fd), YEAR_SIZE);
                    }
                    else
                    {
                        (void) printf("Parameter %d is unknown\n", iterator);
                    }

                    /* Send the content. */
                    /* TODO: Check the returned value. */
                    (void) write(named_pipe, &message, sizeof(message));

                    // Reinitialize the message to 0.
                    memset(&message, 0, sizeof(message));
                }

                message.flag = 1;
                memset(message.msg_buf, 0, sizeof(eMaxSize));

                /* Send the content. */
                /* TODO: Check the returned value. */
                (void) write(named_pipe, &message, sizeof(message));

                /* Receive the final response. */
                /* TODO: Check the returned value. */
                (void) read(named_pipe, reponse_buf, sizeof(reponse_buf));
                printf("\n %s \n", reponse_buf);

                /* TODO: Check the returned value. */
                (void) close(fd);
                (void) close(named_pipe);
            }
        }
        else
        {
            (void) printf("Insufficient number of parameters\n");
        }
    }
    else
    {
        printf("Fork failed!");
    }

    /* Why do we do that? */
    (void) unlink(FIFO_NAME);

    return 0;
}

/* TODO: Check funtions' returned values. */
byte *getTitle(const uint32_t fd_param)
{
    // Get the offset byte.
    (void) lseek(fd_param, TITLE_OFFSET, SEEK_END);

    // Read the data and put into buffer.
    (void) read(fd_param, buffer, sizeof(byte) * TITLE_SIZE);

    // Remove the white-space characters.
    (void) strtok(buffer, " ");

    return buffer;
}

byte *getArtist(const uint32_t fd_param)
{
    // Get the offset byte.
    (void) lseek(fd_param, ARTIST_OFFSET, SEEK_END);

    // Read the data and put into buffer.
    (void) read(fd_param, buffer, sizeof(byte) * ARTIST_SIZE);

    // Remove the white-space characters.
    (void) strtok(buffer, " ");

    return buffer;
}

byte *getAlbum(const uint32_t fd_param)
{
    // Get the offset byte.
    (void) lseek(fd_param, ALBUM_OFFSET, SEEK_END);

    // Read the data and put into buffer.
    (void) read(fd_param, buffer, sizeof(byte) * ALBUM_SIZE);

    // Remove the white-space characters.
    (void) strtok(buffer, " ");

    return buffer;
}

byte *getYear(const uint32_t fd_param)
{
    // Get the offset byte.
    (void) lseek(fd_param, YEAR_OFFSET, SEEK_END);

    // Read the data and put into buffer.
    (void) read(fd_param, buffer, sizeof(byte) * YEAR_SIZE);

    // Remove the white-space characters.
    (void) strtok(buffer, " ");

    return buffer;
}
