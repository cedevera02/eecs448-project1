#ifndef BOARD_H
#define BOARD_H
#include<string>

///This class will handle many calls to generate and read boards.
///
///In the game of battleship, seeing the board as you play is paramount. To correctly enable this feature its own class is required. This will be used to print boards on every turn after updates have been made.

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
