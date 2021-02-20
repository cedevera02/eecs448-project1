#include"game.h"

using namespace std;

game::game()
{
    m_gameOver = false;
    m_tempX = 0;
    m_tempY = 0;
    m_player1 = nullptr;
    m_player2 = nullptr;

    m_clearScreenString = "";
    for(int i=0; i<70;i++)//we construct this string once, that way we don't have to run the loop
    {//every time we want to clear the screen
        m_clearScreenString += "\n";
    }
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
void game::testPlay()//creates 2 players with 3 ships each
{//ships are placed in upper left corner of the board horizontally
    m_player1 = new player("p1", 3);
    m_player2 = new player("p2", 3);
    for(int i=0; i < 3; i++)
    {
        m_player1 -> buildAndPlaceShip(i, true, 0, i);
        m_player2 -> buildAndPlaceShip(i, true, 0, i);
    }

    while(m_gameOver == false)
    {
        fullTurn();
    }
    closingScreen();
}
void game::setUp()
{
    setUpIO();

    shipIO(m_player1);
    switchPlayerPrompt();
    shipIO(m_player2);
}
void game::setUpIO()
{
    string name = "";
    string name0 = "";
    string shipCount = "";
    string shipCount0 = "";

    cout << "Player 1, please input your name: ";
    cin >> name;
    cout << "Please enter the number of ships you could like to have? (1-6): ";
    cin >> shipCount;
    m_player1 = new player(name, stoi(shipCount));

    cout << "Player 2, please input your name: ";
    cin>> name0;
    cout << "Please enter the number of ships you could like to have? (1-6): ";
    cin>> shipCount0;
    m_player2 = new player(name0, stoi(shipCount0));
}

void game::shipIO(player* p)
{
    int ASCII_OFFSET = 65;
    int xLocTemp, yLocTemp;
    bool orienTemp;
    string coordinatesTemp, orientationInputTemp;

    cout<< p -> printShipBoard();
    cout<<"\nNow placing ships for "<<p -> getName()<<": \n";
    for (int i = 0; i < p -> getShipCount(); i++)
    {
        cout<< "\nPlacing ship of size "<<i+1<<": \n";
        cout<< "Would you like your ship to be veritcal or horizontal? (H/V): ";
        cin>> orientationInputTemp;
        cout<< "To place your ship, enter the coordinate of the upper-left most slot: ";
        cin>> coordinatesTemp;
        
        xLocTemp = (int)toupper(coordinatesTemp[0]) - ASCII_OFFSET;
        coordinatesTemp.erase(0,1);
        yLocTemp = stoi(coordinatesTemp) - 1;

        p -> buildAndPlaceShip(i+1, (orientationInputTemp == "H"), xLocTemp, yLocTemp);
        cout<< p -> printShipBoard();
    }
}
void game::fullTurn()
{
//PLAYER1 TURN
    turnIO(m_player1);//gathers input and prints player boards
    m_player1 -> playerTurn(m_tempX, m_tempY, m_player2 -> hitCheck(m_tempX, m_tempY) );//updates the player's boards and prints the result of the shot
    std::cout<<m_player2 -> updatePlayerShotAt(m_tempX, m_tempY);//updates the opposing player's boards and prints the result of the shot
    m_gameOver = m_player2-> loserCheck();
    switchPlayerPrompt();
    clearScreen();
//PLAYER2 TURN
    if(m_gameOver == false)
    {
        turnIO(m_player2);//gathers input and prints player boards
        m_player2 -> playerTurn(m_tempX, m_tempY, m_player1 -> hitCheck(m_tempX, m_tempY));//updates the player's boards and prints the result of the shot
        std::cout<<m_player1 -> updatePlayerShotAt(m_tempX, m_tempY);//updates the opposing player's boards and prints the result of the shot
        m_gameOver = m_player1-> loserCheck();
        switchPlayerPrompt();
        clearScreen();
    }
}
void game::turnIO(player* p)
{
    int ASCII_OFFSET = 65;
    string coordinatesTemp = "";
    
    cout<< p -> printBoard();
    cout << "Please enter a coordinate (ex. F8): ";
    
    m_tempX = (int)toupper(coordinatesTemp[0]) - ASCII_OFFSET;
    coordinatesTemp.erase(0,1);
    m_tempY = stoi(coordinatesTemp) - 1;
}
void game::closingScreen()
{
    if( m_player1->loserCheck() == true)
    {
        cout << "Congratulations " << m_player2->getName() << ", you have won!\n\n";
    }
    else
    {
        cout << "Congratulations " << m_player1->getName() << ", you have won!\n\n";
    }

    // cout << "       _      _\n";
    // cout << "      (_)    | |\n";
    // cout << "__   ___  ___| |_ ___  _ __ _   _\n";
    // cout << "\ \ / / |/ __| __/ _ \| '__| | | |\n";
    // cout << " \ V /| | (__| || (_) | |  | |_| |\n";
    // cout << "  \_/ |_|\___|\__\___/|_|   \__, |\n";
    // cout << "                             __/ |\n";
    // cout << "                            |___/\n";
}

void game::clearScreen()
{
    std::cout<<m_clearScreenString;
}
void game::switchPlayerPrompt()
{
    std::string dummy;
    std::cout<<"\nPress enter when the next player is ready: ";
    std::getline(std::cin, dummy);
}
