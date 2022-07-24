#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QVector>
#include "gametoqt.h"
#include "cell.h"
#include "observerinterface.h"
#include "subjectinterface.h"



class GameBoard : public QWidget, public ObserverInterface, public SubjectInterface2
{
    Q_OBJECT
public:
    GameBoard();

    explicit GameBoard(QWidget *parent);

    GameBoard(QWidget *parent, int _NCells);

    void update(const int&, const std::vector<std::vector<int>>&, const bool&, const bool& ) override;

    void add(ObserverInterface2*) override;

    void notify(const char&) const override;

    void initBoard(const int, const int) override;

private:
    // main game logic



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

    // instruction widget
    QLabel *instruction;

    bool isWon, isLost;

    int NCells, gamegoal;

    QVector<QVector<Cell*>> cells;

    void drawBoard();

    void resetGame();
    void init();

// interface



protected:
    void keyPressEvent(QKeyEvent *event) override;
};


#endif // GAMEBOARD_H
