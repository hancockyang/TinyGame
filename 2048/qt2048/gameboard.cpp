#include "gameboard.h"
#include "cell.h"
#include "utility.h"
#include <cstdlib>

GameBoard::~GameBoard(){
    delete game;
}

GameBoard::GameBoard(QWidget *parent) : QWidget(parent), isWon(false), isLost(false)
{
    // set default size
    resize(650, 450);

    // create the main layout
    mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    game = new Game();
    game->add(this);
    add(game);

    boardLayout = new QGridLayout();
    drawBoard(game->board);

    drawStatus();

    setStyleSheet("GameBoard { background-color: rgb(187,173,160) }");
}




void GameBoard::drawBoard(const std::vector<std::vector<int>>& panel){

    delete boardLayout;
    boardLayout = new QGridLayout();
    for (int i = 0; i < NCells; ++i) {
        for (int j = 0; j < NCells; ++j) {
            delete cells[i][j];
            cells[i][j] = new Cell(panel[i][j]);
            boardLayout->addWidget(cells[i][j], i, j);
            cells[i][j]->draw();
        }
    }
    mainLayout->insertLayout(0, boardLayout);
}

void GameBoard::drawStatus(){
    //delete statusLayout;
    statusLayout = new QHBoxLayout();
    //    // create the score widget and add it to the board
    //delete score;
    score = new QLabel(QString("SCORE: 0"));
    score->setStyleSheet("QLabel { color: rgb(235,224,214); font: 16pt; }");
    score->setFixedHeight(50);
    statusLayout->insertWidget(0, score, 0, Qt::AlignLeft);

    //delete resetBtn;
    resetBtn = new QPushButton(QString("RESET"));
    resetBtn -> setStyleSheet("resetBtn {background-color: rgb(187,173,160); color: rgb(235,224,214); font: 16pt; }");
    resetBtn -> setFixedSize(80, 50);
    statusLayout -> insertWidget(1, resetBtn, 0, Qt::AlignRight);


    connect(resetBtn, &QPushButton::clicked, this, &GameBoard::resetGame);

    mainLayout ->insertLayout(1, statusLayout);
}

void GameBoard::keyPressEvent(QKeyEvent *event)
{

    if (isWon){
        score->setText(QString("You Won"));
        return;
    }
    if (isLost){
        score->setText(QString("You Lost"));
        return;
    }
    char ch;
    switch (event->key()) {
    case Qt::Key_W: // UP
        //game->move(false, false);
        ch = 'W';
        break;
    case Qt::Key_S: // down
        //game->move(false, true);
        ch = 'S';
        break;
    case Qt::Key_A: // LEFT
        //game->move(true, false);
        ch = 'A';
        break;
    case Qt::Key_D: // right
        //game->move(true, true);
        ch = 'D';
        break;
    }

    notify(ch);

}


void GameBoard::resetGame(){
    char ch = 'E';
    notify(ch);
    //game->resetGame();
}

void GameBoard::update(const int& gamescore, const std::vector<std::vector<int>>& panel, const bool& _isWon, const bool& _isLost) {

    score->setText(QString("SCORE: %1").arg(gamescore));
    drawBoard(panel);
    isWon = _isWon;
    isLost = _isLost;
}

void GameBoard::add(ObserverInterface2* obr){
    observers.push_back(obr);
}

void GameBoard::notify(const char& ch) const{
    for (const auto& obr : observers){
        obr -> update(ch);
    }
}