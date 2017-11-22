#include <unistd.h>
#include <fcntl.h>

#include "../header/pipe.h"

Pipe::Pipe() : Connector(0, 0) {};

Pipe::Pipe(Base* left, Base* right) : Connector(left, right) {};

bool Pipe::execute() {
    int pipefd[2];
    pid_t cpid;
    int statVal;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return false;
    }
    
    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) {
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        right->execute();
    } else {
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        left->execute();
        do {
            waitpid(cpid, &statVal, 0);
        } while (!WIFEXITED(statVal));
    }
    return !WEXITSTATUS(statVal);    
}
