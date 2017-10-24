#ifndef __shell_h__
#define __shell_h__

#include <string>

#include "base.h"

class Shell {
 private:
 	std::string prompt;
 public:
 	Shell();
 	Shell(std::string);
 	void run();
	void exit();
	Base* parse(std::string&);
};

#endif
