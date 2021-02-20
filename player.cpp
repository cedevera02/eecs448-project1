#include"player.h"

player::player(std::string name, int shipCount)
{
    m_name = name;
    m_shipCount = shipCount;
    m_ships = new ship* [m_shipCount];
    for(int i=0; i<m_shipCount; i++)
    {
        m_ships[i] = nullptr;
    }
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
    if(orien == true)//horizontal
    {
        for(int i = 0; i < size; i++)
        {
            if( (xLoc + i) > 9 || (xLoc + i) < 0) return false;
            if( m_board.m_shipGrid[yLoc][xLoc + i] == 'o') return false;
        }
    }
    else//vertical
    {
        for(int i = 0; i < size; i++)
        {
            if( (yLoc + i) > 9 || (yLoc + i) < 0) return false;
            if( m_board.m_shipGrid[yLoc + i][xLoc] == 'o') return false;
        }
    }
    //input is valid, now we build and place the ship
    m_ships[size-1] = new ship(size, orien, xLoc, yLoc);//build
    for(int i=0; i < size; i++)//place into grid
    {
        if(orien == true)
        {
            m_board.m_shipGrid[yLoc][xLoc + i] = 'o';
        }
        else
        {
            m_board.m_shipGrid[yLoc + i][xLoc] = 'o';
        }
    }
    return true;

//     if (orien == true)
//     {
//         if (tempx < 10 && tempy < 10) {
//             for (int i = 0; i < size; i++)
//             {
//                 if (tempx < 10 && tempy < 10) {
//                     if (m_board.m_shipGrid[tempx][tempy] == '.')
//                     {
//                        // m_board.m_shipGrid[tempx][tempy] = 'o';
//                         tempx = tempx + 1;
//                     }
//                     else {
//                         isvalid = false;
//                         return isvalid;
//                         //std::cout << "spot is occupied";
//                     }
//                 }
//                 else {
//                     isvalid = false;
//                     return isvalid;
//                     //std::cout << "Invalid option ; beyond the board boundary";
//                 }

//             }
//         }
//         else {
//             isvalid = false;
//             return isvalid;
//             //std::cout << "Invalid option";
//         }
//     }
//     else {


//         //board b;
//         if (tempx < 10 && tempy < 10) {
//             for (int i = 0; i < size; i++)
//             {
//                 if (tempx < 10 && tempy < 10) {
//                     if (m_board.m_shipGrid[tempx][tempy] == '.')
//                     {
//                        // m_board.m_shipGrid[tempx][tempy] = 'o';
//                         tempy = tempy + 1;
//                     }
//                     else {
//                         isvalid = false;
//                         return isvalid;
//                        /* std::cout << "spot is occupied";*/
//                     }
//                 }
//                 else {
//                     isvalid = false;
//                     return isvalid;
//                  //   std::cout << "Invalid option ; beyond the board boundary";
//                 }

//             }
//         }
//         else {
//             isvalid = false;
//             return isvalid;
//            /* std::cout << "Invalid option";*/
//         }

//     }
//     if (orien == true) {
//         for (int i = 0; i < size; i++)
//         {

//             if (m_board.m_shipGrid[tempx][tempy] == '.')
//             {
//                 m_board.m_shipGrid[tempx][tempy] = 'o';
//                 tempx = tempx + 1;
//             }
//         }
//     }
//     else {
//         for (int i = 0; i < size; i++)
//         {

//             if (m_board.m_shipGrid[tempx][tempy] == '.')
//             {
//                 m_board.m_shipGrid[tempx][tempy] = 'o';
//                 tempy = tempy + 1;
//             }
//         }
//     }
//     return isvalid;
// }
}
//returns "HIT!", "Miss", "Ship of size <s> destroyed!"
void player::playerTurn(int x, int y, bool hitCheck)
{
    if(hitCheck == true) m_board.m_shotGrid[x][y] = 'X';
    else m_board.m_shotGrid[x][y] = 'O';
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
    if(hitCheck(x,y) == true)
    {
        m_board.m_shipGrid[x][y] = '!';//update ship grid
        int temp = updateShip(x,y);//update ships returns an int if a ship is destroyed
        if(temp != 0)
        {
            return ("HIT! Ship of size " + std::to_string(temp) + " destroyed!");
        }
        else return "**HIT**";
    }
    else return "**Miss**";
}
//returns true if hit, false otherwise
bool player::hitCheck(int x, int y)
{
    if(m_board.m_shipGrid[x][y] == 'o') return true;
    else return false;
}
//updates the ships if any have been hit
int player::updateShip(int x, int y)
{
    ship* s = shipIdentifier(x,y);
    s -> incrementShipHitCount();
    if(s -> sinkCheck() == true) return s -> getSize();
    else return 0;
}
//returns the ship that occupies the coordinates (x,y)
ship* player::shipIdentifier(int x, int y)
{
    for(int i=0; i < getShipCount(); i++)//iterate through every ship
    {
        for(int j=0; j < m_ships[i] -> getSize(); j++)//iterate along the length of the ship
        {
            if(m_ships[i] -> getOrien() == true)//if horizontal
            {
                if(m_ships[i] -> getXLoc() + j == x && m_ships[i] -> getYLoc() == y)
                   {//check each location along the length of the ship to see if it matches the shot
                       return m_ships[i];
                   }
            }
            else//if vertical
            {
                if(m_ships[i] -> getXLoc() == x && m_ships[i] -> getYLoc() + j == y)
                   {//check each location along the length of the ship to see if it matches the shot
                       return m_ships[i];
                   }
            }
        }
    }
}
//retuns true if the player loses (shipCount == sinkCount), false otherwise
bool player::loserCheck()
{
    if( m_shipCount == m_sinkCount) return true;
    else return false;
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

std::string player::getName()
{
    return (m_name);
}
