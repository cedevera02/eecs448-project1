#include "AI.h"
#include <stdlib.h> //srand and rand from here
#include <time.h> //this allows us to get the time to generate a random seed using srand

AI::AI(int shipCount)
{
    m_sinkCount = 0;
    m_name = "AI";
    m_shipCount = shipCount;
    m_ships = new ship* [m_shipCount];
    for(int i=0; i<m_shipCount; i++)
    {
        m_ships[i] = nullptr;
    }
}



int AI::randomCoord()
{
    srand(time(NULL));

    return (rand() % 10);
}