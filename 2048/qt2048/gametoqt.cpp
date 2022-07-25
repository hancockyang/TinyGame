#include "gametoqt.h"
#include "gameruledefault.h"
#include "gamerule2.h"
GameToQt::GameToQt(std::unique_ptr<GameInterface> gameRule): gptr(std::move(gameRule)){}

void GameToQt::add(ObserverInterface *obr){
    observers.push_back(obr);
    obr->initBoard(gptr->NCells, gptr->goal);
}

void GameToQt::notify(const int& total_score, const std::vector<std::vector<int>>& board, const bool& isWon, const bool& isLost) const {

    for (const auto obr : observers){
        obr -> update(total_score, board, isWon, isLost);
    }
}

/*
'A' : LEFT, 'S': DOWN, 'D':right, 'W': UP, 'E': rest
*/

void GameToQt::update(const char& ch){
    //printf("entered %c", ch);
    switch (ch) {
    case 'A':
        gptr->move(true, false);
        break;
    case 'S':
        gptr->move(false, true);
        break;
    case 'D':
        gptr->move(true, true);
        break;
    case 'W':
        gptr->move(false, false);
        break;
    case 'E':
        gptr->resetGame();
        break;
    default:
        break;
    }
    notify(gptr->total_score, gptr->board, gptr->isWon, gptr->isLost);
}


