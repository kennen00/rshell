#include "../header/connector.h"

Connector::Connector(Base *left, Base *right) : left(left), right(right) {
}

bool Connector::isConnector() {
	return true;
}

void Connector::setLeft(Base *left) {
    this->left = left;
}

void Connector::setRight(Base *right) {
    this->right = right;
}
