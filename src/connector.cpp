#include "../header/connector.h"

Connector::Connector(Base *left, Base *right) : left(left), right(right) {
}

Connector::~Connector() {
    delete left;
    delete right;
}
