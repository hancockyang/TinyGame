#ifndef GAMERULEDEFAULT_H
#define GAMERULEDEFAULT_H

#include "gameinterface.h"

class GameRuleDefault : public GameInterface
{
public:
    GameRuleDefault();

private:
    void move(bool, bool) override;

    void resetGame() override;

    std::pair<int, int> getEmptyPos() const override;

};

#endif // GAMERULEDEFAULT_H
