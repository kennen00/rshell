//Used by Kennen to test the execution of commands

#include <iostream>

#include "../header/command.h"
#include "../header/terminate.h"
#include "../header/or.h"
#include "../header/and.h"

int main() {
    std::vector<char *> args, args1;
    args.push_back((char *)"ls");
    args1.push_back((char *)"ls");
    args.push_back((char *)"-al");
    args1.push_back((char *)"-l");
    bool success = false;
    
    Base *left = new Command(args);
    Base *right = new Command(args1);
    Base *command = new Terminate(left, right);
    Base *command1 = new And(left, right);
    Base *command2 = new Or(left, right);
    success = command->execute();
    std::cout << success << std::endl;
    success = command1->execute();
    std::cout << success << std::endl;
    success = command2->execute();
    std::cout << success << std::endl;

    return 0;
}
