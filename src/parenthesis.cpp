#include "../header/parenthesis.h"

openParen::openParen() {}

bool openParen::execute() {
	return false;
}

int openParen::precedence() {
	return 3;
}

closeParen::closeParen() {}

bool closeParen::execute() {
	return false;
}

int closeParen::precedence() {
	return 2;
}
