#include "../header/shell.h" //Header file
#include "../header/command.h"

#include <string> //For string manipulation
#include <boost/tokenizer.hpp> //For Tokenizer parsing

#include <iostream> //For Testing
#include <list>
#include <vector> 

Shell::Shell(): prompt("$ ") {}
Shell::Shell(std::string prompt): prompt(prompt) {} 
void Shell::run() {
	std::string cmd;
	Base* executableCmd;

	while(1) {
		std::cout << this->prompt;
		std::getline(std::cin, cmd);
		executableCmd = this->parse(cmd);
	}

	return;
}

void Shell::exit() {
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

	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" ");
	
	tokenizer tok(input, sep);

	//Fills vector with commands tokenized by spaces
	for (tokenizer::iterator tok_iter = tok.begin(); tok_iter != tok.end(); ++tok_iter) {
		commands.push_back(*tok_iter);
	}

	//Break the ending semicolons off of strings and leaves them as seperate tokens.
	for (auto it = commands.begin(); it != commands.end(); ++it) {
		if (it->back() == ';' && (it->size() > 1)) {
			//Remove semicolon and add to list immediately after command
			it->pop_back();
			++it;
			commands.insert(it, ";");
		}
	}
	
	return 0;
}

//Is passed in the unparsed text of the command and 
// returns the build command leaf.
//
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

char* Shell::toCstring(const std::string& s) {
	char cstring[s.size()];
	for (size_t i = 0; i < s.size(); ++i) {
		cstring[i] = s.at(i);
	}
	cstring[s.size()] = '\0';

	return cstring;
}












