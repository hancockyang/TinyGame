#include "gameboard.h"
#include "cell.h"
#include <cstdlib>

GameBoard::GameBoard() :
    QWidget(0),
    isWon(false),
    isLost(false)
{
    init();
}


GameBoard::GameBoard(QWidget *parent) :
    QWidget(parent),
    isWon(false),
    isLost(false)
{
    init();
}



void GameBoard::init(){
     resize(650, 500);


     mainLayout = new QVBoxLayout(this);
     setLayout(mainLayout);


     boardLayout = new QGridLayout();

     setStyleSheet("GameBoard { background-color: rgb(187,173,160) }");

     mainLayout->insertLayout(1, boardLayout);


     statusLayout = new QHBoxLayout();
    // create the score widget and add it to the board

     score = new QLabel(QString("SCORE: 0"));
     score->setStyleSheet("QLabel { color: rgb(235,224,214); font: 16pt; }");
     score->setFixedHeight(50);
     statusLayout->insertWidget(0, score, 0, Qt::AlignLeft);


     resetBtn = new QPushButton(QString("RESET"));
     resetBtn -> setStyleSheet("resetBtn {background-color: rgb(187,173,160); color: rgb(235,224,214); font: 16pt; }");
     resetBtn -> setFixedSize(80, 50);
     statusLayout -> insertWidget(1, resetBtn, 0, Qt::AlignRight);


     connect(resetBtn, &QPushButton::clicked, this, &GameBoard::resetGame);

     mainLayout ->insertLayout(2, statusLayout);

}


void GameBoard::drawBoard(){


    for (int i = 0; i < NCells; ++i) {
        for (int j = 0; j < NCells; ++j) {
            boardLayout->addWidget(cells[i][j], i, j);
            cells[i][j]->draw();
        }
    }

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
    if (isWon){
        score->setText(QString("You Won"));
    }
    if (isLost){
        score->setText(QString("You Lost"));
    }

}


void GameBoard::resetGame(){
    char ch = 'E';
    notify(ch);
}

void GameBoard::update(const int& gamescore, const std::vector<std::vector<int>>& panel, const bool& _isWon, const bool& _isLost) {

    score->setText(QString("SCORE: %1").arg(gamescore));

    for (int i = 0; i < NCells; ++i) {
        for (int j = 0; j < NCells; ++j) {
            cells[i][j] -> value = panel[i][j];
        }
    }
    drawBoard();
    isWon = _isWon;
    isLost = _isLost;
}

void GameBoard::add(std::shared_ptr<ObserverInterface2> obr){
    observers.push_back(obr);
}

void GameBoard::notify(const char& ch) const{
    for (const auto& obr : observers){
        obr -> update(ch);
    }
}

void GameBoard::initBoard(const int _NCells, const int _gamegoal){
    NCells = _NCells;
    gamegoal = _gamegoal;
    cells = QVector<QVector<Cell*>>(NCells, QVector<Cell*>(NCells));
    for (int i = 0; i < NCells; ++i) {
        for (int j = 0; j < NCells; ++j) {
            cells[i][j] = new Cell(0);

        }
    }
    instruction = new QLabel(QString("UP: W, DOWN: S, LEFT: A, RIGHT: D.   GOAL: %1").arg(gamegoal));
    instruction->setStyleSheet("QLabel { color: rgb(235,224,214); font: 16pt; }");
    instruction->setFixedHeight(50);
    mainLayout ->insertWidget(0, instruction, 0, Qt::AlignLeft);
}
