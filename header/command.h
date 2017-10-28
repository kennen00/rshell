#ifndef __COMMAND_H__
#define __COMMAND_H__

//#include <string>
#include <vector>

#include "base.h"

class Command : public Base {
    private: 
        //Vector of arguments to be executed
        std::vector<char *> args;
    public:
        //Constructor that passes in a vector of arguments
        Command(std::vector<char *>);

        //Executes the arguments in args using syscalls
        bool execute();
};

#endif
