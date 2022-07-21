#ifndef SUBJECTINTERFACE_H
#define SUBJECTINTERFACE_H

#include <vector>

#include <memory>
#include "observerinterface.h"


class SubjectInterface{
public:
    virtual void add(ObserverInterface* ) = 0;
    //virtual void remove(ObserverInterface* obr) = 0;
    virtual void notify(const int&, const std::vector<std::vector<int>>&, const bool&, const bool&) const = 0;
    //virtual void notify(T, U) const = 0;
    //virtual void notify(std::string& ) const = 0;

    virtual ~SubjectInterface(){}
};


class SubjectInterface2{
public:
    virtual void add(ObserverInterface2*) = 0;
    //virtual void remove(ObserverInterface* obr) = 0;
    virtual void notify(const char& ) const = 0;

    virtual ~SubjectInterface2(){}
};

#endif // SUBJECTINTERFACE_H
