#include"player.h"

player::player(std::string name, int shipCount)
{
    m_name = name;
    m_shipCount = shipCount;
    m_ships = new ship* [m_shipCount];
}
player::~player()
{
    for(int i=0; i<m_shipCount; i++)
    {
        delete m_ships[i];
    }
    delete m_ships;
}

bool player::buildAndPlaceShip(int size, bool orien, int xLoc, int yLoc)
{

}
//returns "HIT!", "Miss", "Ship of size <s> destroyed!"
void player::playerTurn(int x, int y, bool hitCheck)
{

}
//returns true for valid input, false otherwise
bool player::shoot(int x, int y)
{
    if(x < 0 || x > 9) return false;
    if(y < 0 || y > 9) return false;
    if(m_board.m_shotGrid[x][y] != '.') return false;
    else return true;
}
//returns "**HIT!**", "**Miss**", "Ship of size <s> destroyed!"
//when the opponent attacks, this function updates the ship grid of the player that is being attacked
std::string player::updatePlayerShotAt(int x, int y)
{

}
//returns true if hit, false otherwise
bool player::hitCheck(int x, int y)
{

}
//updates the ships if any have been hit
void updateShips()
{

}
//returns the ship that occupies the coordinates (x,y)
ship player::shipIdentifier(int x, int y)
{

}
//retuns true if the player loses (shipCount == sinkCount), false otherwise
bool player::loserCheck()
{

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
