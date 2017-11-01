#ifndef __and_h__
#define __and_h__

#include "connector.h"

class And : public Connector {
 private:
 	//TODO: Determine if more are needed.
 public:
 	And();
 	And(Base*, Base*);
 	bool execute();
	bool isConnector();
};

#endif
