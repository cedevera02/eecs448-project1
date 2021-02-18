#include"game.h"
#include<iostream>
#include <string>

using namespace std;

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
    string name = '';
    string name0 = '';
    string shipCount = '';
    string shipCount0 = '';

    cout << "Player 1, please input your name: " >> name;
    cout << "\nPlease enter the number of ships you could like to have?(1-6)" >> shipCount;
    m_player1 = new player(name, stoi(shipCount););

    cout << "Player 2, please input your name: " >> name0;
    cout << "\nPlease enter the number of ships you could like to have?(1-6)" >> shipCount0;
    m_player2 = new player(name0, stoi(shipCount0););
}
void game::shipIO(player* p)
{
    string xLocation1, yLocation1, orientation1;
    string xLocation2, yLocation2, orientation2;

    for (int i = 0; i < m_player1 -> m_shipCount; i++)
    {
        cout<< "What x - position would you like to place your "<<i+1<<" x "<<i+1<<" ship: ";
        cin>> xLocation1;
        cout<< "What y - position would you like to place your "<<i+1<<" x "<<i+1<<" ship: ";
        cin>> yLocation1;
        cout<< "What orientation would you like to place your "<<i+1<<" x "<<i+1<<" ship: ";
        cin>> orientation1;
        m_player1 -> m_ships = new ship(i+1 , orientation1, stoi(xLocation1), stoi(yLocation1));
    }

    for (int i = 0; i < m_player2 -> m_shipCount; i++)
    {
        cout<< "What x - position would you like to place your "<<i+1<<" x "<<i+1<<" ship: ";
        cin>> xLocation2;
        cout<< "What y - position would you like to place your "<<i+1<<" x "<<i+1<<" ship: ";
        cin>> yLocation2;
        cout<< "What orientation would you like to place your "<<i+1<<" x "<<i+1<<" ship: ";
        cin>> orientation2;
        m_player2 -> m_ships = new ship(i+1 , orientation2, stoi(xLocation2), stoi(yLocation2));
    }
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
