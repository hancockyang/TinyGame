#ifndef GAMETOQT_H
#define GAMETOQT_H

#include "subjectinterface.h"
#include "observerinterface.h"
#include "game.h"
#include <memory>

class GameToQt : public SubjectInterface, public ObserverInterface2
{
public:
    explicit GameToQt(int method = 0);

    void init();
    //interface:

    void add(ObserverInterface*) override;

    void notify(const int&, const std::vector<std::vector<int>>&, const bool&, const bool&) const override;

    void update(const char& ) override;

private:
    std::unique_ptr<Game> gptr;

};

#endif // GAMETOQT_H
