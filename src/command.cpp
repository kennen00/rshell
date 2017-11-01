#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>

#include "../header/command.h"

Command::Command(std::vector<char *> args) : args(args) {
    this->args.push_back((char *) 0);
}

bool Command::isConnector() {
	return false;
}

bool Command::execute() {
    pid_t pid;
    int statVal;

    pid = fork();
    if (!pid) {
        if (execvp(args.at(0), &args.at(0))) {
            perror("Error executing");
            exit(1);
            return false;
        }
    } else if (pid < 0) {
        perror("Error forking process");
        return false;
    } else {
        do {
           waitpid(pid, &statVal, 0); 
        } while (!WIFEXITED(statVal));
    }

    return !WEXITSTATUS(statVal);
}
