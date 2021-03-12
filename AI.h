#ifndef AI_H
#define AI_H
#include "player.h"


class AI: public player
{
public:
    AI(int shipCount, int difficulty);

    ~AI();

    void easyPlay(player* p); //pass in player one to these

    void mediumPlay(player* p); //i think these three plays should essentially just be like a single turn the AI takes

    void hardPlay(player* p);

    int randomCoord();

    int randomOrien();

    bool randomFire(int xCoord, int yCoord);//I don't think we want this actually
    //99% sure we don't need this as I think we should just put the generated x and y coord into

    void randomShipPlace();

    void aiTurn(player* p); //this will call the different turn (play) types

    int getDifficulty() const; // for testing

    bool getFailChecker() const;

    bool canFireUp(int xCoord, int yCoord) const;

    bool canFireRight(int xCoord, int yCoord) const;

    bool canFireDown(int xCoord, int yCoord) const;

    bool canFireLeft(int xCoord, int yCoord) const;


private:
/*
    std::string m_name;///< the name of the player
    int m_shipCount;///< how many ships does the player have
    int m_sinkCount;///< how many of their own ships have been sunk
    ship** m_ships;///< an array of ships
*/
    int m_initialX;
    int m_initialY;

    int m_directionX;
    int m_directionY;

    int m_directionTracker;
    int m_difficulty;//0 is easy, 1 is medium, 2 is hard

    int m_mediumState;//keeps track of what the mediumPlay should go on the next turn
    int m_incNum;
    bool m_contChecker;
    bool m_failChecker;

    int m_oppsShipsSunk;




};
#endif