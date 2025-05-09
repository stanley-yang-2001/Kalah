#include "button.h"


// button class  used in GUI
Button::Button(QString name, QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    // set the style of the button
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);

    // set the tax of button based on input parameter
    text = new QGraphicsTextItem(name, this);
    int xPos = rect().width()/2 - text -> boundingRect().width()/2;
    int yPos = rect().height()/2 - text -> boundingRect().height()/2;
    text->setPos(xPos, yPos);


    // allows the button class to be hoverable
    setAcceptHoverEvents(true);

}


void Button::mousePressEvent(QGraphicsSceneMouseEvent *event){  // action listener for pressing mouse
    emit clicked();
}


void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event){  // action listener for hovering mouse over the button
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::cyan);
    setBrush(brush);
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){  // action listener for hovering mouse away from the button
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkCyan);
    setBrush(brush);
}
Button::~Button(){
    delete text;
}
