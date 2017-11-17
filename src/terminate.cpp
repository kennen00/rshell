#include "../header/terminate.h"

Terminate::Terminate() : Connector(0, 0) {}
Terminate::Terminate(Base *left, Base *right) : Connector(left, right) {
}

/**
* Executes the operands. First it executes the left, then it executes
* the right and returns that value.
*
* @param None.
* @return Bool, representing if the second command succeeded.
*/
bool Terminate::execute() {
    left->execute();
    right->execute();
    return true;
}

/**
* Simple property evaluation function. If the object is a connector, it returns true.
*
* @param None.
* @return Bool, representing if the object is a connector (true)
*/
int Terminate::precedence() {
	return 1;
}
