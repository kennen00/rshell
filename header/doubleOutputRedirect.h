#ifndef __doubleOutputRedirect_h__
#define __doubleOutputRedirect_h__

#include "connector.h"

class DoubleOutputRedirect : public Connector {
 private:
 	//TODO: Determine if more are needed.
 public:
 	DoubleOutputRedirect();
 	DoubleOutputRedirect(Base*, Base*);
 	bool execute();
	int precedence();
};

#endif
