#ifndef __BASE_H__
#define __BASE_H__

//Abstract class that commands and connectors inherit from
class Base {
    public:
        virtual ~Base() {}
        virtual bool execute() = 0;
		virtual bool isConnector() = 0;
};

#endif
