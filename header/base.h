#ifndef __BASE_H__
#define __BASE_H__

class Base {
    public:
        virtual bool execute() = 0;
		virtual bool isConnector() = 0;
};

#endif
