#include"board.h"
using namespace std;

/// This is the Constructor for the board class.
///
/// This will initialize much of what will be used to create and print boards. In setUpIO and shipIO,
/// many references to this code and shot/ship grid will be made.
board::board()
{
    for(int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            m_shipGrid[i][j] = '.';
            m_shotGrid[i][j] = '.';
        }
    }
}
//returns a string of the ship board to be outputted
//this will be used in the beginning of the game when the user is placing ships
///Creating board for ships.
///
///Using strings it is possible to output our board more efficiently. This will be all the data behind the actual boards.
///returns a string to format the board.

std::string board::drawShipBoard()
{
    std::string finalString = "\nShip board: \n";
    finalString +="   A B C D E F G H I J\n";
    for(int i=0;i<10;i++)
    {
        finalString += to_string(i + 1) + " ";
        if(i != 9) finalString += " ";
        for(int j=0;j<10;j++)
        {
            finalString += (m_shipGrid[i][j] + std::string(" "));
        }
        finalString += "\n";
    }
    return finalString;
}
//concatenate strings with "\n" to a create a block string
//returns a string of both boards to be printed
//this will be used once the game begins

///Creates two boards that display shots and ships respectively.
///
///The board is created two separate times so data can be mapped and displayed to the player during the game.
///returns string that combines both of the boards together.

std::string board::drawFullBoard()
{
    std::string finalString = "\nShot board: \n";
    finalString += "   A B C D E F G H I J\n";
    for(int i=0;i<10;i++)
    {
        finalString += to_string(i + 1) + " ";
        if(i != 9) finalString += " ";
        for(int j=0;j<10;j++)
        {
            finalString += (m_shotGrid[i][j] + std::string(" "));
        }
        finalString += "\n";
    }

    finalString += "\n=========================\n";

    finalString += "\nShip board: \n";
    finalString += "   A B C D E F G H I J\n";
    for(int i=0;i<10;i++)
    {
        finalString += to_string(i + 1) + " ";
        if(i != 9) finalString += " ";
        for(int j=0;j<10;j++)
        {
            finalString += (m_shipGrid[i][j] + std::string(" "));
        }
        finalString += "\n";
    }

    finalString += "\n";
    return finalString;
}
