#ifndef GAME_H
#define GAME_H
#include <vector>
#include "subjectinterface.h"
#include "observerinterface.h"
const int NCells = 4;


class Game : public SubjectInterface, public ObserverInterface2
{
public:
    std::vector<std::vector<int>> board;

    int total_score;
    bool isWon, isLost;

    Game();

    void move(bool, bool);

    void resetGame();

    std::pair<int, int> getEmptyPos() const;

    bool isFull() const;

    bool isDead() const;

    //interface:

    void add(ObserverInterface*) override;

    void notify(const int&, const std::vector<std::vector<int>>&, const bool&, const bool&) const override;

    void update(const char& ) override;
    //void notify(T, U) const override;



//private:
    std::vector<ObserverInterface*> observers;

};


#endif // GAME_H
