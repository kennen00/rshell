#ifndef __or_h__
#define __or_h__

#include "connector.h"

class Or : public Connector {
 private:
 	//TODO: Determine if more are needed.
 public:
 	Or();
 	Or(Base*, Base*);

    //Executes the left command. If it fails, executes the right command and returns that result
 	bool execute();
};

#endif
