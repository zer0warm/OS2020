#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int pid;
    int status;
    int AtoBpipe[2];
    int BtoApipe[2];

    pipe(AtoBpipe);
    pipe(BtoApipe);

    pid = fork();
    if (pid == 0) {
        close(AtoBpipe[0]);
        dup2(AtoBpipe[1], STDOUT_FILENO);
        close(AtoBpipe[1]);

        close(BtoApipe[1]);
        dup2(BtoApipe[0], STDIN_FILENO);
        close(BtoApipe[0]);

        execl("./a.out", "ProgramA", NULL);
    } else if (pid == -1) {
        perror("main: Can't fork to exec ProgramA.");
    }

    close(AtoBpipe[1]);
    close(BtoApipe[0]);

    dup2(BtoApipe[1], STDOUT_FILENO);
    close(BtoApipe[1]);

    dup2(AtoBpipe[0], STDIN_FILENO);
    close(AtoBpipe[0]);

    execl("./b.out", "ProgramB", NULL);

    return 0;
}
