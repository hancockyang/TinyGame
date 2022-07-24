#ifndef GAMERULE2_H
#define GAMERULE2_H

#include "game.h"

class GameRule2 : public Game
{
public:
    GameRule2();
private:
    void move(bool, bool) override;

    void resetGame() override;

    std::pair<int, int> getEmptyPos() const override;

};

#endif // GAMERULE2_H
