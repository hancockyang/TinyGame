#ifndef GAME_H
#define GAME_H
#include <vector>

class Game
{
public:


    explicit Game(int);
    Game();
    Game(int , int);

    virtual ~Game();

protected:
    std::vector<std::vector<int>> board;

    int total_score, NCells, goal;
    bool isWon, isLost;

    void move(bool, bool);

    void resetGame();

    std::pair<int, int> getEmptyPos() const;

};


#endif // GAME_H
