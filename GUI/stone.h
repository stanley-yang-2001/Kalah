#ifndef STONE_H
#define STONE_H

#include <QGraphicsEllipseItem>



class Stone: public QGraphicsEllipseItem
{

private:
    int posX;
    int posY;
public:
    Stone(int x, int y);
};

#endif // STONE_H
