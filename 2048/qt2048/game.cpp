#include <algorithm>
#include <cstring>
#include <vector>
#include "game.h"

Game::Game():
    board{std::vector<std::vector<int>>(4, std::vector<int>(4))},
    total_score(0),
    NCells(4),
    goal(2048),
    isWon(false),
    isLost(false){}

Game::Game(int _size):
    board{std::vector<std::vector<int>>(_size, std::vector<int>(_size))},
    total_score(0),
    NCells(_size),
    goal(2048),
    isWon(false),
    isLost(false) {}

Game::Game(int _size, int _goal):
    board{std::vector<std::vector<int>>(_size, std::vector<int>(_size))},
    total_score(0),
    NCells(_size),
    goal(_goal),
    isWon(false),
    isLost(false) {}

Game::~Game(){};

std::pair<int, int> Game::getEmptyPos () const
{
    int i, j;
    do {
        i = rand() % NCells;
        j = rand() % NCells;
    } while (board[i][j]);
    return {i, j};
}

void Game::resetGame(){
    for (int i = 0; i < NCells; ++i){
        for (int j = 0; j < NCells; ++j){
            board[i][j] = 0;
        }
    }

    board[rand() % NCells][rand() % NCells] = 2;
    auto pos = getEmptyPos();
    board[pos.first][pos.second] = 2;

    total_score = 0; isWon = false; isLost = false;


}


void Game::move(bool isRow, bool isReverse)
{
    using Vec = std::vector<int>;
    auto squeezeVec = [&] (Vec& v) {
        if (isReverse) v = Vec(v.rbegin(), v.rend());
        Vec ans; size_t i = 0;
        while (i + 1 < v.size()) {
            if (v[i] == v[i + 1]) {
                total_score += v[i] * 2;
                ans.push_back(v[i] * 2);
                isWon = (ans.back() == 2048);
                i += 2;
            }
            else{
                ans.push_back(v[i++]);
            }
        }
        if (i + 1 == v.size()) ans.push_back(v[i]);
        while (ans.size() < (unsigned int)NCells){
            ans.push_back(0);
        }
        return isReverse ? Vec(ans.rbegin(), ans.rend()) : ans;
    };

    auto getVal = [&] (int i, int j){
        return isRow ? board[i][j] : board[j][i];
    };
    auto setVal = [&] (int i, int j) -> int& {
        return isRow ? board[i][j] : board[j][i];
    };

    for (int i = 0; i < NCells; ++i) {
        Vec v;
        for (int j = 0; j < NCells; ++j) {
            if (getVal(i, j)) v.push_back(getVal(i, j));
        }
        auto ans = squeezeVec(v);
        for (int j = 0; j < NCells; ++j) {
            setVal(i, j) = ans[j];
        }
    }

    auto isDead = [&](){
        std::vector<std::vector<int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        for (int i = 0; i < NCells; ++i){
            for (int j = 0; j < NCells; ++j){
                for (const auto& dir : dirs){
                    int newI = i + dir[0];
                    int newJ = j + dir[1];
                    if (newI < 0 || newI == NCells || newJ < 0 || newJ == NCells){
                        continue;
                    }
                    if (board[i][j] == board[newI][newJ] || board[i][j] == 0 || board[newI][newJ] == 0){
                        return false;
                    }
                }
            }
        }
        return true;
    };

    auto isFull = [&]()
    {
        for (int i = 0; i < NCells; ++i){
            for (int j = 0; j < NCells; ++j){
                if (board[i][j] == 0){
                    return false;
                }
            }
        }
        return true;
    };

    if (!isFull() && !isWon) {
        auto pos = getEmptyPos();
        board[pos.first][pos.second] = 2;
    }

    if (isDead() && !isWon){
        isLost = true;
    }


}


