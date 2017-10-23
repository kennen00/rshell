#ifndef __COMMAND_H__
#define __COMMAND_H__

//#include <string>
#include <vector>

#include "base.h"

class Command : public Base {
    private:   
        std::vector<char *> args;
    public:
        Command(std::vector<char *>);
        bool execute();
};

#endif
