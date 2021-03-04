#include "AI.h"
#include <stdlib.h> //srand and rand from here
#include <time.h> //this allows us to get the time to generate a random seed using srand
#include <iostream>

AI::AI(int shipCount, int difficulty)
{
    m_sinkCount = 0;
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
   

}

void AI::mediumPlay(player* p)
{

}

void AI::hardPlay(player* p)//access player 1's ship array, itterate through on each turn
{

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