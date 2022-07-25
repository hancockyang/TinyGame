// main.cpp
#include <QApplication>
#include "gameboard.h"
#include "gameruledefault.h"
#include "gamerule2.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    srand(time(NULL));

    GameBoard *board = new GameBoard();
    std::unique_ptr<GameInterface> gameRule1 = std::make_unique<GameRuleDefault>();
    GameToQt *game = new GameToQt(std::move(gameRule1));
    game -> add(board);
    board -> add(game);
    game -> update('E');
    board -> show();

    app.exec();

    delete game;
    game = nullptr;

    return 0;
}



