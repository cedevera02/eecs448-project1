#ifndef PLAYER_H
#define PLAYER_H
#include"board.h"
#include"ship.h"

///The player class will process most of the player specific inputs.
///
///Each player has many things attributed to them. They have their own shot and ship grids that inform them what they have done. Also this class is capable of determining a winner.
///It also handles much of what each player does in their turn.

class player
{
    protected:
    std::string m_name;///< the name of the player
    int m_shipCount;///< how many ships does the player have
    int m_sinkCount;///< how many of their own ships have been sunk
    ship** m_ships;///< an array of ships

    public:
    board m_board;///< the board object attatched to the player
    player(std::string name, int shipCount);
    player();//default
    ~player();
    bool buildAndPlaceShip(int size, bool orien, int xLoc, int yLoc);//returns true and creates new ship under m_ships on valid input, returns false and does nothing on invalid input
    void playerTurn(int x, int y, bool hitCheck);//this function updates the player's shot grid
        bool shoot(int x, int y);//returns true for valid input, false otherwise
    std::string updatePlayerShotAt(int x, int y);//returns "**HIT!**", "**Miss**", "Ship of size <s> destroyed!", updates the ships and ship board when the opponent fires
        bool hitCheck(int x, int y);//returns true if hit, false otherwise, this is called when the opponent attacks
        int updateShip(int x, int y);//if the shot is a hit, updates the ships and return the ship size if ship is sunk, returns 0 if not sunk
            ship* shipIdentifier(int x, int y);//returns the ship that occupies the coordinates (x,y)
    bool loserCheck();//retuns true if the player loses (shipCount == sinkCount), false otherwise
    std::string printBoard();//returns the full board of the player
    std::string printShipBoard();//used in shipIO

    int getShipCount();
    int getSinkCount();
    std::string getName();

};
#endif
