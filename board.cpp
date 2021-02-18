#include"board.h"

board::board()
{
    for(int i = 0; i < 10; i++){
        for (int j = 0; j < 10; j++){
            m_shipGrid[i][j] = ".";
            m_shotGrid[i][j] = ".";
        }
    }
}
//returns a string of the ship board to be outputted
//this will be used in the beginning of the game when the user is placing ships
std::string board::drawShipBoard()
{
//concatenate strings with "\n" to a create a block string
    std::string finalString = "A B C D E F G H I J\n";
        for(int i=0;i<10;i++)
        {
            finalString += std::to_string(i + 1) + " ";
            for(int j=0;j<10;j++)
            {
                finalString += m_shipGrid[i][j] + " ";
            }
            finalString += "\n";
        }
        return finalString;
}
//returns a string of both boards to be printed
//this will be used once the game begins
std::string board::drawFullBoard()
{

}