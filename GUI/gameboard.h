#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include "Pit.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "button.h"
#include <QFont>
#include <QGraphicsTextItem>
#include <QTime>
#include <QCoreApplication>
#include <qdebug.h>
#include <gamepanel.h>
#include <QMessageBox>
#include <QString>
#include "Pit.h"
#include <QSignalMapper>

class GameDriver;
class GameBoard: public QGraphicsView
{
    Q_OBJECT

public:
    GameBoard(GameDriver* driver, QWidget *parent = 0);

    void updatePit(int side, int index);
    void addStonetoPit(int side, int index, int stone);
    void takeStonefromPit(int side, int index);
    void displayMainMenu();
    void assignFunction(int side);
    void delayAnimation();
    void EndMessage();
    ~GameBoard();

public slots:
    void initializeBoard();
    void makeMove(int index);
    void InitializeCPU();
    void InitializeHighScores();
    void BackToMenu();



private:
    int round;
    bool moveMade;
    GamePanel * roundInfo;
    GamePanel * score1;
    GamePanel * score2;
    GamePanel * pitInfo;
    GameDriver* driver;
    Pit* kalah1;
    Pit* kalah2;
    QVector<Pit*> side1;
    QVector<Pit*> side2;
    QGraphicsScene * scene;


};

#endif // GAMEBOARD_H

