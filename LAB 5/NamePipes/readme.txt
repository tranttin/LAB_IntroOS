The fifoWriter program above can be summarized as follows:

The program creates a named pipe for writing:
mkfifo(pipeName, 0666); /* read/write perms for user/group/others */
int fd = open(pipeName, O_CREAT | O_WRONLY);
where pipeName is the name of the backing file passed to mkfifo as the first argument. The named pipe then is opened with the by-now familiar call to the open function, which returns a file descriptor.
For a touch of realism, the fifoWriter does not write all the data at once, but instead writes a chunk, sleeps a random number of microseconds, and so on. In total, 768,000 4-byte integer values are written to the named pipe.
After closing the named pipe, the fifoWriter also unlinks the file:
close(fd);        /* close pipe: generates end-of-stream marker */
unlink(pipeName); /* unlink from the implementing file */
The system reclaims the backing file once every process connected to the pipe has performed the unlink operation. In this example, there are only two such processes: the fifoWriter and the fifoReader, both of which do an unlink operation.
The two programs should be executed in different terminals with the same working directory. However, the fifoWriter should be started before the fifoReader, as the former creates the pipe. The fifoReader then accesses the already created named pipe.



The fifoReader program above can be summarized as follows:

Because the fifoWriter creates the named pipe, the fifoReader needs only the standard call open to access the pipe through the backing file:
const char* file = "./fifoChannel";
int fd = open(file, O_RDONLY);
The file opens as read-only.
The program then goes into a potentially infinite loop, trying to read a 4-byte chunk on each iteration. The read call:
ssize_t count = read(fd, &next, sizeof(int));
returns 0 to indicate end-of-stream, in which case the fifoReader breaks out of the loop, closes the named pipe, and unlinks the backing file before terminating.
After reading a 4-byte integer, the fifoReader checks whether the number is a prime. This represents the business logic that a production-grade reader might perform on the received bytes. On a sample run, there were 37,682 primes among the 768,000 integers received.
On repeated sample runs, the fifoReader successfully read all of the bytes that the fifoWriter wrote. This is not surprising. The two processes execute on the same host, taking network issues out of the equation. Named pipes are a highly reliable and efficient IPC mechanism and, therefore, in wide use.

Here is the output from the two programs, each launched from a separate terminal but with the same working directory:
