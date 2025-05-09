#ifndef GAMELOGIC
#define GAMELOGIC

#include <string.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "GameState.h"
#include <gameboard.h>
#include <qdebug.h>


class GameLogic
{
public:

    bool CheckGameOver(GameState &state)
    {
        std::vector<int> p1Houses = state.GetP1Houses();
        std::vector<int> p2Houses = state.GetP2Houses();

        bool p1Empty = true;
        bool p2Empty = true;

        for (int i = 0; i < 6; i++)
        {

            if (p1Houses[i] != 0)
                p1Empty = false;
            if (p2Houses[i] != 0)
            {
                p2Empty = false;
            }            
        }

        return (p1Empty || p2Empty);
    }
    
    bool CheckExtraTurn(GameState &state)
    {
        return state.extraTurn;
    }

    GameState MakeP1Move(GameState state, int index, GameBoard* board = NULL)
    {
        std::vector<int> newP1Houses = state.GetP1Houses();
        std::vector<int> newP2Houses = state.GetP2Houses();

        int newP1Score = state.GetP1Score();
        if (index < 0 || index >= 6 || newP1Houses[index] == 0)
        {
            // Should we print out a pop message that informs of invalid move ?
            std::cerr << "Invalid move" << std::endl;
            return state;
        }

        //Pulling the stones we have to move and setting the current number of stones in the given index to 0

        int stonesInPlay = newP1Houses[index];
        newP1Houses[index] = 0;
        if(board){
            board->takeStonefromPit(1,index);
        }

        //Tracking current index and which player's houses we are adding to
        int currentIndex = index + 1;
        bool useP1Houses = true;

        while (stonesInPlay > 0)
        {
            if(useP1Houses)//if we should be adding stones to player 1's houses
            {
                if(currentIndex == 6)//check to see if we should be add a stone to player ones score
                {   
                    //increasing player 1s score, setting index to 0 and flagging program to use player 2s houses
                    newP1Score++;
                    board->addStonetoPit(1,currentIndex,1);
                    useP1Houses = false;
                    stonesInPlay--;
                    currentIndex--;

                    //if the last stone was placed inside the p1 house, then take an extra turn
                    if(stonesInPlay == 0)
                    {
                        state.extraTurn = true;
                        qDebug()<<"Extra Turn!";
                    }

                }else{ //otherwise we are adding to player 1's houses
                    newP1Houses[currentIndex]++;
                    board->addStonetoPit(1,currentIndex,1);
                    stonesInPlay--;
                    if (stonesInPlay == 0 && (newP1Houses[currentIndex] == 1)){
                        if (board){
                            board->takeStonefromPit(2,currentIndex);
                            board->addStonetoPit(1,currentIndex, newP2Houses[currentIndex]);
                    }
                        newP1Houses[currentIndex] += newP2Houses[currentIndex];
                        newP1Score +=newP2Houses[currentIndex];
                        newP2Houses[currentIndex] = 0;
                    }
                    currentIndex++;
                }
            }else{//if we should be adding stones to player 2's houses
                newP2Houses[currentIndex]++;

                if(board){
                    board->addStonetoPit(2,currentIndex,1);
                }

                stonesInPlay--;
                currentIndex--;

                if(currentIndex == -1)//check if we have reached the end of player 2 houses
                {

                    //setting index to 0 and flagging program to use player 1's houses
                    currentIndex = 0;
                    useP1Houses = true;
                }
            }
        }

        state.ModifyP1Score(newP1Score);
        state.ModifyP1Houses(newP1Houses);
        state.ModifyP2Houses(newP2Houses);

        return state;
    }

    GameState MakeP2Move(GameState &state, int index, GameBoard* board = NULL)
    {
        std::vector<int> newP1Houses = state.GetP1Houses();
        std::vector<int> newP2Houses = state.GetP2Houses();
        int newP2Score = state.GetP2Score();

        if (index < 0 || index >= 6 || newP2Houses[index] == 0)
        {
            // Should we print out a pop message that informs of invalid move ?
            std::cerr << "Invalid move" << std::endl;
            return state;
        }

        //Pulling the stones we have to move and setting the current number of stones in the given index to 0
        int stonesInPlay = newP2Houses[index];
        newP2Houses[index] = 0;

        if(board){ //Checking to see if a board was passed
            board->takeStonefromPit(2,index);
        }

        //Tracking current index and which player's houses we are adding to
        int currentIndex = index - 1;
        bool useP2Houses = true;

        while (stonesInPlay > 0)
        {
            if(useP2Houses)//if we should be adding stones to player 1's houses
            {
                if(currentIndex == -1)//check to see if we should be add a stone to player ones score
                {   
                    //increasing player 1s score, setting index to 0 and flagging program to use player 2s houses
                    newP2Score++;

                    if(board){ //Checking to see if a board was passed
                        board->addStonetoPit(2,currentIndex,1);
                    }

                    useP2Houses = false;
                    stonesInPlay--;
                    currentIndex = 0;

                    //if the last stone was placed inside the p1 house, then take an extra turn
                    if(stonesInPlay == 0)
                    {
                        state.extraTurn = true;
                    }
                    
                }else{ //otherwise we are adding to player 2's houses
                    newP2Houses[currentIndex]++;

                    if(board){ //Checking to see if a board was passed
                        board->addStonetoPit(2,currentIndex,1);
                    }

                    stonesInPlay--;
                    if (stonesInPlay == 0 && (newP2Houses[currentIndex] == 1)){
                        if (board){
                        board->takeStonefromPit(1,currentIndex);
                        board->addStonetoPit(2,currentIndex, newP1Houses[currentIndex]);
                        }
                        newP2Houses[currentIndex] += newP1Houses[currentIndex];
                        newP2Score +=newP1Houses[currentIndex];
                        newP1Houses[currentIndex] = 0;
                    }
                    currentIndex--;
                }
            }else{//if we should be adding stones to player 1's houses
                newP1Houses[currentIndex]++;
                if(board){
                    board->addStonetoPit(1,currentIndex,1);
                }
                stonesInPlay--;
                currentIndex++;

                if(currentIndex == 6)//check if we have reached the end of player 2 houses
                {
                    //setting index to 0 and flagging program to use player 1's houses
                    currentIndex = 5;
                    useP2Houses = true;
                }
            }
        }

        state.ModifyP2Score(newP2Score);
        state.ModifyP1Houses(newP1Houses);
        state.ModifyP2Houses(newP2Houses);

        return state;
    }

    GameState EndGame(GameState &state)
    {
        std::vector<int> player1Houses = state.GetP1Houses();
        std::vector<int> player2Houses = state.GetP2Houses();

        int finalP1Score = state.GetP1Score();
        int finalP2Score = state.GetP2Score();

        for (int i = 0; i < 6; i++)
        {
            //loops through all houses and moves any seeds to the appropriate store
            finalP1Score += player1Houses[i];
            finalP2Score += player2Houses[i];
            player1Houses[i] = 0;
            player2Houses[i] = 0;
        }

        state.ModifyP1Houses(player1Houses);
        state.ModifyP2Houses(player2Houses);
        state.ModifyP1Score(finalP1Score);
        state.ModifyP2Score(finalP2Score);

        return state;
    }
    
};
#endif
