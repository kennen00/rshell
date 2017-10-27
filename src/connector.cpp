#include "../header/connector.h"

Connector::Connector(Base *left, Base *right) : left(left), right(right) {
}

Connector::~Connector() {
    delete left;
    delete right;
}

void Connector::setLeft(Base *left) {
    this->left = left;
}

void Connector::setRight(Base *right) {
    this->right = right;
}
