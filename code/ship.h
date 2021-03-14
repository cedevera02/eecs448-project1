#ifndef SHIP_H
#define SHIP_H

///Each ship will be placed differently and a class is needed to organize this information.
///
///Ships will each have a size, orientation and coordinates to be stored. As the game progresses they will also take damage and
/// be destroyed. This class helps determine that information so it can be used and altered from different classes such as game.

class ship
{
    private:
    int m_size;///< values from 1-6
    bool m_orien;///< true - horizontal, false - vertical
    //locations given by upper left most coordinate
    int m_xLoc;///< values from 0-9
    int m_yLoc;///< values from 0-9
    int m_shipHitCount;///< values from 0-size, if shipHitCount==size then ship is sunk

    public:
    ship(int size, bool orien, int xLoc, int yLoc);///< ship object constructor, sets ships size, orientation, and position
    void incrementShipHitCount();///< increases shipHitCount when called
    bool sinkCheck();///< returns true if ship is sunk, false otherwise

    int getSize();///< returns size of ship when called
    bool getOrien();///< returns orientation of ship when called
    int getXLoc();///< returns x coordinate of ship when called
    int getYLoc();///< returns y coordinate of ship when called
};
#endif
