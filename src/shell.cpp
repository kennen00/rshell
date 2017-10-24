#include "../header/shell.h" //Header file

#include <string> //For string manipulation
#include <boost/tokenizer.hpp> //For Tokenizer parsing

#include <iostream> //For Testing
#include <list>

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

	for (auto it = commands.begin(); it != commands.end(); ++it) {

		if (it->back() == ';') {
			//Remove semicolon and add to list immediately after command
			it->pop_back();
			++it;
			commands.insert(it, ";");
		}
	}
	

	for (auto it = commands.begin(); it != commands.end(); ++it) {
		std::cout << '<' << *it << "> ";
	}

	std::cout << std::endl;

	return 0;
}
