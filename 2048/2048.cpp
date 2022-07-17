#define _CRT_SECURE_NO_WARNING

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <vector>
#include <iostream>


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

void move(const Direction &dirs, std::vector<std::vector<int>>& panel, int& score, bool& isWon){

    switch (dirs)
    {
    case LEFT:{
        for (int j = 0; j < 4; ++j){
            for (int i = 0; i < 4; ++i){
                if (j == 0 || panel[i][j] == 0){
                    continue;
                }
                int k = j;
                while (k > 0 && panel[i][k - 1] == 0){
                    panel[i][k - 1] = panel[i][k];
                    panel[i][k] = 0;
                    k--;
                }
                if (k > 0 && panel[i][k - 1] == panel[i][k]){
                    panel[i][k - 1] *= 2;
                    isWon = panel[i][k - 1] == 2048;
                    panel[i][k] = 0;
                    score += panel[i][k - 1];  
                    continue;
                }

            }
        }
        break;
    }
    case UP:{
        for (int i = 0; i < 4; ++i){
            for (int j = 0; j < 4; ++j){
                if (i == 0 || panel[i][j] == 0){
                    continue;
                }
                int k = i;
                while(k > 0 && panel[k - 1][j] == 0){
                    panel[k - 1][j] = panel[k][j];
                    panel[k][j] = 0;
                    k--;
                }
                if (k > 0 && panel[k - 1][j] == panel[k][j]){
                    panel[k - 1][j] *= 2;
                    isWon = panel[k - 1][j] == 2048;
                    panel[k][j] = 0;
                    score += panel[k - 1][j];  
                    continue;
                }
            }
        }
        break;
    }  
    case RIGHT:{
        for (int j = 3; j >= 0; --j){
            for (int i = 0; i < 4; ++i){
                if (j == 3 || panel[i][j] == 0){
                    continue;
                }
                int k = j;
                while(k < 3 && panel[i][k + 1] == 0){
                    panel[i][k + 1] = panel[i][k];
                    panel[i][k] = 0;
                    k++;
                }
                if (k < 3 && panel[i][k + 1] == panel[i][k]){
                    panel[i][k + 1] *= 2;
                    isWon = panel[i][k + 1] == 2048;
                    panel[i][k] = 0;
                    score += panel[i][k + 1];
                    continue;
                }
            }
        }
        break;
    }

    case DOWN:{
        for (int i = 3; i >= 0; --i){
            for(int j = 0; j < 4; ++j){
                if (i == 3 || panel[i][j] == 0){
                    continue;
                }
                int k = i;
                while (k < 3 && panel[k + 1][j] == 0){
                    panel[k + 1][j] = panel[k][j];
                    panel[k][j] = 0;
                    k++;
                }
                if (k < 3 && panel[k + 1][j] == panel[k][j]){
                    panel[k + 1][j] *= 2;
                    isWon = panel[k + 1][j] == 2048;
                    panel[k][j] = 0;
                    score += panel[k + 1][j];  
                    continue;
                }
            }
        }
        break;
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
        dirs = LEFT;
        break;
    case 'w':
        dirs = UP;
        break;
    case 'd':
        dirs = RIGHT;
        break;
    case 's':
        dirs = DOWN;
        break;
    }

    move(dirs, panel, score, isWon);



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
        }
    }


    return 0;
}