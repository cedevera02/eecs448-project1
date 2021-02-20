#ifndef BOARD_H
#define BOARD_H
#include<string>

class board
{
    public:
    char m_shotGrid[10][10];//'.' - empty spot, '0' - miss, 'X' - hit
    char m_shipGrid[10][10];//'.' - emtpty spot, 'o' - ship, '!' - hit ship
    board();
    std::string drawShipBoard();//returns a string of the ship board to be outputted, this will be used when the user is placing ships
    std::string drawFullBoard();//returns a string of both boards to be printed

};
#endif