#include "../header/terminate.h"

Terminate::Terminate(Base *left, Base *right) : Connector(left, right) {
}

bool Terminate::execute() {
    bool result1 = left->execute();
    return right->execute();
}
