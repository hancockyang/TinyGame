#ifndef GAMERULE2_H
#define GAMERULE2_H

#include "gameinterface.h"

class GameRule2 : public GameInterface
{
public:
    GameRule2();
private:
    void move(bool, bool) override;

    void resetGame() override;

    std::pair<int, int> getEmptyPos() const override;

};

#endif // GAMERULE2_H
