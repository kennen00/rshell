#include "../header/or.h"

Or::Or() : Connector(0, 0) {}
Or::Or(Base *left, Base *right) : Connector(left, right) {
}

bool Or::execute() {
    if (!left->execute()) {
        return right->execute();
    }
    return false;
}
