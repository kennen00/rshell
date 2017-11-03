#ifndef __connector_h__
#define __connector_h__

#include "base.h"

class Connector : public Base {
 protected:
    //Left command of the connector
 	Base* left;

    //Right command of the connector
	Base* right;
 public:
 	Connector(Base*, Base*);
	virtual bool execute() = 0;
	virtual bool isConnector() = 0;
    virtual void setLeft(Base *);
    virtual void setRight(Base *);
};

#endif
