#include "AI.h"
#include <stdlib.h> //srand and rand from here
#include <time.h> //this allows us to get the time to generate a random seed using srand
#include <iostream>

AI::AI(int shipCount, int difficulty)
{
    m_sinkCount = 0;
    m_mediumState = 0;
    m_directionTracker = 0;
    m_difficulty = difficulty;
    m_name = "AI";
    m_shipCount = shipCount;
    m_ships = new ship* [m_shipCount];
    for(int i=0; i<m_shipCount; i++)
    {
        m_ships[i] = nullptr;
    }
}

AI::~AI()
{
    
   
}

int AI::getDifficulty() const
{
    return m_difficulty;
}


//m_player2 -> playerTurn(m_tempX, m_tempY, m_player1 -> hitCheck(m_tempX, m_tempY));//updates the player's boards and prints the result of the shot
//std::cout<<m_player1 -> updatePlayerShotAt(m_tempX, m_tempY);//updates the opposing player's boards and prints the result of the shot
//use these to fire the shots, it will take care of checks
//if(m_board.m_shotGrid[m_tempY][m_tempX] != '.') problem = true; need this for ensuring firing at new loc

void AI::easyPlay(player* p)
{
   bool problem= false;
  
  
    do{
        problem = false;
        m_initialX= randomCoord();
        m_initialY= randomCoord();
        if(m_board.m_shotGrid[m_initialY][m_initialX] != '.') problem = true;

    }while(problem);

    this-> playerTurn(m_initialX, m_initialY, p->hitCheck(m_initialX, m_initialY));
    std::cout<<p->updatePlayerShotAt(m_initialX,m_initialY);
 

}

void AI::mediumPlay(player* p)
{
    bool problem= false;
    bool hitChecker = false;
    
  
    if(m_mediumState = 0) {
        do{
            problem = false;
            m_initialX= randomCoord();
            m_initialY= randomCoord();
            if(m_board.m_shotGrid[m_initialX][m_initialY] != '.') problem = true;

        }while(problem);

        this-> playerTurn(m_initialX, m_initialY, p->hitCheck(m_initialX, m_initialY));
        std::cout<<p->updatePlayerShotAt(m_initialX,m_initialY);

        m_directionTracker = 0;
        m_mediumState = 1;
    } else if (m_mediumState = 1) {
        if((m_initialY - 1) >= 0 && m_directionTracker == 0 
        && m_board.m_shotGrid[m_initialY - 1][m_initialX] == '.') {
            m_directionTracker = 1;
            hitChecker = p->hitCheck(m_initialX, m_initialY - 1);
            this-> playerTurn(m_initialX, m_initialY - 1, hitChecker);
            std::cout<<p->updatePlayerShotAt(m_initialX,m_initialY - 1);
            if(hitChecker) {
                m_directionX = m_initialX;
                m_directionY = m_initialY - 1;
                m_mediumState = 2; 
            }
        } else if ((m_initialX + 1) <= 9 && m_directionTracker == 0 
        && m_board.m_shotGrid[m_initialY][m_initialX + 1] == '.') {
            m_directionTracker = 2;
            hitChecker = p->hitCheck(m_initialX+1, m_initialY);
            this-> playerTurn(m_initialX+1, m_initialY, hitChecker);
            std::cout<<p->updatePlayerShotAt(m_initialX+1,m_initialY);
            if(hitChecker) {
                m_directionX = m_initialX + 1;
                m_directionY = m_initialY;
                m_mediumState = 2;
            }
        }

    } else {

    }

}

void AI::hardPlay(player* p)//access player 1's ship array, itterate through on each turn
{
   bool problem= false;
  
  
    do{
        problem = false;
        for(int i=0; i < 10; i++)
        {
            for(int j=0; j < 10; j++)
            {
                if(p->m_board.m_shipGrid[i][j] == 'o')
                {
                    m_initalX= j;
                    m_initialY= i;
                    break;
                }
            }
        }
        
        if(m_board.m_shotGrid[m_initalX][m_initialY] != '.') problem = true;

    }while(problem);

    this-> playerTurn(m_initalX, m_initialY, p->hitCheck(m_initalX, m_initialY));
    std::cout<<p->updatePlayerShotAt(m_initalX,m_initialY);
}

void AI::aiTurn(player* p)
{
    if(m_difficulty == 0) {
        easyPlay(p);
    } else if (m_difficulty == 1) {
        mediumPlay(p);
    } else {
        hardPlay(p);
    }
}

int AI::randomCoord()
{
    srand(time(NULL));

    return (rand() % 10);
}

int AI::randomOrien()
{
    srand(time(NULL));

    return (rand() % 2);

}