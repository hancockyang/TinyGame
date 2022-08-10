#ifndef SUBJECTINTERFACE_H
#define SUBJECTINTERFACE_H

#include <vector>
#include "observerinterface.h"
#include <memory>

class SubjectInterface{
public:
    virtual void add(ObserverInterface* ) = 0;

    virtual void notify(const int&, const std::vector<std::vector<int>>&, const bool&, const bool&) const = 0;

    //virtual void setBoard(const int, const int) const = 0;

    virtual ~SubjectInterface(){}
protected:
    std::vector<ObserverInterface*> observers;
};


class SubjectInterface2{
public:
    virtual void add(std::shared_ptr<ObserverInterface2>) = 0;

    virtual void notify(const char& ) const = 0;

    virtual ~SubjectInterface2(){}

protected:
    std::vector<std::shared_ptr<ObserverInterface2>> observers;


};

#endif // SUBJECTINTERFACE_H
