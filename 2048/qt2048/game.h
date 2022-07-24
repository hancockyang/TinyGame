#ifndef GAME_H
#define GAME_H
#include <vector>
class Game
{
public:


    Game();

    virtual void move(bool, bool) = 0;

    virtual void resetGame() = 0;

    virtual std::pair<int, int> getEmptyPos() const = 0;

    virtual ~Game();

    int total_score;
    bool isWon, isLost;

    int NCells, goal;

    std::vector<std::vector<int>> board;

};


#endif // GAME_H
