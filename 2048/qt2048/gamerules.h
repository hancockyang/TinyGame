#ifndef GAMERULES_H
#define GAMERULES_H

#include <vector>

class GameRules
{
public:
    //isRow, isReverse, isWon, isLost, goal, total_score, board
    virtual void play(const bool&, const bool&, bool&, bool&, const int&, const int&, int&, std::vector<std::vector<int>>& )= 0;
};

#endif // GAMERULES_H
