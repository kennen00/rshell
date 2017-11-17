#include "../header/or.h"

Or::Or() : Connector(0, 0) {}
Or::Or(Base *left, Base *right) : Connector(left, right) {
}

/**
* Executes the operands. If the left fails to execute, then the
* right executes. Otherwise, it returns false.
*
* @param None.
* @return Bool, representing if the operator succeeded in executing
*/
bool Or::execute() {
    if (!left->execute()) {
        return right->execute();
    }
    return true;
}

/**
* Simple property evaluation function. Returns true if the object is a connector.
*
* @param None.
* @return Bool, true if the object is a connector (true)
*/
int Or::precedence() {
	return 1;
}
