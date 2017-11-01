#ifndef __terminate_h__
#define __terminate_h__

#include "connector.h"

class Terminate : public Connector {
 private:
 	//TODO: Determine if data members are needed.
 public:
 	Terminate();
 	Terminate(Base*, Base*);

    //Executes the left command, and then executes the right command. Returns the result of the right
	bool execute();
	bool isConnector();
};

#endif
