#ifndef __BASE_H__
#define __BASE_H__

//Abstract class that commands and connectors inherit from
class Base {
    public:
        //Inherited method used by commands and connectors
        virtual bool execute() = 0;
};

#endif
