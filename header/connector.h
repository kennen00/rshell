#ifndef __conector_h__
#define __connector_h__

#include "base.h"

class Connector : public Base {
 private:
 	Base* left;
	Base* right;
 public:
 	Connector(Base*, Base*);
	virtual bool execute() = 0;
};
