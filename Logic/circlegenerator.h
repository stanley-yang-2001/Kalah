#ifndef CIRCLEGENERATOR_H
#define CIRCLEGENERATOR_H


#include <QVector>


class circleGenerator
{
public:
    circleGenerator(int a, int b, int r, int R, int distance);
    int generateX();
    int generateY(int randX);
    QVector<int> getPoints();

private:
    int x;
    int y;
    int smallR;
    int largeR;
    int safeDistance;
};


#endif // CIRCLEGENERATOR_H


