#include "pit.h"
#include <QGraphicsScene>
#include "stone.h"
#include <QVector>
#include <QDebug>
#include <QMouseEvent>

Pit::Pit(int x, int y, int size, int initialStone, GamePanel * panel): posX(x), posY(y),
    stoneRadius(20), stoneCount (initialStone), radius(size/2), panel(panel)
{
    // set the information of the circle for ciclegenerator and the amount of stone in pit
    radius = size/2;

    stoneRadius = 20;
    stoneCount = initialStone;

    // set the position and graphics of the pit
    generator = new circleGenerator(x,y,radius,radius+stoneRadius, stoneRadius);
    setBrush(Qt::red);
    setRect(posX, posY, size, size);
    setZValue(1);

    // create the selected square gui for the pit
    selected = new QGraphicsRectItem();
    selected->setBrush(Qt::white);
    selected->setRect(posX, posY, radius*2, radius*2);

    setAcceptHoverEvents(true);


}

void Pit::update(){ // update the stone in a pit
    if (stoneCount ==0){    // clear all stone if there's no stone
        for (auto s: stoneInPit){
            scene()->removeItem(s);
            delete s;
        }
        stoneInPit.clear();
    }
    else{
        int currentStone = stoneInPit.size();
        for (int i = 0; i < stoneCount - currentStone; i++){    // add stone graphic to the pit based on the stoneCount and current stone in the pit
            QVector <int> points = generator->getPoints();
            Stone * s = new Stone(points[0], points[1]);
            s->setBrush(Qt::green);
            s->setZValue(2);
            stoneInPit << (s);
            scene()->addItem(s);
        }
    }
}

void Pit::clearStoneCount(){
    stoneCount = 0;
    //return hold;
}

void Pit::addStoneCount(int count){ // add stone tot he pit based on count
    stoneCount+= count;
    update();
}
int Pit::getStoneCount(){
    return stoneCount;
}


void Pit::addStoneInPit(Stone * s){     // add stone (object) to the built-in vector of pit
    stoneInPit.append(s);
}

QVector<Stone*> Pit::getStoneInPit(){
    return stoneInPit;
}

void Pit::clearStoneInPit(){
    stoneInPit.clear();
    clearStoneCount();
}

void Pit::mousePressEvent(QGraphicsSceneMouseEvent *event){

    emit clicked();

}

void Pit::hoverEnterEvent(QGraphicsSceneHoverEvent *event){ // creates a quare bracket around the selected pit when mouse hover over it
    scene()->addItem(selected);
    if (panel != 0){
        panel->displayPlayerInfo();
        panel->updatePanelInfo("Current Stone: ", stoneCount);
    }
}
void Pit::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){ // removes the quare bracket around the selected pit when mouse leaves the pit
    scene()->removeItem(selected);
    qDebug()<<"did the remmoveitem appear?";
    if (panel != 0){
        panel->clearPanel();
    }
}
Pit::~Pit(){
    delete selected;
    for (auto s: stoneInPit){
        delete s;
    }
    stoneInPit.clear();
    delete generator;

    // panel doesn't belong to Pit, it's deleted in GameBoard instead

}
