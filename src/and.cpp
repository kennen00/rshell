#include "../header/and.h"

And::And() : Connector(0,0) {}
And::And(Base *left, Base *right) : Connector(left, right) {
}

bool And::execute() {
    if (left->execute()) {
        return right->execute();
    }
    return false;
}

bool And::isConnector() {
	return true;
}
