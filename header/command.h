#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <vector>

#include "base.h"

class Command : public Base {
    private: 
        //Vector of arguments to be executed
        std::vector<char *> args;
    public:
        Command(std::vector<char *>);
        ~Command();
        bool execute();
		bool isConnector();
    private:
        bool test();
};

#endif
