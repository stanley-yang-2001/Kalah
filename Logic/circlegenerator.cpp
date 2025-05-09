#include "circlegenerator.h"
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <cmath>
#include <QVector>
#include <QRandomGenerator>

// creates random points on a circle with center point (x,y) and within
// certain radius
circleGenerator::circleGenerator(int a, int b, int r, int R, int distance)
{
    x = a;
    y = b;
    smallR = r;
    largeR = R;
    safeDistance = distance;
}


int circleGenerator::generateX(){   // generate random x point within the circle
    int largeX = x+3.5*safeDistance;
    int smallX = x;
    int value = QRandomGenerator::global()->generate();
    if (value < 0){
        value = -value;
    }
    int randX = smallX + value % (largeX-smallX+1);
    return randX;
}


int circleGenerator::generateY(int randX){  // generate random y point within the circle based on the x point

        // circle formula: (x/a)^2 + (y/b)^2 = r^2
        int largeY = safeDistance * sqrt(10+1-((randX-x)/safeDistance)^(2))+ y;


        int smallY = round(largeY) - safeDistance-40;

        int value = QRandomGenerator::global()->generate();
        if (value < 0){
        value = -value;
        }

        int randY = smallY + value % (largeY-smallY+1);


        return randY;
}

QVector<int> circleGenerator::getPoints(){  // getting a random point in the circle with random x and y
        int x = generateX();
        QVector<int> points = {x, generateY(x)};
        return points;
    }

