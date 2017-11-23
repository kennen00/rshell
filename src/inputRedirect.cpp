#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <fcntl.h>

#include "../header/inputRedirect.h"
#include "../header/command.h"

InputRedirect::InputRedirect() : Connector(0, 0) {}

InputRedirect::InputRedirect(Base* left, Base* right) : Connector(left, right) {}

bool InputRedirect::execute() {
    int in;
    pid_t pid;
    int statVal;

    pid = fork();
    if (!pid) {
        in = open(static_cast<Command*>(right)->getFirst(), O_RDONLY);
        if (in == -1) {
            perror("open");
            exit(EXIT_FAILURE);
            return false;
        }
        if (dup2(in, 0) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
            return false;
        }
        if (close(in) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
            return false;
        }
        if (!left->execute()) {
            exit(EXIT_FAILURE);
            return false;
        }
        exit(EXIT_SUCCESS);
    } else if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
        return false;
    } else {
        do {
            waitpid(pid, &statVal, 0);
        } while (!WIFEXITED(statVal));
    }
    return !WEXITSTATUS(statVal);
}

int InputRedirect::precedence() {
    return 1;
}
