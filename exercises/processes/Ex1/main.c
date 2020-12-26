#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    int status; // for waitpid() call
    int pid;
    int p[2];

    pipe(p);

    pid = fork();
    
    if (pid == 0) {
        waitpid(getppid(), &status, 0);

        close(p[1]);
        dup2(p[0], STDIN_FILENO);
        close(p[0]);

        execlp("Print", "Print", NULL);
    } else if (pid != -1) {
        close(p[0]);
        dup2(p[1], STDOUT_FILENO);
        close(p[1]);

        execlp("gendoc", "gendoc", NULL);
    }

    return 0;
}
