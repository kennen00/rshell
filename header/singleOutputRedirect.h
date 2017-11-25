#ifndef __singleOutputRedirect_h__
#define __singleOutputRedirect_h__

#include "connector.h"

class SingleOutputRedirect : public Connector {
 private:
 	//TODO: Determine if more are needed.
 public:
 	SingleOutputRedirect();
 	SingleOutputRedirect(Base*, Base*);
 	bool execute();
	int precedence();
};

#endif
