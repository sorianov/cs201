//----------------------------------------------------------------------------
// Author: Victor Soriano Mendoza
// Instructor: Rich Albers
// Date: 2019-11-30
// Title: Assignment 8: Processes (forking, signals, pipes)
// Description: A program which creates up to 4 child processes, does
// interprocess communication via signals, and properly processes the
// children's exit values.
//----------------------------------------------------------------------------
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

/**
 * Prints program help
 */
void printHelp(char** argv) {
    printf("%s help:\n", argv[0]);
    printf("\t%s fork_count\n", argv[0]);
}

/**
 * Parent SIGUSR1 handler.
 *
 * Will send a SIGUSR1 signal to every child in the global children array.
 *
 * Input:
 * int sig - SIGNAL
 */
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

/**
 * Child SIGUSR1 handler.
 *
 * Prints a message to stdout upon receival of a SIGUSR1 signal. Will increment
 * global long childSignals for every signal received.
 *
 * Input:
 * int sig - SIGNAL
 */
void handleChildUSR1(int sig) {
    printf("CHILD: SIGUSR1 signal received!\n");
    fflush(stdout);
    ++childSignals;
}

/**
 * Parent SIGTERM handler.
 *
 * Sends a SIGKILL signal to every child in the global children array and
 * to the callee.
 *
 * Input:
 * int sig - SIGNAL
 */
void handleParentTERM(int sig) {
    // send SIGKILL to children
    pid_t pid;
    for (size_t i = 0; i < numForks; ++i) {
        pid = children[i];
        kill(pid, SIGKILL);
    }
    // send SIGKILL to parent
    raise(SIGKILL);
}

/**
 * For use by forked children processes. Will sleep between 30 and 60 seconds
 * and will return number of SIGUSR1 signals received.
 *
 * Return:
 * global int childSignals - Number of SIGUSR1 signals received.
 */
int child() {
    int maxSeconds = 60;
    int minSeconds = 30;
    int seconds = 0;
    int remainingSeconds;

    signal(SIGUSR1, handleChildUSR1);

    printf("CHILD %d is alive!\n", getpid());
    fflush(stdout);

    seconds = rand() % (maxSeconds - minSeconds + 1) + minSeconds;
    remainingSeconds = sleep(seconds);
    while (remainingSeconds != 0) {
        remainingSeconds = sleep(remainingSeconds);
    }
    exit(childSignals);
}

/**
 * For use by the parent process. Registers SIGUSR1 and SIGTERM handlers.
 */
void parent() {
    signal(SIGUSR1, handleParentUSR1);
    signal(SIGTERM, handleParentTERM);
}

void parseArgs(int argc, char** argv) {
    char* tailPtr;
    long forks;
    if (argc != 2) {
        printHelp(argv);
        exit(EXIT_FAILURE);
    }

    forks = strtol(argv[1], &tailPtr, 10);
    if (numForks > MAX_FORKS) {
        numForks = MAX_FORKS;
    }
    if (numForks < MIN_FORKS) {
        numForks = MIN_FORKS;
    }

    numForks = forks;
}

/**
 * Forks processes according to global long numForks.
 *
 * Prints a parent pid, and number of children to be forked. Saves children
 * pids in global children array. If any fork fails, parent exits.
 */
void forkProcesses() {
    pid_t pid;

    printf("PARENT: process id is %d\n", getpid());
    printf("PARENT: Forking %ld times.\n", numForks);
    fflush(stdout);
    for(size_t i = 0; i < numForks; ++i) {
        children[i] = fork();
        pid = children[i];

        if (pid > 0 ) {
            parent();
        } else if (pid == 0) {
            child();
            exit(0); // don't let the child enter for loop
        } else {
            perror("Fork failed. Exiting.\n");
            // TODO: Proper child cleanup
            exit(EXIT_FAILURE);
        }
    }
}

/**
 * For use by the parent to wait children exit.
 *
 * Waits for children to exit and prints sum of children's exit codes.
 */
void waitForChildren() {
    int exitSum = 0;
    int status = 0;
    int n = numForks;

    printf("PARENT: waiting for children to end.\n");
    fflush(stdout);
    while (n > 0) {
        wait(&status);
        if (WIFEXITED(status)) {
            exitSum += WEXITSTATUS(status);
        }
        --n;
    }
    printf("PARENT: sum of children exit codes: %d\n", exitSum);
    fflush(stdout);
}

int main(int argc, char* argv[]) {

    parseArgs(argc, argv);
    children = (pid_t*) malloc(sizeof(pid_t) * numForks);
    forkProcesses();

    waitForChildren();
    free(children);
    return EXIT_SUCCESS;
}
