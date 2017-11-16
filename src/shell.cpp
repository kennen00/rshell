#include "../header/shell.h" 	//Header files
#include "../header/command.h"
#include "../header/terminate.h"
#include "../header/and.h"
#include "../header/or.h"
#include "../header/base.h"
#include "../header/connector.h"
#include "../header/parenthesis.h"

#include <regex>		// Parsing string input
#include <string> 		// For string manipulation
#include <iostream> 	// I/O streams(testing)
#include <list>			// STL list(parsing connected commands)
#include <vector>		// STL vector(building commands)
#include <stack>		// STL stack(reversing command expression)
#include <stdlib.h>		// exit, EXIT_SUCCESS
#include <stdexcept>	// out_of_range, invalid_input

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

	std::cout << this->prompt;

	while(std::getline(std::cin, cmd)) {
		if (cmd.front() == ' ' || cmd.front() == '#' || cmd.empty()) {
            std::cout << this->prompt;
            continue;
        }

		parsedInput = this->parse(cmd);
		executableCmd = buildTree(parsedInput);
		executableCmd->execute();
        delete executableCmd;

		std::cout << this->prompt;
	}
	return;
}
 
/**
* Parse the user input: remove all comments, replace 
*  test operators [ ] with test command, tokenize
*  input by: spaces, semicolons, and parenthesis.
*
* @param String: User input to the shell prompt.
* @return List of strings: Tokenized input that will be
*			passed to the build tree function.
*/
std::list<std::string> Shell::parse(std::string &input) {
	std::list<std::string> commands;

	//Remove comments from the command string
	size_t index = input.find("#");
	input = input.substr(0, index);

	//Replace test operators with test command ([ -e ... ] -> test -s ...)
	std::regex test("\\[(.+?)\\]");
	std::string replaceString = "test $1";
	input = regex_replace(input, test, replaceString);

	// Tokenize string by spaces and semicolons
	std::regex expr("([;\\(\\)]|[^\\s;\\(\\)]+)");

	std::regex_token_iterator<std::string::iterator> rit{input.begin(), input.end(), expr};
	std::regex_token_iterator<std::string::iterator> rend;

	while (rit != rend) {
		commands.push_back(rit->str());
		rit++;
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
	std::vector<Base*> cmds;
	short parenthesisCount = 0;

	while (!commands.empty()) {
		std::vector<std::string> cmd;

		while (!isConnector(commands.front()) && !commands.empty()) {
			cmd.push_back(commands.front());
			commands.pop_front();
		}

		if (!cmd.empty()) {
			cmds.push_back(this->buildCommand(cmd));
		} else if (commands.front() == ";") {
			cmds.push_back(new Terminate()); 
			commands.pop_front();
		} else if (commands.front() == "||") {
			cmds.push_back(new Or()); 
			commands.pop_front();
		} else if (commands.front() == "&&") {
			cmds.push_back(new And()); 
			commands.pop_front();
		} else if (commands.front() == "(") {
			cmds.push_back(new openParen());
			commands.pop_front();
			parenthesisCount++;
		} else if (commands.front() == ")") {
			cmds.push_back(new closeParen());
			commands.pop_front();
			parenthesisCount--;
		}
	}
	
	if (parenthesisCount != 0) {
		std::cout << "Error: Uneven parenthesis" << std::endl;
		run();
	}

	//Arrange the commands to be in postfix notations
	std::stack<Base*> connectorStack;
	std::vector<Base*> postfix;

	for (size_t i = 0; i < cmds.size(); ++i) {
		if (cmds.at(i)->precedence() == 3) { //Cmd is a opening parenthesis
			connectorStack.push(cmds.at(i));
		} else if (cmds.at(i)->precedence() == 2) { //Cmd is a closing parenthesis
			while (!connectorStack.empty() && connectorStack.top()->precedence() != 3) {
				postfix.push_back(connectorStack.top());
				connectorStack.pop();
			}
			connectorStack.pop();
			
		} else if (cmds.at(i)->precedence() == 1) { //Cmd is a connector
			if (connectorStack.empty()) {
				connectorStack.push(cmds.at(i));
			} else {
				if (connectorStack.top()->precedence() == 3) {
					connectorStack.push(cmds.at(i));
				} else {
					postfix.push_back(connectorStack.top());
					connectorStack.pop();
					connectorStack.push(cmds.at(i));
				}
			}
		} else if (cmds.at(i)->precedence() == 0) { //Cmd is a command
			postfix.push_back(cmds.at(i));
		}
	}
	
	while (!connectorStack.empty()) {
		postfix.push_back(connectorStack.top());
		connectorStack.pop();
	}

	//Build the expression tree from the postfix notation
	Base* tree = 0;// = postfix.at(postfix.size() - 1);

	try {

    	std::stack<Base *> stack;
    	for (size_t i = 0; i < postfix.size(); ++i) {
    	    if (postfix.at(i)->precedence() == 1) {
        	    Base *right = stack.top();
        	    stack.pop();
        	    Base *left = stack.top();
        	    stack.pop();
        	    Connector *connector = static_cast<Connector*>(postfix.at(i));

				if (!left || !right || !connector) {
					throw std::invalid_argument("Missing arguments");
				}

				connector->setLeft(left);
        	    connector->setRight(right);
        	    stack.push(connector);

        	} else {
            	stack.push(postfix.at(i));
        	}
    	}
    	tree = stack.top();

	} catch (const std::exception& e) {
		std::cerr << "Error: Connector used with not enough arguments\n";
		run();
	}
   
	return tree;
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
		size_t index = input.at(i).find("\"");
		if (index <= input.at(i).size()) 
			input.at(i).erase(index, 1);

		index = input.at(i).find("\"");
		if (index <= input.at(i).size()) 
			input.at(i).erase(index, 1);

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
	char *cstring = new char[s.size() + 1];
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
	v.push_back("(");
	v.push_back(")");

	for (size_t i = 0; i < v.size(); ++i) {
		if (v.at(i) == s) {
			return true;
		}
	}
	return false;
}

Base* Shell::popAndReturn(std::stack<Base*>& s) {
	if (!s.empty()) {
		Base* returnVal = s.top();
		s.pop();

		return returnVal;
	}

	return 0;
}
