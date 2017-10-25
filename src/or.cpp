#include "../header/or.h"

Or::Or(Base *left, Base *right) : Connector(left, right) {
}

bool Or::execute() {
    if (!left->execute()) {
        return right->execute();
    }
    return false;
}
