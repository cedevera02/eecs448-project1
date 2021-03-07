#include"player.h"

/// player constructor, initializes member variables to input params.
///
///@param name then name of the player, i.e "John".
///@param shipCount How many ships the player selects (expected value 1-6).
player::player(std::string name, int shipCount)
{
    m_sinkCount = 0;
    m_name = name;
    m_shipCount = shipCount;
    m_ships = new ship* [m_shipCount];
    for(int i=0; i<m_shipCount; i++)
    {
        m_ships[i] = nullptr;
    }
}

player::player()
{
    
}

///Simple destructor for the heap allocated array.
player::~player()
{
    for(int i=0; i<m_shipCount; i++)
    {
        delete m_ships[i];
    }
    delete m_ships;
}

int player::getSinkCount()
{
    return m_sinkCount;
}

///Main logic for ships and their placement.
///
///checks for valid input, if valid: creates a ship object in the m_ships array, then places the ship into the shipGrid, does nothing on invalid input.
///parameters are the same as the constructor.
///@return true - input is valid and ship was placed, false - invalid input.
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
}

//returns "HIT!", "Miss", "Ship of size <s> destroyed!"
///allows a player to shoot a shot and updates the player's shot grid.
///
///@param hitCheck from the game class, true is passed in if the shot was a hit, false if miss
///@param x the x coord that was selected
///@param y the y coord that was selected
void player::playerTurn(int x, int y, bool hitCheck)
{
    if(hitCheck == true) m_board.m_shotGrid[y][x] = 'X';
    else m_board.m_shotGrid[y][x] = 'O';
}

///checks for valid input.
///
///@param x takes in x coord to check
///@param y takes in y coord to check
///@return true for valid input, false otherwise
bool player::shoot(int x, int y)
{
    if(x < 0 || x > 9) return false;
    if(y < 0 || y > 9) return false;
    if(m_board.m_shotGrid[y][x] != '.') return false;
    else return true;
}

///When a player is attacked, this function updates the ship grid of the player that is being attacked.
///
///during player1's turn, this will be called on player2 to update their board and ships, and get information about the shot.
///@param x takes in x coord to update
///@param y takes in y coord to update
///@return "**HIT!**", "**Miss**", "Ship of size <s> destroyed!"
std::string player::updatePlayerShotAt(int x, int y)
{
    if(hitCheck(x,y) == true)
    {
        m_board.m_shipGrid[y][x] = '!';//update ship grid
        int temp = updateShip(x,y);//update ships returns an int if a ship is destroyed
        if(temp != 0)
        {
            return ("HIT! Ship of size " + std::to_string(temp) + " destroyed!");
        }
        else return "**HIT**";
    }
    else return "**Miss**";
}


///Checks to see if a shot was a hit.
///
///@param x takes in x coord to check
///@param y takes in y coord to check
///@return true if hit, false otherwise
bool player::hitCheck(int x, int y)
{
    if(m_board.m_shipGrid[y][x] == 'o') return true;
    else return false;
}

//updates the ships if any have been hit
///updates the ships if any have been hit.
///
///@param x takes in x coord to check
///@param y takes in y coord to check
///@return 0 if no ship was sunk, the size of the the hit ship if it was sunk from that turn
int player::updateShip(int x, int y)
{
    ship* s = shipIdentifier(x,y);
    s -> incrementShipHitCount();
    if(s -> sinkCheck() == true)
    {
        m_sinkCount++;
        return s -> getSize();
    }
    else return 0;
}

///given a coordinate, find the ship that occupies that coordinate.
///returns the ship that occupies the coordinates (x,y).
///
///@param x takes in x coord to check
///@param y takes in y coord to check
///@return a pointer to the ship that occupies the input coordinates
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

///checks if the player has lost i.e. (shipCount == sinkCount).
///@return true if the player loses (shipCount == sinkCount), false otherwise
bool player::loserCheck()
{
    if( m_shipCount == m_sinkCount) return true;
    else return false;
}

///gathers the full board of the player.
///@return a string of the formatted board
std::string player::printBoard()
{
    return m_board.drawFullBoard();
}

///gathers the ship board of the player.
///@return a string of the formatted board
std::string player::printShipBoard()
{
    return m_board.drawShipBoard();
}

///Getter for member variable
///@return the shipCount of the player
int player::getShipCount()
{
    return m_shipCount;
}

///Getter for member variable
///@return a string of the name of the player
std::string player::getName()
{
    return (m_name);
}
