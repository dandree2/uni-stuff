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

typedef enum Response
{
    NOT_REQUIRED = 0,
    REQUIRED     = 1
} eResponses;

typedef struct Message
{
    eResponses flag;
    char       msg_buf[eMaxSize];
} sPackage;

/* Define function prototypes */
char *getTitle(const int);
char *getArtist(const int);
char *getAlbum(const int);
char *getYear(const int);

/* Define arrays in the Data segment */
static char buffer[eMaxSize]          = {0};
static char mp3_data[METADATA_SIZE]   = {0};
static char reponse_buf[RESPONSE_LEN] = {0};
static const char response_msg[]      = "Information printed!\n";

/* TODO: Split to additional functions */
int main(int argc, char **argv) //Must remain int
{   
    pid_t childId = 0;

    int named_pipe_fd = 0;

    /* Create the FIFO (named pipe) - it will be executed
    for child and parent - the first one, who executes this
    code will create it. The second one will fail, but this
    is not an issue, because it's already in the file system.
    */
    (void) mkfifo(FIFO_NAME, 0666);

    childId = fork();

    if (0 == childId)
    {
        /* Initialize the message var */
        sPackage message = {0};

        /* Creates a named pipe */
        named_pipe_fd = open(FIFO_NAME, O_RDWR);

        if (0 <= named_pipe_fd)
        {
            /* Endless loop */
            for(;;)
            {
                /* TODO: Check the returned values */
                (void) read(named_pipe_fd, &message, sizeof(message));

                (void) strcat(mp3_data, " ");
                (void) strcat(mp3_data, message.msg_buf);

                if (REQUIRED == message.flag)
                {
                    (void) printf("Child received: %s\n", mp3_data);
                    
                    /* TODO: Check read's output */
                    (void) write(named_pipe_fd, response_msg, sizeof(response_msg));
                    // Makes sure the pipe remains open prior deletion.
                    //sleep(1);
                                       // Disables the child;
                    (void) close(named_pipe_fd);
                    break;
                }
            }
        }
        else
        {
            (void) printf("Child cannot open the pipe!\n");
        }
    }
    else if (0 < childId)
    {
        if (argc >= 1)
        {
            int fd = open(argv[1], O_RDONLY);

            if (0 <= fd)
            {
                size_t iterator  = 0;
                named_pipe_fd    = open(FIFO_NAME, O_RDWR);
                sPackage message = {0};

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
                        (void) printf("Parameter %d is unknown\n", (int)iterator);
                    }

                    /* Send the content. */
                    /* TODO: Check the returned value. */
                    message.flag = NOT_REQUIRED;
                    (void) write(named_pipe_fd, &message, sizeof(message));

                    // Reinitialize the message to 0.
                    memset(&message, 0, sizeof(message));

                    // Makes sure duplex communication appears on different systems.
                    sleep(1);
                }

                message.flag = REQUIRED;
                (void) write(named_pipe_fd, &message, sizeof(message));
                memset(message.msg_buf, 0, sizeof(eMaxSize));

                /* Receive the final response. */
                /* TODO: Check the returned value. */
                (void) read(named_pipe_fd, reponse_buf, sizeof(reponse_buf));
                (void) printf("Response in parent: %s\n", response_msg);

                sleep(1);
                /* TODO: Check the returned value. */
                (void) close(fd);
            }
        }
        else
        {
            (void) printf("Insufficient number of parameters\n");
        }
    }
    else
    {
        (void) printf("Fork failed!");
    }

    /* Why do we do that? */
    (void) unlink(FIFO_NAME);

    return 0;
}

/* TODO: Check funtions' returned values. */
char *getTitle(const int fd_param)
{
    // Get the offset char.
    (void) lseek(fd_param, TITLE_OFFSET, SEEK_END);

    // Read the data and put into buffer.
    (void) read(fd_param, buffer, sizeof(char) * TITLE_SIZE);

    // Remove the white-space characters.
    (void) strtok(buffer, " ");

    return buffer;
}

char *getArtist(const int fd_param)
{
    // Get the offset char.
    (void) lseek(fd_param, ARTIST_OFFSET, SEEK_END);

    // Read the data and put into buffer.
    (void) read(fd_param, buffer, sizeof(char) * ARTIST_SIZE);

    // Remove the white-space characters.
    (void) strtok(buffer, " ");

    return buffer;
}

char *getAlbum(const int fd_param)
{
    // Get the offset char.
    (void) lseek(fd_param, ALBUM_OFFSET, SEEK_END);

    // Read the data and put into buffer.
    (void) read(fd_param, buffer, sizeof(char) * ALBUM_SIZE);

    // Remove the white-space characters.
    (void) strtok(buffer, " ");

    return buffer;
}

char *getYear(const int fd_param)
{
    // Get the offset char.
    (void) lseek(fd_param, YEAR_OFFSET, SEEK_END);

    // Read the data and put into buffer.
    (void) read(fd_param, buffer, sizeof(char) * YEAR_SIZE);

    // Remove the white-space characters.
    (void) strtok(buffer, " ");

    return buffer;
}
