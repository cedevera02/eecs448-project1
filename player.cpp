#include"player.h"
#include"board.h"
#include"game.h"
#include <iostream>

player::player(std::string name, int shipCount)
{
    m_name = name;
    m_shipCount = shipCount;
    m_ships = new ship * [m_shipCount];
}
player::~player()
{
    for (int i = 0; i < m_shipCount; i++)
    {
        delete m_ships[i];
    }
    delete m_ships;
}

bool player::buildAndPlaceShip(int size, bool orien, int xLoc, int yLoc)
{
    bool isvalid = true;
    int tempx = xLoc;
    int tempy = yLoc;
    if (orien == true)
    {
  
        //board b;
        if (tempx < 10 && tempy < 10) {
            for (int i = 0; i < size; i++)
            {
                if (tempx < 10 && tempy < 10) {
                    if (m_board.m_shipGrid[tempx][tempy] == '.')
                    {
                       // m_board.m_shipGrid[tempx][tempy] = 'o';
                        tempx = tempx + 1;
                    }
                    else {
                        isvalid = false;
                        return isvalid;
                        //std::cout << "spot is occupied";
                    }
                }
                else {
                    isvalid = false;
                    return isvalid;
                    //std::cout << "Invalid option ; beyond the board boundary";
                }

            }
        }
        else {
            isvalid = false;
            return isvalid;
            //std::cout << "Invalid option";
        }
    }
    else {


        //board b;
        if (tempx < 10 && tempy < 10) {
            for (int i = 0; i < size; i++)
            {
                if (tempx < 10 && tempy < 10) {
                    if (m_board.m_shipGrid[tempx][tempy] == '.')
                    {
                       // m_board.m_shipGrid[tempx][tempy] = 'o';
                        tempy = tempy + 1;
                    }
                    else {
                        isvalid = false;
                        return isvalid;
                       /* std::cout << "spot is occupied";*/
                    }
                }
                else {
                    isvalid = false;
                    return isvalid;
                 //   std::cout << "Invalid option ; beyond the board boundary";
                }

            }
        }
        else {
            isvalid = false;
            return isvalid;
           /* std::cout << "Invalid option";*/
        }

    }
    if (orien == true) {
        for (int i = 0; i < size; i++)
        {

            if (m_board.m_shipGrid[tempx][tempy] == '.')
            {
                m_board.m_shipGrid[tempx][tempy] = 'o';
                tempx = tempx + 1;
            }
        }
    }
    else {
        for (int i = 0; i < size; i++)
        {

            if (m_board.m_shipGrid[tempx][tempy] == '.')
            {
                m_board.m_shipGrid[tempx][tempy] = 'o';
                tempy = tempy + 1;
            }
        }
    }
    return isvalid;
}

//returns "HIT!", "Miss", "Ship of size <s> destroyed!"
void player::playerTurn(int x, int y)
{

}
//returns true for valid input, false otherwise
bool player::shoot(int x, int y)
{
    //if (x < 0 || x > 9) return false;
    //if (y < 0 || y > 9) return false;
    //if (board::m_shotGrid[x][y] != '.') return false;
    //else 
        return true;
}
//returns "**HIT!**", "**Miss**", "Ship of size <s> destroyed!"
//when the opponent attacks, this function updates the ship grid of the player that is being attacked
std::string player::updatePlayerShotAt(int x, int y)
{
    return "hit";// Sandhya
}
//returns true if hit, false otherwise
bool player::hitCheck(int x, int y)
{
    return true; // sandhya
}
//updates the ships if any have been hit
void updateShips()
{

}
//returns the ship that occupies the coordinates (x,y)
ship player::shipIdentifier(int x, int y)
{
    ship s(1,true,x,y);
    return s;
}
//retuns true if the player loses (shipCount == sinkCount), false otherwise
bool player::loserCheck()
{
    return true;
}
//returns the full board of the player
std::string player::printBoard()
{
    return m_board.drawFullBoard();
}

std::string player::printShipBoard()
{
    return m_board.drawShipBoard();
}

int player::getShipCount()
{
    return m_shipCount;
}

void player::setName()
{

}

std::string player::getName()
{
    return (m_name);
}
