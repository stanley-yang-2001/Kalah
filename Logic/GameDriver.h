#ifndef GAMEDRIVER
#define GAMEDRIVER

#include <iostream>
#include <fstream>
#include "GameState.h"
#include "GameLogic.h"
#include "KalahAI.h"
#include "HighScores.h"
#include "KalahAI.h"
#include "HighScores.h"
#include <gameboard.h>



class GameDriver
{
private:
    //--------- INSTANCE VARIABLES --------------
    bool isP1Turn;
    bool CPU;
    GameState state;
    GameLogic logic;
    KalahAI computer;

/*
    void GameOver()
    {
        state = logic.EndGame(state);

        if(state.GetP1Score() > state.GetP2Score())
        {
            std::cout << "Player 1 wins! Yay!" << std::endl;
        } else {
            std::cout << "Player 2 wins! Nice job partner!" << std::endl;
        }

        std::cout << "Play again? (y/n)" << std::endl;
        char newGame;
        std::cin >> newGame;

        if(newGame == 'y')
        {
            state = GameState();
            isP1Turn = true;
        }
    }*/


public:
    //--------------- PUBLIC FUNCTIONS ------------ 
    //constructor
    GameDriver()
    {
        //initialize instance variables
        state = GameState();
        logic = GameLogic();
        isP1Turn = true;
        computer = KalahAI();
        CPU = false;
    }

    void SaveScoreToFile(std::string &personName, std::string &filename, int score)
    {
        HighScoreManager scoreManager = HighScoreManager(filename);
        scoreManager.WriteHighScore(personName, score);
    }


    void Player1Turn(int moveIndex, GameBoard* board)
    {
        //replaces state object with new state returned from GameLogic
        //ONLY IF VALID MOVE --> perhaps throw an exception or an error here?

        state = logic.MakeP1Move(state, moveIndex, board);
        if (!state.CheckExtraTurn()){
            EndTurn();
        }
    }


    void Player2Turn(int moveIndex, GameBoard* board)
    {

        state = logic.MakeP2Move(state, moveIndex, board);
        if (!state.CheckExtraTurn()){
            EndTurn();
        }

    }

    bool ResetCPU()
    {
        CPU = false;
        return CPU;
    }

    bool StartCPU()
    {
        CPU = true;
        return CPU;
    }

    bool CPUStatus()
    {
        return CPU;
    }

    int GetCPUMove()
    {
        return computer.PickMove(state);
    }


    bool CheckExtraTurn(){
        return state.extraTurn;
    }
    void UseExtraTurn(){
        state.extraTurn = false;
    }

    bool GetTurn(){
        return isP1Turn;
    }
    void EndTurn(){
        isP1Turn = !isP1Turn;
    }

    bool CheckGameOver(){
        return logic.CheckGameOver(state);
    }

};
#endif
