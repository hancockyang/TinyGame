#include "gametoqt.h"


GameToQt::GameToQt():Game(){}

GameToQt::GameToQt(int _size):Game(_size){}

GameToQt::GameToQt(int _size, int _goal):Game(_size, _goal){}

void GameToQt::add(ObserverInterface *obr){
    observers.push_back(obr);
    obr->initBoard(Game::NCells, Game::goal);
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
        Game::move(true, false);
        break;
    case 'S':
        Game::move(false, true);
        break;
    case 'D':
        Game::move(true, true);
        break;
    case 'W':
        Game::move(false, false);
        break;
    case 'E':
        Game::resetGame();
        break;
    default:
        break;
    }
    notify(total_score, board, isWon, isLost);
}


