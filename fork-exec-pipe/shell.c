#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>
#include "readcmd.h"

int main(void)
{
    while (1) {
        printf("shell> ");

        struct cmdline *line = readcmd();
        char ***cmds = line->seq;
        int status;
        
        if (strcmp(cmds[0][0], "exit") == 0) {
            exit(EXIT_SUCCESS);
        }

        if (cmds[1] == NULL) {
            pid_t pid = fork();
            if (pid == 0) {
                execvp(cmds[0][0], cmds[0]);
            } else if (pid != -1) {
                waitpid(pid, &status, 0);
                continue;
            }
        }

        int p[2];
        pipe(p);

        pid_t pid = fork();
        if (pid == 0) {
            close(p[0]);
            dup2(p[1], STDOUT_FILENO);
            close(p[1]);
            execvp(cmds[0][0], cmds[0]);
        } else if (pid != -1) {
            waitpid(pid, &status, 0);
            close(p[1]);
        }

        pid_t next_pid = fork();
        if (next_pid == 0) {
            dup2(p[0], STDIN_FILENO);
            close(p[0]);
            execvp(cmds[1][0], cmds[1]);
        } else if (pid != -1) {
            waitpid(next_pid, &status, 0);
            close(p[0]);
            continue;
        }
    }

    return 0;
}
