#define _CRT_SECURE_NO_WARNING

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <vector>
#include <iostream>
#include <algorithm>


enum Direction {
    LEFT = 1,
    UP,
    RIGHT,
    DOWN,
} dirs;


int spawnNewBlock(std::vector<std::vector<int>>& panel){
    
    int haveBlank = 0;

    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            if (panel[i][j] == 0){
                haveBlank = 1;
            }
        }
    }

    if (haveBlank == 0){
        return 0;
    }

    int i, j;
    do {
        j = rand() % 4;
        i = rand() % 4;
    } while (panel[i][j] != 0);

    panel[i][j] = 2;

    return 1;

}

void printNumber(int number){
    int color;

    switch (number)
    {
    case 2:
        color = 32;
        break;
    case 4:
        color = 33;
        break;
    case 8:
        color = 31;
        break;
    case 16:
        color = 34;
        break;
    case 32:
        color = 35;
        break;
    case 64:
        color = 36;
        break;
    case 128:
        color = 30;
        break;
    case 256:
        color = 29;
        break;
    case 512:
        color = 37;
        break;
    case 1024:
        color = 38;
        break;
    case 2048:
        color = 39;
        break;
    case 0:
    default:
        color = 40;
        break;
    }

    printf("\033[%d;1m %5d\033[0m", color, number);
}


void printPanel(const std::vector<std::vector<int>>& panel, const int& score){
    system("cls");
    printf("A: Left, S: Down, D: Right, W: Up\n");

    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            printNumber(panel[i][j]);
        }
        printf("\n\n");
    }

    printf("Current Score: %d\n", score);

}

void move(bool isRow, bool isReverse, std::vector<std::vector<int>>& panel, int& score, bool& isWon){

    using Vec = std::vector<int>;
    auto squeezVec = [&] (Vec& v) {
        if (isReverse){
            reverse(v.begin(), v.end());
        }
        int i = 0;
        Vec ans;
        while (i + 1 < v.size()){
            if (v[i] == v[i + 1]){
                score += v[i] * 2;
                ans.push_back(v[i] * 2);
                i += 2;
            }else{
                ans.push_back(v[i]);
                i++;
            }
        }
        if (i + 1 == v.size()){
            ans.push_back(v[i]);
        }
        while (ans.size() < 4){
            ans.push_back(0);
        }

        return isReverse ? Vec(ans.rbegin(), ans.rend()) : ans;
    };

    auto getVals = [&] (int i, int j){
        return isRow ? panel[i][j] : panel[j][i];
    };

    auto setVals = [&] (int i, int j) -> int& {
        return isRow ? panel[i][j] : panel[j][i];
    };

    for (int i = 0; i < 4; ++i){
        Vec v;
        for (int j = 0; j < 4; ++j){
            if (getVals(i, j) > 0){
                v.push_back(getVals(i, j));
            }
        }
        auto ans = squeezVec(v);
        for (int j = 0; j < 4; ++j){
            setVals(i, j) = ans[j];
            isWon = ans[j] == 2048;
        }
    }

}

void play(std::vector<std::vector<int>>& panel, int& score, bool& isWon){
    char action;
    std::cin >> action;
    //printf("enter: %c\n", action);
    switch (action)
    {
    case 'a':
        move(true, false, panel, score, isWon);
        break;
    case 'w':
        move(false, false, panel, score, isWon);
        break;
    case 'd':
        move(true, true, panel, score, isWon);
        break;
    case 's':
        move(false, true, panel, score, isWon);
        break;
    }

}

bool isDead(const std::vector<std::vector<int>>& panel){
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < 4; ++i){
        for (int j = 0; j < 4; ++j){
            for (const auto& dir : dirs){
                int newI = i + dir[0];
                int newJ = j + dir[1];
                if (newI < 0 || newI == 4 || newJ < 0 || newJ == 4){
                    continue;
                }
                if (panel[i][j] == panel[newI][newJ]){
                    return false;
                }
            }

        }
    }
    return true;
}


int main(){
    std::vector<std::vector<int>> panel(4, std::vector<int>(4));
    int score{0};
    srand(time(NULL));
    spawnNewBlock(panel);
    bool isWon;
    
    while (true){
        if (spawnNewBlock(panel) == 0 && isDead(panel)){
            printf("Game over\n");
            printf("Your scores: %d\n", score);
            system("pause");
            return 0;
        }
        printPanel(panel, score);
        play(panel, score, isWon);
        if (isWon){
            printf("You win\n");
            printf("Your scores: %d\n", score);
            system("pause");
            return 0;
        }
    }


    return 0;
}