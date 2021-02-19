#include"game.h"

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
    setUpIO();

    shipIO(m_player1);
    shipIO(m_player2);
}
void game::setUpIO()
{
    string name = "";
    string name0 = "";
    string shipCount = "";
    string shipCount0 = "";
    
    bool successInput = false;

    cout << "Player 1, please input your name: ";
    cin >> name;
    cout << "Please enter the number of ships you could like to have? (1-6): ";
    
    //adding in some exception handling
    
     while(!successInput) //Runs until user gives a proper input
    {
        cin >> shipCount;

        try
        {
            m_player1 = new player(name, stoi(shipCount));
            if( stoi(shipCount) > 6 || stoi(shipCount) < 1 ) { //Checks 1-6 constraint
                cout << "Please enter a number from 1-6 only";
            }
            else {
                successInput = true;
            }
        }
        catch(const std::exception& e) //Runs if user inputs anything but a number
        {
            std::cerr << "Please enter a number" << '\n';
        }
    }

    successInput = false; //Reset success flag

    cout << "Player 2, please input your name: ";
    cin>> name0;
    cout << "Please enter the number of ships you could like to have? (1-6): ";
    
    while(!successInput) //Handle exceptions again
    {
        cin >> shipCount0;

        try
        {
            m_player2 = new player(name, stoi(shipCount0));
            if( stoi(shipCount0) > 6 || stoi(shipCount0) < 1 ) {
                cout << "Please enter a number from 1-6 only";
            }
            else {
                successInput = true;
            }
        }
        catch(const exception &e)
        {
            cout << "Please enter a number";
        }
    }
}

void game::shipIO(player* p)
{
    int ASCII_OFFSET = 65;
    int xLocTemp, yLocTemp;
    bool orienTemp;
    string coordinatesTemp, orientationInputTemp;

    cout<<"Now placing ships for "<<p -> getName()<<"\n";
    for (int i = 0; i < p -> getShipCount(); i++)
    {
        cout<< p -> printShipBoard();
        cout<< "\nPlacing ship of size "<<i+1<<": \n\n";
        cout<< "Would you like your ship to be veritcal or horizontal? (H/V): ";
        cin>> orientationInputTemp;
        cout<< "To place your ship, enter the coordinate of the upper-left most slot: ";
        cin>> coordinatesTemp;
        
        xLocTemp = (int)toupper(coordinatesTemp[0]) - ASCII_OFFSET;
        yLocTemp = stoi(to_string((coordinatesTemp[1])) ) - 1;

        p -> buildAndPlaceShip(i+1, (orientationInputTemp == "H"), xLocTemp, yLocTemp);
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
