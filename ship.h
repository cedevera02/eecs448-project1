#ifndef SHIP_H
#define SHIP_H

///Each ship will be placed differently and a class is needed to organize this information.
///
///Ships will each have an size, orientation and coordinates to be documented. As the game progresses they will also take damage and
/// be destroyed. This class helps determine that information so it can be used and altered in different classes such as game.

class ship
{
    private:
    int m_size;//vales from 1-6
    bool m_orien;//true - horizontal, false - vertical
    //locations given my upper left most coordinate
    int m_xLoc;//values from 0-9
    int m_yLoc;//values from 0-9
    int m_shipHitCount;//values from 0-size, if shipHitCount==size then ship is sunk

    public:
    ship(int size, bool orien, int xLoc, int yLoc);
    void incrementShipHitCount();
    bool sinkCheck();//returns true if ship is sunk, false otherwise

    int getSize();
    bool getOrien();
    int getXLoc();
    int getYLoc();
};
#endif
