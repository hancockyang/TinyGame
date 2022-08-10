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
    std::shared_ptr<GameToQt> game = std::make_shared<GameToQt>(std::move(gameRule1));

    std::shared_ptr<ObserverInterface2> sptr2 = game;
    //GameToQt *game = new GameToQt(std::move(gameRule1));
    game -> add(board);

    board -> add(sptr2);
    game -> update('E');
    board -> show();



    return app.exec();
}



