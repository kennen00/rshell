#ifndef __or_h__
#define __or_h__

#include "connector.h"

class Or : public Connector {
 private:
 	//TODO: Determine if more are needed.
 public:
 	Or();
 	Or(Base*, Base*);
 	bool execute();
	int precedence();
};

#endif
