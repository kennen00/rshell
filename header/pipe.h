#ifndef __pipe_h__
#define __pipe_h__

#include "connector.h"

class Pipe : public Connector {
 private:
 	//TODO: Determine if more are needed.
 public:
 	Pipe();
 	Pipe(Base*, Base*);
 	bool execute();
	int precedence();
};

#endif
