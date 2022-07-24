// main.cpp
#include <QApplication>
#include "gameboard.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    srand(time(NULL));

    GameBoard *board = new GameBoard();
    GameToQt *game = new GameToQt();
    game -> add(board);
    board -> add(game);
    game -> update('E');
    board -> show();

    app.exec();

    delete game;
    game = nullptr;

    return 0;
}



