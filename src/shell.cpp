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

/**
* The main execution loop that displays prompts, and calls all 
*  necesary functions to ensure constant execution of the
*  rshell.
*
* @param None.
* @return Nothing, exits before return.
*/
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

/**
* Special exit command that exists the shell w/o an error code.
*
* @param None.
* @return Nothing, exits before return.
*/
void Shell::exit() {
	std::exit(EXIT_SUCCESS);
	return;
}

/**
* Parse the user input, build command expression tree and return
* the root node pointer.
*
* @param String: User input to the shell prompt.
* @return Base*: Point to root of command expression tree.
*/
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

/**
* Build a single command leaf that is dynamically allocated,
*  and return that to be used in either simple or more complex
*  experssion trees.
*
* @param String: String for one single command.
* @return Base*: Pointer to command leaf to corresponding input.
*/
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

/**
* Convert a STL string into a C-String which is accepted by 
*  the command class for executeable objects.
*
* @param String: C++ String class that is to be converted.
* @return Char*: C-string for the correspond string.
*/
char* Shell::toCstring(const std::string s) {
	char *cstring = new char[s.size()];
	for (size_t i = 0; i < s.size(); ++i) {
		cstring[i] = s.at(i);
	}
	cstring[s.size()] = '\0';

	return cstring;
}
