#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>

#include "../header/command.h"

Command::Command(std::vector<char *> args) : args(args) {
    this->args.push_back((char *) 0);
}

/**
* Simple property evaluation function. Returns true if the
* object is a connector.
*
* @param None.
* @return Bool, representing if the object is a connector (false)
*/
bool Command::isConnector() {
	return false;
}

/**
* Executes the arguments in the data member 'args' using
* C++ system calls. 
*
* @param None.
* @return Bool, representing if the command succeeded in executing
*/
bool Command::execute() {
    if (!(strcmp(args.at(0), (char *)"exit"))) {
        std::exit(EXIT_SUCCESS);
    }
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
