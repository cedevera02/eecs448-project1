#ifndef AI_H
#define AI_H
#include "player.h"


class AI: public player
{
public:
    AI(int shipCount);

    ~AI();

    void easyPlay();

    void mediumPlay(); //i think these three plays should essentially just be like a single turn the AI takes

    void hardPlay();

    int randomCoord();

    bool randomFire(int xCoord, int yCoord);//I don't think we want this actually
    //99% sure we don't need this as I think we should just put the generated x and y coord into

    void randomShipPlace();

    void aiTurn(); //this will call the different turn (play) types



private:
    std::string m_name;///< the name of the player
    int m_shipCount;///< how many ships does the player have
    int m_sinkCount;///< how many of their own ships have been sunk
    ship** m_ships;///< an array of ships

    int m_initalX;
    int m_initialY;

    int m_directionX;
    int m_directionY;

    int m_directionTracker;
    int m_difficulty;




};
#endif