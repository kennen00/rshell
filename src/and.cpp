#include "../header/and.h"

And::And() : Connector(0,0) {}
And::And(Base *left, Base *right) : Connector(left, right) {
}

/**
* The main execution function for the and connector.
* If the left command evaluates to true, then the right
* command is executed. Otherwise, it returns false.
*
* @param None.
* @return Bool, representing if execution succeeded or not
*/
bool And::execute() {
    if (left->execute()) {
        return right->execute();
    }
    return false;
}
/**
* Simple property evaluation function.
*
* @param None.
* @return Bool, represting if the object is a connector (true)
*/
bool And::isConnector() {
	return true;
}
