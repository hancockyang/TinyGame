#include <algorithm>
#include <cstring>
#include <vector>
#include "game.h"

Game::Game():
    total_score(0),
    isWon(false),
    isLost(false),
    NCells(4),
    goal(2048),
    board{std::vector<std::vector<int>>(4, std::vector<int>(4))}{}



Game::~Game(){};


