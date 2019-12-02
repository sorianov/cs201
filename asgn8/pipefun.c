#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

const int MAX_LENGTH = 255;

int main(int argc, char* argv[]) {
    int fd[2];
    int status;
    pid_t pid;
    char* string;
    char* dString;
    int nbytes;

    pipe(fd);
    pid = fork();

    if (pid > 0) {
        // parent
        printf("Parent [%d] forked.\n", getpid());
        close(fd[1]);
        string = (char*) malloc(sizeof(char) * MAX_LENGTH); 
        nbytes = read(fd[0], string, MAX_LENGTH);
        dString = (char*) malloc(sizeof(char) * (nbytes+1));
        for (size_t i = 0; i < nbytes; ++i) {
            dString[i] = string[i];
        }
        if (nbytes != 0) {
            printf("Parent recieved: [%s]\n", dString);
        } else {
            printf("Read failure.\n");
        }
    } else if (pid == 0) {
        // child
        printf("Child [%d] created.\n", getpid());
        close(fd[0]);
        string = (char*) malloc(sizeof(char) * MAX_LENGTH); 
        nbytes = snprintf(string, MAX_LENGTH, "Child [%d] reporting in.", getpid());
        if (MAX_LENGTH > nbytes) {
            printf("String should be reallocated. Wrote %d bytes\n", nbytes);
            dString = (char*) malloc(sizeof(char) * (nbytes+1));
            for (size_t i = 0; i < nbytes; ++i) {
                dString[i] = string[i];
            }
            free(string);
        }
        printf("%s\n", dString);
        write(fd[1], dString, nbytes);
        free(dString);
        exit(0);
    } else {
        perror("Fork failed.\n");
        exit(1);
    }
    wait(&status);
    //return EXIT_SUCCESS;
}
