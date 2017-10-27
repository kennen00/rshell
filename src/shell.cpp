#include "../header/shell.h" //Header file
#include "../header/command.h"

#include <boost/tokenizer.hpp> //For Tokenizer parsing

#include <string> 		//For string manipulation
#include <iostream> 	// I/O streams(testing)
#include <list>			// STL list(parsing connected commands)
#include <vector>		// STL vector(building commands)
#include <stdlib.h>		// exit, EXIT_SUCCESS

Shell::Shell(): prompt("$ ") {}
Shell::Shell(std::string prompt): prompt(prompt) {} 

void Shell::run() {
	std::string cmd;
	Base* executableCmd;

	while(1) {
		std::cout << this->prompt;
		std::getline(std::cin, cmd);

		if (cmd == "exit") {
			this->exit();
		}

		executableCmd = this->parse(cmd);
		executableCmd->execute();
	}

	return;
}

void Shell::exit() {
	std::exit(EXIT_SUCCESS);
	return;
}

Base* Shell::parse(std::string &input) {
	std::list<std::string> commands;

	//Remove comments from the command string
	for (size_t i = 0; i < input.size(); ++i) {
		if (input.at(i) == '#') {
			input = input.substr(0, i);
			break;
		}
	}

	return this->buildCommand(input);
}

//Is passed in the unparsed text of the command and 
// returns the build command leaf.

Base* Shell::buildCommand(std::string &input) {
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" ");

	tokenizer tok(input, sep);
	
	std::vector<char*> cmd;

	for (tokenizer::iterator tok_it = tok.begin(); tok_it != tok.end(); ++tok_it) {
		cmd.push_back(toCstring(*tok_it));
	}

	return new Command(cmd);
}

char* Shell::toCstring(const std::string s) {
	char *cstring = new char[s.size()];
	for (size_t i = 0; i < s.size(); ++i) {
		cstring[i] = s.at(i);
	}
	cstring[s.size()] = '\0';

	return cstring;
}
