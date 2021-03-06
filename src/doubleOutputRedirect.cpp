#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <fcntl.h>

#include "../header/doubleOutputRedirect.h"
#include "../header/command.h"

DoubleOutputRedirect::DoubleOutputRedirect() : Connector(0, 0) {}

DoubleOutputRedirect::DoubleOutputRedirect(Base* left, Base* right) : Connector(left, right) {}

bool DoubleOutputRedirect::execute() {
    int out;
    pid_t pid;
    int statVal;

    pid = fork();
    if (!pid) {
        out = open(static_cast<Command*>(right)->getFirst(), O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

        if (out == -1) {
            perror("open");
            exit(EXIT_FAILURE);
            return false;
        }
        if (dup2(out, 1) == -1) {
            perror("dup2");
            exit(EXIT_FAILURE);
            return false;
        }
        if (!left->execute()) {
            exit(EXIT_FAILURE);
            return false;
        }
        if (close(out) == -1) {
            perror("close");
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

int DoubleOutputRedirect::precedence() {
    return 1;
}
