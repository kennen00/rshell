#ifndef __shell_h__
#define __shell_h__

#include <string>
#include <list>
#include <vector>
#include <stack>

#include "base.h"

class Shell {
 private:
 	std::string prompt;
 public:
 	Shell();
 	Shell(std::string);
 	void run();
	std::list<std::string> parse(std::string&);
	Base* buildTree(std::list<std::string>&);
	Base* buildCommand(std::vector<std::string>&);
 private:
 	char* toCstring(const std::string);
	bool  isConnector(const std::string&);
	Base* popAndReturn(std::stack<Base*>&);
    void  buildTree(Base*, std::vector<Base*>);
};

#endif
