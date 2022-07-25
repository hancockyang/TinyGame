#ifndef GAMETOQT_H
#define GAMETOQT_H

#include "subjectinterface.h"
#include "observerinterface.h"
#include "gameinterface.h"
#include <memory>

class GameToQt : public SubjectInterface, public ObserverInterface2
{
public:
    explicit GameToQt(std::unique_ptr<GameInterface>);

    void init();
    //interface:

    void add(ObserverInterface*) override;

    void notify(const int&, const std::vector<std::vector<int>>&, const bool&, const bool&) const override;

    void update(const char& ) override;

private:
    std::unique_ptr<GameInterface> gptr;

};

#endif // GAMETOQT_H
