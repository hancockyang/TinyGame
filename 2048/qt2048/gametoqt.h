#ifndef GAMETOQT_H
#define GAMETOQT_H

#include "subjectinterface.h"
#include "observerinterface.h"
#include "game.h"

class GameToQt : protected Game, public SubjectInterface, public ObserverInterface2
{
public:
    explicit GameToQt(int );
    GameToQt();
    GameToQt(int, int);
    void init();
    //interface:

    void add(ObserverInterface*) override;

    void notify(const int&, const std::vector<std::vector<int>>&, const bool&, const bool&) const override;

    void update(const char& ) override;

    //void setBoard(const int, const int) const override;

private:
    std::vector<ObserverInterface*> observers;

};

#endif // GAMETOQT_H
