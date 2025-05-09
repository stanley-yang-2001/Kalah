#include "gameboard.h"
#include "Pit.h"
#include <QSignalMapper>
#include <QInputDialog>
#include <../Logic/GameDriver.h>
#include <../Logic/HighScores.h>
#include <string.h>
GameBoard::GameBoard(GameDriver* driver, QWidget* parent):moveMade(false), driver(driver)
{
    // set up the basis of the page for the game
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1100,600);
    setScene(scene);
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1100,600);
}


void GameBoard::updatePit(int side, int index){ // updates the pit's stone graphic when a move occurred

    // side 1 - player 1
    if (side == 1){
        if (index == 6){        // if current move reaches the store
            kalah1->update();
        }else {                 // if move on pit
            side1[index]->update();
        }

    } else if (side == 2){      // if current move reaches the store
        if (index == -1){
            kalah2->update();
        }
        else {
            side2[index]->update(); // if move on pit
    }
        }

}


void GameBoard::initializeBoard(){  // initialize the GUI for the Kalah Game

    round = 1;

    // clear existing graphics on the board
    scene->clear();
    side1.clear();
    side2.clear();

    // initialize the stores
    kalah2 = new Pit(40, 200, 130, 0);
    kalah1 = new Pit(880, 200, 130, 0);

    scene->addItem(kalah1);
    scene->addItem(kalah2);

    for (int i = 0; i<6; i++){

    int x_pos = 180+ 120*i;

    // initialize the game panels

    roundInfo = new GamePanel(450,0,200,100);
    score1 = new GamePanel(895,350,100,80);
    score2 = new GamePanel(53,350,100,80);
    pitInfo =new GamePanel(450,500,200,100);

    // setting up the information for player
    scene->addItem(roundInfo);
    roundInfo->updatePlayerInfo("Player 1's Turn");
    roundInfo->updatePanelInfo("Round: ", round);

    scene->addItem(score1);
    score1->panelInfoFirst(false);
    score1->updatePlayerInfo("Player 1");
    score1->updatePanelInfo("Score: ", kalah1->getStoneCount());
    score1->setFontSize(10);


    scene->addItem(score2);
    score2->panelInfoFirst(false);
    score2->updatePlayerInfo("Player 2");
    score2->updatePanelInfo("Score: ", kalah2->getStoneCount());
    score2->setFontSize(10);

    scene->addItem(pitInfo);
    pitInfo->setFontSize(10);
    pitInfo->panelInfoFirst(false);

    // initialize the pits with 4 stones in each initially
    Pit * p = new Pit(x_pos,120,90,4, pitInfo);
    Pit * q = new Pit(x_pos,320,90,4, pitInfo);
    p -> setRect(x_pos, 120, 90, 90);
    q -> setRect(x_pos, 320, 90, 90);

    side1.append(p);
    side2.append(q);

    scene->addItem(p);
    scene->addItem(q);

    }

    for (int i = 0; i < 6; i++){
        updatePit(1,i);
        updatePit(2,i);
    }

    // allowing player 1 to move
    assignFunction(1);


}

void GameBoard::takeStonefromPit(int side, int index){  // player mvoes: take all stone from selected pits
    if (side == 1){
        side1[index]->clearStoneCount();        // remove all stone graphic from pit
        side1[index]->update();                 // update the graphic of the pit
    }
    else if (side == 2){
        side2[index]->clearStoneCount();
        side2[index]->update();
    }
    updatePit(side, index);
}


void GameBoard::addStonetoPit(int side, int index, int stone){  // adding stones to the pit and updates the pit

    if (side == 1){

        if (index == 6){
            kalah1->addStoneCount(stone);
            kalah1->update();
            score1->updatePanelInfo("Score: ", kalah1->getStoneCount());    // updateds the score of player 1
        }
        else{
            side1[index]->addStoneCount(stone);
            side1[index]->update();
        }
    }
    else if (side == 2){
        if (index == -1){
            kalah2->addStoneCount(stone);
            kalah2->update();
            score2->updatePanelInfo("Score: ", kalah2->getStoneCount());    // updateds the score of player 1
        } else {
            side2[index]->addStoneCount(stone);
            side2[index]->update();
        }
    }
    delayAnimation();                                                       // delay the system for visual of adding stone to pit
    updatePit(side, index);

}

void GameBoard::InitializeCPU() // initialize the game if it's player vs ai
{
    initializeBoard();
    driver->StartCPU();
}

void GameBoard::BackToMenu(){
    displayMainMenu();
}

void GameBoard::displayMainMenu(){  // displays the main menu with option to PvP, PvE, and High Score
    // Title
    scene->clear();
    QGraphicsTextItem* title = new QGraphicsTextItem(QString("Kalah"));
    QFont titleFont("comic sans", 60);
    title->setFont(titleFont);

    int titleX = this->width()/2-title->boundingRect().width()/2;
    int titleY = 150;
    title->setPos(titleX, titleY);
    scene->addItem(title);

    // PvP
    Button* startButton = new Button(QString("PvP"));
    int bxPos = this->width()/2 - startButton->boundingRect().width()/2;
    int byPos = 375;
    startButton->setPos(bxPos, byPos);
    connect(startButton, SIGNAL(clicked()), this, SLOT(initializeBoard()));
    scene->addItem(startButton);

    // PvE
    Button* aiButton = new Button(QString("AI"));
    int aibxPos = this->width()/2 - aiButton->boundingRect().width()/2;
    int aibyPos = 475;
    aiButton->setPos(aibxPos, aibyPos);
    //connect(aiButton, SIGNAL(clicked()), this, SLOT(initializeBoard()));
    connect(aiButton, SIGNAL(clicked()), this, SLOT(InitializeCPU()));
    scene->addItem(aiButton);

    // Hish Scores
    Button* highScoreButton = new Button(QString("High Scores"));
    int highScorexPos = this->width()/2 - highScoreButton->boundingRect().width()/2;
    int highScoreyPos = 275;
    highScoreButton->setPos(highScorexPos, highScoreyPos);
    connect(highScoreButton, SIGNAL(clicked()), this, SLOT(InitializeHighScores()));
    scene->addItem(highScoreButton);


    show();
}



void GameBoard::makeMove(int index){    // Player making move - calls to GameDriver
    if (driver->GetTurn()){
        driver->Player1Turn(index, this);
        if (driver->CheckExtraTurn()){  // if extra turn, then player 1 keep moving and player 2's pit won't be assigned functions
            driver->UseExtraTurn();
        } else {
            assignFunction(2);
        }
    } else {
        if(!driver->CPUStatus()){       // checks if player is playing against player or Ai
            driver->Player2Turn(index, this);
        }else{                          // Ai's move
            roundInfo->updatePlayerInfo("Player 2's Turn");
            driver->Player2Turn(driver->GetCPUMove(), this);
        }
        if (driver->CheckExtraTurn()){  // if extra turn, then player 2 keep moving and player 1's pit won't be assigned functions
            driver->UseExtraTurn();
        } else {
            assignFunction(1);
        }
    }
    // continues the game/adding to round if game is not over
    if (driver->CheckGameOver()){
        EndMessage();
    } else {
        round +=1;
        roundInfo->updatePanelInfo("Round: ", round);
    }

}

void GameBoard::assignFunction(int side){   // assign makeMove to the pits in the GUI

    QSignalMapper* mapper = new QSignalMapper(this);
    int count = 0;
    if (side == 1){

        for(auto p: side1){                 // if it's player 1's turn
            if (p->getStoneCount()!=0){
                // assign makeMove to player 1's pits
                connect(p, SIGNAL(clicked()), mapper, SLOT(map()));
                mapper->setMapping(p,count);
            }
            count += 1;
        }

        for(auto p: side2){
            // disconnect makeMove from player 2's pits
            p->disconnect();
        }
        connect(mapper, SIGNAL(mappedInt(int)), this, SLOT(makeMove(int)));
        roundInfo->updatePlayerInfo("Player 1's Turn");         // updates the round panel
    } else {                                // if it's player 2's turn
            for(auto p: side2){
                if (p->getStoneCount()!=0){
                // assign makeMove to player 2's pits
                    connect(p, SIGNAL(clicked()), mapper, SLOT(map()));
                    mapper->setMapping(p,count);
                }
                count += 1;
            }
            for(auto p: side1){
                // disconnect makeMove from player 1's pits
                p->disconnect();
            }
            connect(mapper, SIGNAL(mappedInt(int)), this, SLOT(makeMove(int)));
            roundInfo->updatePlayerInfo("Player 2's Turn");     // updates the round panel
        }

    }



void GameBoard::delayAnimation(){                               // delay the function by 0.5 sec
    QTime waitTime = QTime::currentTime().addMSecs(250);
    while (QTime::currentTime() < waitTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents, 50);
    }

}

void GameBoard::EndMessage(){

    QMessageBox gameEnd;
    QString winner;
    if (kalah1->getStoneCount() > kalah2->getStoneCount()){
        winner = "Player 1 won!";
    } else{
        winner = "Player 2 won!";
    }

    //GET PLAYER 1 NAME FROM INPUT WINDOW TEXT BOX OR SM
    //spawn text window that asks for player one name
    std::string playerOneName = "Default player 1";



    playerOneName = QInputDialog::getText(0, "Save Score",
                                          "Player One Name:", QLineEdit::Normal,
                                          "").toStdString();

    std::string filename = "scoreboard.csv";
    driver->SaveScoreToFile(playerOneName, filename, kalah1->getStoneCount());

    //if player 2 is NOT the AI
    if(!driver->CPUStatus())
    {
        //GET PLAYER 2 NAME FROM INPUT WINDOW TEXT BOX OR SM
        std::string playerTwoName = "Default player 2";
        playerTwoName = QInputDialog::getText(0, "Save Score",
                                              "Player Two Name:", QLineEdit::Normal,
                                              "").toStdString();

        driver->SaveScoreToFile(playerTwoName, filename, kalah2->getStoneCount());
    }

    gameEnd.setText(winner);
    gameEnd.setInformativeText("Do you want to play again?");
    gameEnd.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    int choice = gameEnd.exec();

    switch (choice){
    case QMessageBox::Yes:
        initializeBoard();
    case QMessageBox::No:
        displayMainMenu();
        driver->ResetCPU();
    }


}




void GameBoard::InitializeHighScores(){
    scene->clear();
    QGraphicsTextItem* header = new QGraphicsTextItem(QString("High Scores"));
    QFont headerFont("comic sans", 40);
    header->setFont(headerFont);

    //Adding title to top
    int headerX = this->width()/2-header->boundingRect().width()/2;
    int headerY = 10;
    header->setPos(headerX, headerY);
    scene->addItem(header);

    //Adding back button
    Button* backButton = new Button(QString("Back"));
    connect(backButton, SIGNAL(clicked()), this, SLOT(BackToMenu()));
    scene->addItem(backButton);



    //Displaying HighScores
    HighScoreManager manager = *new HighScoreManager("scoreboard.csv");
    std::vector<std::pair<std::string, int>> highScores = manager.GetHighScores();

    int yOffset = 100;
    int xOffset = this->width()/2-100;

    QFont highScoreFont("comic sans", 20);

    for(const auto& entry : highScores){
        std::string name = entry.first;
        int score = entry.second;

        std::string displayItem = name + ": " +  std::to_string(score);

        QString text = QString::fromStdString(displayItem);

        QGraphicsTextItem* item = new QGraphicsTextItem(text);



        item->setFont(highScoreFont);
        item->setPos(xOffset, yOffset);

        scene->addItem(item);

        yOffset += 35;

    }

}

GameBoard::~GameBoard(){
    delete roundInfo;
    delete score1;
    delete score2;
    delete pitInfo;
    delete driver;
    delete kalah1;
    delete kalah2;
    for (auto pit: side1){
        delete pit;
    }
    side1.clear();
    for (auto pit: side2){
        delete pit;
    }
    side2.clear();
    delete scene;
}

