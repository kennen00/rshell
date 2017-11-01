#include "../header/shell.h" 	//Header files
#include "../header/command.h"
#include "../header/terminate.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/base.h"
#include "../header/connector.h"

#include <boost/tokenizer.hpp> //For Tokenizer parsing

#include <string> 		//For string manipulation
#include <iostream> 	// I/O streams(testing)
#include <list>			// STL list(parsing connected commands)
#include <vector>		// STL vector(building commands)
#include <stack>		// STL stack(reversing command expression)
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
	std::list<std::string> parsedInput;
	Base* executableCmd;

	while(1) {
		std::cout << this->prompt;
		std::getline(std::cin, cmd);

		if (cmd == "exit") {
			this->exit();
		}

		parsedInput = this->parse(cmd);
		executableCmd = buildTree(parsedInput);
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
std::list<std::string> Shell::parse(std::string &input) {
	std::list<std::string> commands;

	//Remove comments from the command string
	for (size_t i = 0; i < input.size(); ++i) {
		if (input.at(i) == '#') {
			input = input.substr(0, i);
			break;
		}
	}

	// Tokenize string by spaces
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" ");

	tokenizer tok(input, sep);

	for (tokenizer::iterator tok_it = tok.begin(); tok_it != tok.end(); ++tok_it) {
		commands.push_back(*tok_it);
	}

	for (std::list<std::string>::iterator it = commands.begin(); it != commands.end(); ++it) {
		if (it->back() == ';' && (it->size() > 1)) {
			it->pop_back();
			++it;
			commands.insert(it, ";");
		}
	}

	return commands;
}


/**
* Take the parsed input and build the expression tree using the
*  shunting-yard algorithm for an expression tree
*
* @param STL list<string> that was returned by the parse function
* @return Base*: Point to root of command expression tree.
*/
Base* Shell::buildTree(std::list<std::string>& commands) {
	std::stack<Base*> stack;

	while (!commands.empty()) {
		std::vector<std::string> cmd;

		while (!isConnector(commands.front()) && !commands.empty()) {
			cmd.push_back(commands.front());
			commands.pop_front();
		}

		if (!cmd.empty()) {
			stack.push(this->buildCommand(cmd));
		} else if (commands.front() == ";") {
			stack.push(new Terminate()); 
			commands.pop_front();
		} else if (commands.front() == "||") {
			stack.push(new Or()); 
			commands.pop_front();
		} else if (commands.front() == "&&") {
			stack.push(new And()); 
			commands.pop_front();
		}
	}

	//Reverse the commands so that the tree is correct
	std::vector<Base*> reversedCmds;

	while(!stack.empty()) {
		reversedCmds.push_back(stack.top());
		stack.pop();
	}

	//Arrange the commands to be in postfix notations
	std::stack<Base*> connectorStack;
	std::vector<Base*> postfix;

	for (size_t i = 0; i < reversedCmds.size(); ++i) {
		if (reversedCmds.at(i)->isConnector()) {
			if (connectorStack.empty()) {
				connectorStack.push(reversedCmds.at(i));
			} else {
				postfix.push_back(connectorStack.top());
				connectorStack.pop();
				connectorStack.push(reversedCmds.at(i));
			}
		} else {
			postfix.push_back(reversedCmds.at(i));
		}

		if (i == reversedCmds.size() - 1) {
			if (!connectorStack.empty()) {
				postfix.push_back(connectorStack.top());
			}
		}
	}

	//Build the expression tree from the postfix notation
	std::stack<Base*> tree;

	for (size_t i = 0; i < postfix.size(); ++i) {
		if (postfix.at(i)->isConnector()) {
			Base* left = tree.top();
			tree.pop();
			Base* right = tree.top();
			tree.pop();
			
			Connector* connector = static_cast<Connector*>(postfix.at(i));
			connector->setLeft(left);
			connector->setRight(right);

			tree.push(connector);
		} else {
			tree.push(postfix.at(i));
		}
	}

	return tree.top();
}


/**
* Build a single command leaf that is dynamically allocated,
*  and return that to be used in either simple or more complex
*  experssion trees.
*
* @param String: String for one single command.
* @return Base*: Pointer to command leaf to corresponding input.
*/
Base* Shell::buildCommand(std::vector<std::string> &input) {
	std::vector<char *> cmd;

	for (size_t i = 0; i < input.size(); ++i) {
		cmd.push_back(toCstring(input.at(i)));
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

/**
* Take an STL string and compare it to the list
*  of known connection classes.
*
* @param String: C++ String class that is to be compared.
* @return Bool;  Logial result of if the input is in the list.
*/
bool Shell::isConnector(const std::string& s) {
	std::vector<std::string> v;

	v.push_back(";");
	v.push_back("&&");
	v.push_back("||");

	for (size_t i = 0; i < v.size(); ++i) {
		if (v.at(i) == s) {
			return true;
		}
	}
	return false;
}
