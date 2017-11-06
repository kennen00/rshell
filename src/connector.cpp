#include "../header/connector.h"

Connector::Connector(Base *left, Base *right) : left(left), right(right) {
}

/**
* Simple property evaluation function. Returns true if object is a connector.
*
* @param None.
* @return Bool, representing if the object is a connector (true)
*/
bool Connector::isConnector() {
	return true;
}

void Connector::setLeft(Base *left) {
    this->left = left;
}

void Connector::setRight(Base *right) {
    this->right = right;
}
