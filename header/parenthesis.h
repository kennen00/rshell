#ifndef __parenthesis_h__
#define __parenthesis_h__

#include "base.h"

class openParen : public Base {
 private:
 	// Determine if private data members are needed.
 public:
 	openParen();
	bool execute();
	int precedence();
};

class closeParen: public Base {
 private:
 	// Determine if private data members are needed.
 public:
 	closeParen();
	bool execute();
	int precedence();
};

#endif
