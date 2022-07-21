#ifndef OBSERVERINTERFACE_H
#define OBSERVERINTERFACE_H

#include <vector>
#include <string>

class ObserverInterface{
public:
    virtual void update(const int&, const std::vector<std::vector<int>>&, const bool&, const bool&) = 0;
    //virtual void update(T, U) = 0;
    //virtual void update(std::string& ) = 0;

    virtual ~ObserverInterface(){}
};

class ObserverInterface2{
public:
    virtual void update(const char& ) = 0;

    virtual ~ObserverInterface2(){}
};


#endif // OBSERVERINTERFACE_H