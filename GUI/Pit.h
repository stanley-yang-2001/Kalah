#ifndef PIT_H
#define PIT_H

#include <QVector>
#include "stone.h"
#include <QGraphicsEllipseItem>
#include <../Logic/circlegenerator.h>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <gamepanel.h>
#include <QVector>
#include <QDebug>
#include <QMouseEvent>



class Pit : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
private:

    int posX;
    int posY;
    int stoneRadius;
    int stoneCount;
    int radius;
    QGraphicsRectItem* selected;
    QVector<Stone*> stoneInPit;
    circleGenerator* generator;
    GamePanel * panel;


public:
    Pit(int x, int y, int size, int initialStone, GamePanel * panel = 0);
    void update();
    void clearStoneCount();
    void addStoneCount(int count);
    int getStoneCount();
    void addStoneInPit(Stone * s);
    QVector<Stone*> getStoneInPit();
    void clearStoneInPit();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    ~Pit();

signals:
    void clicked();
};

#endif // PIT_H

