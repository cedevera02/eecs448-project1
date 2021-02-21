#include"ship.h"
//CONSTRUCTOR
///This constructor houses important variables used in player and game.
///
///@param size This taxes the value 1x(1-6) for the ship
///@param orien This helps determine if the ship is placed horizantal or vertical
///@param xLoc helps find the upper left coordinate of the ship
///@param yLoc helps find the upper left coordinates of the ship

ship::ship(int size, bool orien, int xLoc, int yLoc)
{
    m_size = size;
    m_orien = orien;
    m_xLoc = xLoc;
    m_yLoc = yLoc;
    m_shipHitCount = 0;
}

//METHODS
///The ship count will be incremented by one when called.

void ship::incrementShipHitCount()
{
    m_shipHitCount = m_shipHitCount + 1;
}

///This will check if the ship is sunk.
///
///returns rue if ship is sunk, false if not.

bool ship::sinkCheck()//returns true if ship is sunk, false otherwise
{
    if (m_shipHitCount == m_size){
        return true;
    }
    else{
        return false;
    }
}
//GETTERS

///Gets size and returns that size.

int ship::getSize()
{
    return(m_size);
}

/// gets orientation and returns orientation.

bool ship::getOrien()
{
    return(m_orien);
}

/// gets x locations and returns it.
int ship::getXLoc()
{
    return(m_xLoc);
}

///gets y location and returns it.

int ship::getYLoc()
{
    return(m_yLoc);
}
