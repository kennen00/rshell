#ifndef __connector_h__
#define __connector_h__

#include "base.h"

class Connector : public Base {
 protected:
 	Base* left;
	Base* right;
 public:
 	Connector(Base*, Base*);
    virtual ~Connector();
	virtual bool execute() = 0;
};

#endif
