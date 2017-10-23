#include <iostream>

#include "../header/command.h"

int main() {
    std::vector<char *> args;
    args.push_back((char *)"ls");
    //args.push_back((char *)"-al");
    //args.push_back((char *)"-l");
    bool success = false;
    
    Base *command = new Command(args);
    success = command->execute();
    std::cout << success << std::endl;

    return 0;
}
