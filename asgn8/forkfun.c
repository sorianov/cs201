#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

const long MAX_FORKS = 4;
const long MIN_FORKS = 1;

pid_t* children = NULL;
long numForks;
long childSignals = 0;

void printHelp(char** argv) {
    printf("%s fork_count\n", argv[0]);
}

void handleParentUSR1(int sig) {
    pid_t pid;
    printf("PARENT: SIGUSR1 signal recieved!\n");
    fflush(stdout);
    
    // send USR1 signal to each child
    for (size_t i = 0; i < numForks; ++i) {
        pid = children[i];
        kill(pid, SIGUSR1);
    }
}

void handleChildUSR1(int sig) {
    printf("CHILD: SIGUSR1 signal received!\n");
    fflush(stdout);
    ++childSignals;
}

void handleTERM(int sig) {
    // send SIGKILL to children
    // send SIGKILL to parent
}

int child() {
    int maxSeconds = 60;
    int minSeconds = 30;
    int seconds = 0;
    int remainingSeconds;
    signal(SIGUSR1, handleChildUSR1);
    printf("CHILD %d is alive!\n", getpid());
    seconds = rand() % (maxSeconds - minSeconds + 1) + minSeconds;
    remainingSeconds = sleep(seconds);
    while (remainingSeconds != 0) {
        remainingSeconds = sleep(remainingSeconds);
    }
    return childSignals;
}

void parent() {
    signal(SIGUSR1, handleParentUSR1);
    //signal(SIGTERM, handleTERM);
    printf("PARENT: process id is %d\n", getpid());
    printf("PARENT: Forking %ld times.\n", numForks);
}

void parseArgs(int argc, char** argv) {
    char* tailPtr;
    long forks = strtol(argv[1], &tailPtr, 10);
    
    if (argc != 2) {
        printHelp(argv);
        exit(EXIT_FAILURE);
    }
    
    if (numForks > MAX_FORKS) {
        numForks = MAX_FORKS;
    }
    if (numForks < MIN_FORKS) {
        numForks = MIN_FORKS;
    }

    numForks = forks;
}

pid_t forkProcesses() {
    pid_t pid;
    
    for(size_t i = 0; i < numForks; ++i) {
        children[i] = fork();
        pid = children[i];
        printf("FORK: %zu\n", i); // TODO: Remove debugging

        if (pid > 0 ) {
            parent(numForks);
        } else if (pid == 0) {
            child();
            exit(0); // don't let the child enter for loop
        } else {
            perror("Fork failed. Exiting.\n");
            exit(EXIT_FAILURE);
        }
    }
    return pid;
}

void waitForChildren() {
    int exitSum = 0;
    int status = 0;
    int n = numForks;
    
    printf("PARENT: waiting for children to end.\n");
    while (n > 0) {
        wait(&status);
        //printf("PARENT: child with PID %ld exited with status 0x%x.\n",
        //        (long)pid, status);
        exitSum += status;
        --n;
    }
    printf("PARENT: sum of children exit codes: %d\n", exitSum);
}

int main(int argc, char* argv[]) {

    parseArgs(argc, argv);
    children = (pid_t*) malloc(sizeof(pid_t) * numForks);
    forkProcesses();
   
    waitForChildren();
    free(children);
    return EXIT_SUCCESS;
}
