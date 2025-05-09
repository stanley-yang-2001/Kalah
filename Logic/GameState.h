#ifndef GAMESTATE
#define GAMESTATE

#include <string.h>
#include <stdexcept>
#include <iostream>
#include <vector>


class GameState
{
    private:
        std::vector<int> p1Houses;
        std::vector<int> p2Houses;
        int p1Score;
        int p2Score;
        

    public:
        bool extraTurn;
        
        GameState()
        {

            p1Houses = std::vector<int>(6,4);
            p2Houses = std::vector<int>(6,4);
            p1Score = 0;
            p2Score = 0;
            extraTurn = false;
        }

        int GetP1Score()
        {
            return p1Score;
        }

        int GetP2Score()
        {
            return p2Score;
        }

        std::vector<int> GetP1Houses()
        {

            //std::cout<<"size"<<p1Houses.size()<<std::endl;
            return p1Houses;
        }

        std::vector<int> GetP2Houses()
        {
            return p2Houses;
        }

        void ModifyP1Houses(std::vector<int> newData)
        {
            p1Houses = newData;
        }

        void ModifyP2Houses(std::vector<int> newData)
        {

            p2Houses = newData;
        }


        void ModifyP1Score(int newScore)
        {
            p1Score = newScore;
        }

        void ModifyP2Score(int newScore)
        {
            p2Score = newScore;
        }


        bool CheckExtraTurn(){
            return extraTurn;
        }

        std::vector<int> GetLegalP1Moves()
        {
            std::vector<int> legalMoves;

		    for (int i = 0; i < p1Houses.size(); i++)
		    {
			    if (p1Houses[i] > 0)
			    {
				    legalMoves.push_back(i);
		    	}
	    	}

            return legalMoves;
        }

        std::vector<int> GetLegalP2Moves()
        {
            std::vector<int> legalMoves;
		    for (int i = 0; i < p2Houses.size(); i++)
		    {
			    if (p2Houses[i] > 0)
			    {
				    legalMoves.push_back(i);
		    	}
	    	}

            return legalMoves;
        }

};
#endif
