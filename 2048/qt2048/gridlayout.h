#ifndef GRIDLAYOUT_H
#define GRIDLAYOUT_H

#include <QWidget>
#include <QGridLayout>
#include "game.h"
#include "cell.h"

class GridLayout : public QGridLayout
{
    Q_OBJECT
public:
    GridLayout();

    //Cell *cells[NCells][NCells] {};

    void update();
};

#endif // GRIDLAYOUT_H
