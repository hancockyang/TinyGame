#include "gameruledefault.h"
#include <algorithm>
#include <cstring>
#include <vector>
GameRuleDefault::GameRuleDefault() : GameInterface(){};


std::pair<int, int> GameRuleDefault::getEmptyPos () const
{
    int i, j;
    do {
        i = rand() % NCells;
        j = rand() % NCells;
    } while (board[i][j]);
    return {i, j};
}

void GameRuleDefault::resetGame(){
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

void GameRuleDefault::move(bool isRow, bool isReverse){
    using Vec = std::vector<int>;
    auto squeezeVec = [&] (Vec& v) {
        if (isReverse) v = Vec(v.rbegin(), v.rend());
        Vec ans; size_t i = 0;
        while (i + 1 < v.size()) {
            if (v[i] == v[i + 1]) {
                total_score += v[i] * 2;
                isWon = (v[i] * 2 == goal);
                ans.push_back(v[i] * 2);
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
