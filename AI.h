#ifndef AI_H
#define AI_H
#include "player.h"

/// AI is a subclass of the Player class. It  instantiates an AI object when user wants to play with AI and
///handles the AI easy, medium, and hard levels.

class AI: public player
{
public:
    AI(int shipCount, int difficulty); 

    ~AI();

    void easyPlay(player* p); ///pass in player one to these
                            ///If user chooses easy AI, this will be called. AI shoots randomly.

    void mediumPlay(player* p); //i think these three plays should essentially just be like a single turn the AI takes
                                ///If user chooses medium AI, this will be called. If AI shoots and hits, then AI continues to shoot around that location.

    void hardPlay(player* p); ///If user chooses hard AI, this will be called. AI knows where ships are and shoot at them. 

    int randomCoord(); /// creates a random number

    int randomOrien(); /// creates a random orientation

    void aiTurn(player* p); ///this will call the different turn (play) types


    int getDifficulty() const; /// for testing

    bool getFailChecker() const; /// helper method for MediumPlay. Returns a boolean value for failChecker

    bool canFireUp(int xCoord, int yCoord) const; /// helper method for MediumPlay. Returns true for if AI can fire above last hit. 

    bool canFireRight(int xCoord, int yCoord) const;/// helper method for MediumPlay. Returns true for if AI can fire right of last hit.

    bool canFireDown(int xCoord, int yCoord) const; /// helper method for MediumPlay. Returns true for if AI can fire below of last hit.

    bool canFireLeft(int xCoord, int yCoord) const; /// helper method for MediumPlay. Returns true for if AI can fire left of last hit.


private:
/*
    std::string m_name;///< the name of the player
    int m_shipCount;///< how many ships does the player have
    int m_sinkCount;///< how many of their own ships have been sunk
    ship** m_ships;///< an array of ships
*/
    int m_initialX; ///< x coordinate for AI
    int m_initialY; ///< y coordinate for AI

    int m_directionX; ///< direction of x 
    int m_directionY; ///< y coordinate for AI

    int m_directionTracker; ///< 0,1,3,4 up down right left. Tracks clockwise direction for AI Firing in Mediumplay
    int m_difficulty;///<0 is easy, 1 is medium, 2 is hard

    int m_mediumState;///<keeps track of what the mediumPlay should go on the next turn
    int m_incNum; ///<Increment number for coordinates clockwise around a hit.
    bool m_contChecker;///<Keeps track of if the medium AI should continue in a direction, false if they get a miss 
    bool m_failChecker; ///<Ensures that the AI will try to fire again if the current location can't be fired at

    int m_oppsShipsSunk;///< Count of player's ships that AI sunk.




};
#endif