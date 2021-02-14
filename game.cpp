#include"game.h"
#include<iostream>

game::game()
{
    m_gameOver = false;
}
game::~game()
{
    delete m_player1;
    delete m_player2;
}
//the main game loop
void game::play()
{
    setUp();
    while(m_gameOver == false)
    {
        fullTurn();
    }
    closingScreen();
}
void game::setUp()
{
    setUpIO(m_player1);
    shipIO(m_player1);

    setUpIO(m_player2);
    shipIO(m_player2);
}
void game::setUpIO(player* p)
{

}
void game::shipIO(player* p)
{

}
void game::fullTurn()
{
//PLAYER1 TURN
    turnIO(m_player1);//gathers input and prints player boards
    m_player1 -> playerTurn(m_tempX, m_tempY);//updates the player's boards and prints the result of the shot
    std::cout<<m_player2 -> updatePlayerShotAt(m_tempX, m_tempY);//updates the opposing player's boards and prints the result of the shot
    m_gameOver = m_player2-> loserCheck();
    switchPlayerPrompt();
    clearScreen();
//PLAYER2 TURN
    if(m_gameOver == false)
    {
        turnIO(m_player2);//gathers input and prints player boards
        m_player2 -> playerTurn(m_tempX, m_tempY);//updates the player's boards and prints the result of the shot
        std::cout<<m_player1 -> updatePlayerShotAt(m_tempX, m_tempY);//updates the opposing player's boards and prints the result of the shot
        m_gameOver = m_player1-> loserCheck();
        switchPlayerPrompt();
        clearScreen();
    }
}
void game::turnIO(player* p)
{
//check for valid input using player.shoot() method
}
void game::closingScreen()
{

}
void game::clearScreen()
{
    std::string s = "";
    for(int i=0; i<70;i++)
    {
        s += "\n";
    }
    std::cout<<s;
}
void game::switchPlayerPrompt()
{

}