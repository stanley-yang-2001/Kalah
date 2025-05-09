#ifndef GAMEPANEL_H
#define GAMEPANEL_H


#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QGraphicsScene>
#include <qstring.h>
#include <qdebug.h>
#include <QFont>

class GamePanel : public QGraphicsRectItem
{
private:
    int x;
    int y;
    int width;
    int length;
    QGraphicsTextItem * panelInfo;
    QGraphicsTextItem * playerInfo;

public:
    GamePanel(int x, int y, int width, int length);
    void panelInfoFirst(bool status);
    void updatePlayerInfo(QString text);
    void updatePanelInfo(QString text, int info);
    void clearPanel();
    void displayPlayerInfo();
    void displayPanelInfo();
    void setFontSize(int size);
    ~GamePanel();
};

#endif // GAMEPANEL_H
