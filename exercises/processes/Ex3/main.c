#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int pid;
    int status;
    // p1 will be the pipe between "ps -ef" and "grep firefox"
    int p1[2];
    // p2 will be the pipe between "grep firefox" and "wc -l"
    int p2[2];

    // Make p1 and p2 pipes:
    // - Anything written to p1[1] can be read from p1[0]
    // - Anything written to p2[1] can be read from p2[0]
    pipe(p1);
    pipe(p2);

    /* For executing ps -ef */
    pid = fork();

    if (pid == 0) {
        // We are in the first child process
        // We only need to capture the output of this command
        close(p1[0]);
        // Make standard output (with file descriptor STDOUT_FILENO, or commonly 1) the writing end of the first pipe
        dup2(p1[1], STDOUT_FILENO);
        close(p1[1]);

        // Execute the command ps -ef, acknowledging PATH is available
        execlp("ps", "ps", "-ef", NULL);
    } else if (pid == -1) {
        perror("main: Can't fork. (1)");
    }

    // Wait for the child created above to finish executing
    waitpid(pid, &status, 0);
    // Close unused file descriptor
    close(p1[1]);

    /* For executing ps -ef | grep firefox */
    pid = fork();

    if (pid == 0) {
        // We are in the second child
        // Make standard input the reading end of the first pipe
        dup2(p1[0], STDIN_FILENO);
        close(p1[0]);

        // Make standard output the writing end of the second pipe
        close(p2[0]);
        dup2(p2[1], STDOUT_FILENO);
        close(p2[1]);

        // Assuming there are "firefox" processes in ps -ef output.
        execlp("grep", "grep", "firefox", NULL);
    } else if (pid == -1) {
        perror("main: Can't fork. (2)");
    }

    waitpid(pid, &status, 0);
    // Close unused file descriptors
    close(p1[0]);
    close(p2[1]);

    /* For executing grep firefox | wc -l */
    pid = fork();

    if (pid == 0) {
        // Make standard input the reading end of the second pipe
        dup2(p2[0], STDIN_FILENO);
        close(p2[0]);

        execlp("wc", "wc", "-l", NULL);
    } else if (pid == -1) {
        perror("main: Can't fork. (3)");
    }

    waitpid(pid, &status, 0);
    // Close unused file descriptor
    close(p2[0]);

    return 0;
}
