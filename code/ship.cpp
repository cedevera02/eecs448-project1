#include"ship.h"
//CONSTRUCTOR
///This constructor houses important variables used in player and game.
///
///@param size This takes in the value (expected to be 1-6) for the ship
///@param orien Horizontal == true, vertical == false
///@param xLoc Marks the upper-left coordinate of the ship
///@param yLoc Marks the upper-left coordinate of the ship
ship::ship(int size, bool orien, int xLoc, int yLoc)
{
    m_size = size;
    m_orien = orien;
    m_xLoc = xLoc;
    m_yLoc = yLoc;
    m_shipHitCount = 0;
}

//METHODS
///The shipCount member will be incremented by one when called.
void ship::incrementShipHitCount()
{
    m_shipHitCount = m_shipHitCount + 1;
}

///This will check if the ship is sunk.
///
///@return True if ship is sunk, false if not.
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
///@return the size of the ship
int ship::getSize()
{
    return(m_size);
}

/// gets orientation and returns orientation.
///@return the orientation of the ship
bool ship::getOrien()
{
    return(m_orien);
}

/// gets x locations and returns it.
///@return the x coordinate of the ship
int ship::getXLoc()
{
    return(m_xLoc);
}

///gets y location and returns it.
///@return the y coordinate of the ship
int ship::getYLoc()
{
    return(m_yLoc);
}
