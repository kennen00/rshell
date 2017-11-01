#include "../header/terminate.h"

Terminate::Terminate() : Connector(0, 0) {}
Terminate::Terminate(Base *left, Base *right) : Connector(left, right) {
}

bool Terminate::execute() {
    left->execute();
    return right->execute();
}

bool Terminate::isConnector() {
	return true;
}
