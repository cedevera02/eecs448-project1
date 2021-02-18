#include"ship.h"
//CONSTRUCTOR
ship::ship(int size, bool orien, int xLoc, int yLoc)
{
    m_size = size;
    m_orien = orien;
    m_xLoc = xLoc;
    m_yLoc = yLoc;
    m_shipHitCount = 0;
}
//METHODS
void ship::incrementShipHitCount()
{
    m_shipHitCount = m_shipHitCount + 1;
}
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
int ship::getSize()
{
    return(m_size);
}
bool ship::getOrien()
{
    return(m_orien);
}
int ship::getXLoc()
{
    return(m_xLoc);
}
int ship::getYLoc()
{
    return(m_yLoc);
}