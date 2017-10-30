#include "../header/terminate.h"

Terminate::Terminate(Base *left, Base *right) : Connector(left, right) {
}

bool Terminate::execute() {
    left->execute();
    return right->execute();
}
