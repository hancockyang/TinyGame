#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H
#include <vector>
class GameInterface
{
public:


    GameInterface();

    virtual void move(bool, bool) = 0;

    virtual void resetGame() = 0;

    virtual std::pair<int, int> getEmptyPos() const = 0;

    virtual ~GameInterface();

    int total_score;
    bool isWon, isLost;

    int NCells, goal;

    std::vector<std::vector<int>> board;

};


#endif // GAMEINTERFACE_H
