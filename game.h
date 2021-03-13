#ifndef GAME_H
#define GAME_H
#include"player.h"
#include "AI.h"
#include "ship.h"
#include<iostream>

///< /game is the driver class that handles all IO and pieces everything together.
///< /
///< /This class is the most vital class to the project. It will take in its own parameters as well as use parts of the player, board and ship classes.
///< /Throughout the class many values for the game to progress will be created stored and used. This main logic is stored here.

class game
{
    private:
    bool m_gameOver;///<  true if a winner has been declared
    std::string m_clearScreenString;///<  a string of "\n"'s stored so it only has to be constructed once
    int m_tempX;///<  a variable to store the corrinate for the current turn
    int m_tempY;///<  a variable to store the corrinate for the current turn
	std::string useMissile;///<  string that stored player choice of use missile or not
    bool m_missileGame;
    int m_mode;///<  a variable to store the mode of the game (0 for AI off, 1 for AI on)

    public:
    player* m_player1;///<  a pointer to a player that will be created at runtime
    player* m_player2;///<  a pointer to a player that will be created at runtime
    game();///<  game constructor, sets some of the more important variables and helps limit loops.
    ~game();///<  game deconstrunctor
    AI* m_player2AI;///<  a pointer to the AI player that will be created if the user chooses to play with AI
    void play();///<  the main game loop
    void testPlay();///<  runs the game but skips the set up to speed up testing
    void setUp();///<  get the names of the players and place their ships
        void setUpIO();///<  takes in the player being modified, gets the names of the a player and their number of ships
        int aiSetUpIO();///<   
        void shipIO(player* p);///< takes in the player being modified, allows the user to place their ships
        void aiShipIO(AI* p);
    void fullTurn();///< a full turn occurs after both players finish their turn
        void turnIO(player* p);///< takes in the player being modified, gathers the input for a half turn, sets m_shotX and m_shotY, prints full board
    void closingScreen();///< after a winner has been determined, print a closing screen stating the winner
    void clearScreen();///< prints 70 "\n"'s to clear the screen
    void switchPlayerPrompt();///< waits to press enter before switching players
    void finishSetUpPrompt();///< lets the users know set up is complete and the battle is beginning
    void finishTurnPrompt();
    bool isStringInt(std::string s);
    bool isStringLetter(std::string s);
    void missileTurn(player* current, player* opposing);///< calls playerTurn but 9 times to simulate a 3x3 shot
    void missileTurnIO(player* p);///< gets input for 3x3 shot
    void missilePrompt();///< asks player if they want to fire a missile shot
    bool overlap(int xcord, int ycord, player *p); ///< checks to see if missile coordinates will have a previous hit
};
#endif
