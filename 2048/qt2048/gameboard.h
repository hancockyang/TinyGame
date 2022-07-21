#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QKeyEvent>
#include <QPushButton>
#include "game.h"
#include "cell.h"
#include "observerinterface.h"
#include "subjectinterface.h"
#include <memory>


class GameBoard : public QWidget, public ObserverInterface, public SubjectInterface2
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = 0);
    ~GameBoard();

private:
    // main game logic
    //Game game;

    //std::unique_ptr<ObserverInterface2> game = std::make_unique<Game>();
    Game* game;

    Cell *cells[NCells][NCells] {};

    // main layout
    QVBoxLayout *mainLayout;

    // grid layout of board
    QGridLayout *boardLayout;

    // status layout of board
    QHBoxLayout *statusLayout;

    // reset button
    QPushButton *resetBtn;

    // score widget
    QLabel *score;

    bool isWon, isLost;

    void drawBoard(const std::vector<std::vector<int>>& );

    void drawStatus();

    void resetGame();

// interface

    void update(const int&, const std::vector<std::vector<int>>&, const bool&, const bool& ) override;

    void add(ObserverInterface2*) override;

    void notify(const char&) const override;

private:
    std::vector<ObserverInterface2*> observers;

protected:
    void keyPressEvent(QKeyEvent *event);
};


#endif // GAMEBOARD_H
