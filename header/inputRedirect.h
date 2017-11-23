#ifndef __inputRedirect_h__
#define __inputRedirect_h__

#include "connector.h"

class InputRedirect : public Connector {
 private:
 	//TODO: Determine if more are needed.
 public:
 	InputRedirect();
 	InputRedirect(Base*, Base*);
 	bool execute();
	int precedence();
};

#endif
