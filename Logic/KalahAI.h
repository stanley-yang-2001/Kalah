#ifndef KALAHAI
#define KALAHAI

#include <vector>
#include <cstdlib> 
#include <iostream>
#include <ctime>
#include "GameState.h"
#include "GameLogic.h"

class KalahAI
{
private:
	int searchDepth; //defines how many moves deep it will search
	int randMoveChance; //An integer between 0 and 100 that represents the percentage chance of making a random move
	GameLogic rules = GameLogic();

	int EvaluationFunction(GameState state) //generates an integer estimate of the value of the game state
	{
		int aiScore = state.GetP2Score();
		int playerScore = state.GetP1Score();
		
		return aiScore - playerScore; //wants to maximize its own score while minimizing the players

	}

	int MiniMax(GameState state, int depth, bool isMax)
	{
		if(rules.CheckGameOver(state) || depth == 0)
		{
			return EvaluationFunction(state);
		}

		std::vector<int> legalMoves;

		if(isMax)
		{
			legalMoves = state.GetLegalP2Moves();
			int maxScore = -9999999;
			
			for (int i = 0; i < legalMoves.size(); i++)
			{
				int currentMove = legalMoves[i];
                GameState nextState = rules.MakeP2Move(state, currentMove);
				int currentScore;
				if(nextState.extraTurn)
				{
					nextState.extraTurn = false;
					currentScore = MiniMax(nextState, depth - 1, true);
				}
				else
				{
					currentScore = MiniMax(nextState, depth - 1, false);
				}

				if (currentScore > maxScore)
				{
					maxScore = currentScore;
				}
			}
			
			return maxScore;
		}
		else 
		{
			legalMoves = state.GetLegalP1Moves();
			int minScore = 9999999;
			
			for (int i = 0; i < legalMoves.size(); i++)
			{
				int currentMove = legalMoves[i];
				GameState nextState = rules.MakeP1Move(state, currentMove);
				int currentScore;
				if(nextState.extraTurn)
				{
					nextState.extraTurn = false;
					currentScore = MiniMax(nextState, depth - 1, false);
				}
				else
				{
					currentScore = MiniMax(nextState, depth - 1, true);
				}

				if (currentScore < minScore)
				{
					minScore = currentScore;
				}
			}

			return minScore;
		}
	}

public:
	KalahAI(int depth = 1, int randomChance = 0)
	{
		searchDepth = depth;
		randMoveChance = randomChance;
		std::srand(std::time(0));
	}

	void SetDepth(int depth)
	{
		searchDepth = depth;
	}

	void SetRandMoveChance(int randomChance)
	{
		randMoveChance = randomChance;
		std::srand(std::time(0));
	}

	int PickMove(GameState state)//right now it assumes we're only searching at a depth of one and with no random chance
	{	
		int choice;
		bool makeRandMove = ((std::rand() % 100 + 1) <= randMoveChance);
		std::vector<int> legalMoves = state.GetLegalP2Moves();

		if(makeRandMove)
		{
			int numMoves = legalMoves.size();
			choice = (std::rand() % numMoves);

			return legalMoves[choice];
		}
		else
		{	
			int maxScore = -999999;
			for (int i = 0; i < legalMoves.size(); i++)
			{
				int currentMove = legalMoves[i];
				GameState nextState = rules.MakeP2Move(state, currentMove);
				int currentScore;
				if(nextState.extraTurn)
				{
					nextState.extraTurn = false;
					currentScore = MiniMax(nextState, searchDepth - 1, true);
				}
				else
				{
					currentScore = MiniMax(nextState, searchDepth - 1, false);
				}

				if (currentScore > maxScore)
				{
					maxScore = currentScore;
					choice = i;
				}
			}
		}
		
		std::cout << "choice is " << choice << std::endl;
		return legalMoves[choice];
	}
};
#endif
