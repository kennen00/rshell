#include "../header/connector.h"

Connector::Connector(Base *left, Base *right) : left(left), right(right) {
}

Connector::~Connector() {
    delete left;
    delete right;
}

Connector::setLeft(Base *left) {
    this->left = left;
}

Connector::setRight(Base *right) {
    this->right = right;
}
