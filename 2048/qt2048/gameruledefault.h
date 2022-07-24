#ifndef GAMERULEDEFAULT_H
#define GAMERULEDEFAULT_H

#include "game.h"

class GameRuleDefault : public Game
{
public:
    GameRuleDefault();

private:
    void move(bool, bool) override;

    void resetGame() override;

    std::pair<int, int> getEmptyPos() const override;

};

#endif // GAMERULEDEFAULT_H
