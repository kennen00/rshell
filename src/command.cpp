#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "../header/command.h"

Command::Command(std::vector<char *> args) : args(args) {
    this->args.push_back((char *) 0);
}

Command::~Command() {
    for (unsigned int i = 0; i < args.size() - 1; ++i) {
        delete[] args.at(i);
    }
}

/**
* Simple property evaluation function. Returns true if the
* object is a connector.
*
* @param None.
* @return Int, representing if the object is a connector (false)
*/
int Command::precedence() {
	return 0;
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
        if (!(strcmp(args.at(0), (char *)"test"))) {
            return test();
        }
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

char* Command::getFirst() {
    return args.at(0);
}

bool Command::test() {
    if (!args.at(1)) {
        exit(1);
        return false;
    }
    struct stat sb;
    if (!(strcmp(args.at(1), (char *) "-e"))) {
        int error = stat(args.at(2), &sb);
        if (error) {
            if (errno == ENOENT) {
                std::cout << "(False)" << std::endl;
            } else {
                perror("stat");
            }
            exit(1);
            return false;
        }
        std::cout << "(True)" << std::endl;
    } else if (!(strcmp(args.at(1), (char *) "-f"))) {
        int error = stat(args.at(2), &sb);
        if (error) {
            if (errno == ENOENT) {
                std::cout << "(False)" << std::endl;
            } else {
                perror("stat");
            }
            exit(1);
            return false;
        }
        if (S_ISREG(sb.st_mode)) {
            std::cout << "(True)" << std::endl;
        } else {
            std::cout << "(False)" << std::endl;
            exit(1);
            return false;
        }
    } else if (!(strcmp(args.at(1), (char *) "-d"))) {
        int error = stat(args.at(2), &sb);
        if (error) {
            if (errno == ENOENT) {
                std::cout << "(False)" << std::endl;
            } else {
                perror("stat");
            }
            exit(1);
            return false;
        }
        if (S_ISDIR(sb.st_mode)) {
            std::cout << "(True)" << std::endl;
        } else {
            std::cout << "(False)" << std::endl;
            exit(1);
            return false;
        }
    } else {
        int error = stat(args.at(1), &sb);
        if (error) {
            if (errno == ENOENT) {
                std::cout << "(False)" << std::endl;
            } else {
                perror("stat");
            }
            exit(1);
            return false;
        }
        std::cout << "(True)" << std::endl;
    }
    exit(0);
    return true;
}
