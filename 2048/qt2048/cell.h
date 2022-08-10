// cell.h
#ifndef CELL_H
#define CELL_H

#include <QLabel>

class Cell : public QLabel
{
    Q_OBJECT
public:
    Cell(int _value);
    int value;
    void draw();
private:


};

#endif // CELL_H
