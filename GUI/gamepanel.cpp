#include "gamepanel.h"

// panel in GUI that displays information
GamePanel::GamePanel(int x, int y, int width, int length): x(x), y(y),width(width), length(length)
{
    // set style of panel
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    setBrush(brush);
    setPos(x,y);
    setRect(0,0,width, length);

    // set information of the panel and the font
    panelInfo = new QGraphicsTextItem(" ");
    panelInfo->setPos(x+width*0.1, y+length*0.1);

    playerInfo = new QGraphicsTextItem(" ");
    playerInfo->setPos(x+width*0.1, y+length*0.4);

    QFont panelFont("comic sans", 13);

    panelInfo->setFont(panelFont);
    playerInfo->setFont(panelFont);


}
void GamePanel::panelInfoFirst(bool status){    // move the panel information to the top instead of player's panel if needed
    if (status){
        panelInfo->setPos(x+width*0.1, y+length*0.1);
        playerInfo->setPos(x+width*0.1, y+length*0.4);
    } else {
        playerInfo->setPos(x+width*0.1, y+length*0.1);
        panelInfo->setPos(x+width*0.1, y+length*0.4);
    }
}

void GamePanel::updatePlayerInfo(QString text){ // updates the information of the player on the panel
    scene()->removeItem(playerInfo);
    playerInfo->setPlainText(text);
    displayPlayerInfo();
}
void GamePanel::updatePanelInfo(QString text, int info){    // updates the information the panel displays
    scene()->removeItem(panelInfo);
    QString panelText = QString::number(info);
    text = text+panelText;
    panelInfo->setPlainText(text);
    displayPanelInfo();
}

void GamePanel::clearPanel(){                     // removing all texts from panel
    scene()->removeItem(playerInfo);
    scene()->removeItem(panelInfo);
}

void GamePanel::displayPlayerInfo(){            // adding player's information to panel
    scene()->addItem(playerInfo);
}

void GamePanel::displayPanelInfo(){            // adding game's information to panel
    scene()->addItem(panelInfo);
}

void GamePanel::setFontSize(int size){          // set font size of a panel

    QFont panelFont("comic sans", size);

    panelInfo->setFont(panelFont);
    playerInfo->setFont(panelFont);
    clearPanel();
    displayPlayerInfo();
    displayPanelInfo();
}
GamePanel::~GamePanel(){
    delete panelInfo;
    delete playerInfo;
}
