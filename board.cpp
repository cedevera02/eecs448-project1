#include"board.h"
using namespace std;

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
std::string board::drawShipBoard()
{
    std::string finalString = "  1 2 3 4 5 6 7 8 9 10\n";
    for(int i=0;i<10;i++)
    {
        finalString += std::string(1, static_cast<char>(65 + i)) + " ";
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
std::string board::drawFullBoard()
{
    std::string finalString = "\nShot board: \n";
    finalString += "  1 2 3 4 5 6 7 8 9 10\n";
    for(int i=0;i<10;i++)
    {
        finalString += std::string(1, static_cast<char>(65 + i)) + " ";
        for(int j=0;j<10;j++)
        {
            finalString += (m_shipGrid[i][j] + std::string(" "));
        }
        finalString += "\n";
    }

    finalString += "\n=========================\n";

    finalString += "\nShip board: \n";
    finalString += "  1 2 3 4 5 6 7 8 9 10\n";
    for(int i=0;i<10;i++)
    {
        finalString += std::string(1, static_cast<char>(65 + i)) + " ";
        for(int j=0;j<10;j++)
        {
            finalString += (m_shipGrid[i][j] + std::string(" "));
        }
        finalString += "\n";
    }

    finalString += "\n";
    return finalString;
}
