#include"game.h"
#include<string>

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
        m_player1 -> buildAndPlaceShip(i + 1, true, 0, i);
        m_player2 -> buildAndPlaceShip(i + 1, true, 0, i);
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
    finishTurnPrompt();
    clearScreen();
    shipIO(m_player2);
    finishTurnPrompt();
    clearScreen();

    finishSetUpPrompt();
}
void game::setUpIO()
{
    string name = "";
    string name0 = "";
    string shipCount = "";
    string shipCount0 = "";
    bool problem = false;
//PLAYER1
    do
    {
        problem = false;
        cout << "Player 1, please input your name: ";
        std::getline(std::cin, name);
        cout << "Please enter the number of ships you could like to have? (1-6): ";
        std::getline(std::cin, shipCount);

        if(!isStringInt(shipCount) || shipCount.length() == 0) problem = true;
        if(!problem)
        {
            if(stoi(shipCount) > 6 || stoi(shipCount) < 1 ) problem = true;
        }
        if(problem) std::cout<<"\n**Invalid input. Please try again.**\n";

    }while(problem);
    m_player1 = new player(name, stoi(shipCount));
    
    finishTurnPrompt();
    clearScreen();
//PLAYER2
    do
    {
        problem = false;
        cout << "Player 2, please input your name: ";
        std::getline(std::cin, name0);
        cout << "Please enter the number of ships you could like to have? (1-6): ";
        std::getline(std::cin, shipCount0);

        if(!isStringInt(shipCount0) || shipCount0.length() == 0) problem = true;
        if(!problem)
        {
            if(stoi(shipCount0) > 6 || stoi(shipCount0) < 1 ) problem = true;
        }
        if(problem) std::cout<<"\n**Invalid input. Please try again.**\n";

    }while(problem);
    m_player2 = new player(name0, stoi(shipCount0));

    finishTurnPrompt();
    clearScreen();
// shipcountcheck1:
//     if (isStringInt(shipCount)) {
//         if (stoi(shipCount) > 0 && stoi(shipCount) < 7)
//         {
//             m_player1 = new player(name, stoi(shipCount));
//         }
//         else
//         {
//             cout << "Invalid entry \n";
//             goto shipcountcheck1;
//         }
//     }
//     else
//     {
//         cout << "Invalid entry \n";
//         goto shipcountcheck1;
//     }
//     cout << "Player 2, please input your name: ";
//     std::getline(std::cin, name0);
// shipcountcheck2:
//     cout << "Please enter the number of ships you could like to have? (1-6): ";
//     std::getline(std::cin, shipCount0);
//     if (isStringInt(shipCount)) {
//         if (stoi(shipCount) > 0 && stoi(shipCount) < 7)
//         {
//             m_player2 = new player(name0, stoi(shipCount0));
//         }
//         else
//         {
//             cout << "Invalid entry \n";
//             goto shipcountcheck1;
//         }
//     }
//     else {
//         cout << "Invalid entry \n";
//         goto shipcountcheck2;
//     }

}
void game::shipIO(player* p)
{
    bool problem = false;
    bool problem2 = false;
    int ASCII_OFFSET = 65;
    int xLocTemp, yLocTemp;
    bool orienTemp;
    string coordinatesTemp, orientationInputTemp;

    cout<< p -> printShipBoard();
    cout<<"\nNow placing ships for "<<p -> getName()<<": \n";
    for (int i = 0; i < p -> getShipCount(); i++)
    {
        do
        {
            if(problem2) std::cout<<"\n**Ship could not be placed. Please check the coordinates and try again.**\n";
            problem2 = false;
            do
            {
                problem = false;
                cout<< "\nPlacing ship of size "<<i+1<<": \n";
                cout<< "Would you like your ship to be veritcal or horizontal? (H/V): ";
                std::getline(std::cin, orientationInputTemp);
                cout<< "To place your ship, enter the coordinate of the upper-left most slot: ";
                std::getline(std::cin, coordinatesTemp);

                if(orientationInputTemp.length() != 1 || 
                   (toupper(orientationInputTemp[0]) != 'H' &&
                   toupper(orientationInputTemp[0]) != 'V') ) problem = true;
                if(coordinatesTemp.length() > 3  || coordinatesTemp.length() < 2 ||
                   !isStringInt(coordinatesTemp.substr(1)) ||
                   !isStringLetter(coordinatesTemp.substr(0,1)) ) problem = true;
                if(problem) std::cout<<"\n**Invalid input. Please try again.**\n";
            }
            while(problem);

            xLocTemp = (int)toupper(coordinatesTemp[0]) - ASCII_OFFSET;
            coordinatesTemp.erase(0,1);
            yLocTemp = stoi(coordinatesTemp) - 1;
            orienTemp = (toupper(orientationInputTemp[0]) == 'H');
            
            if(yLocTemp > 10 || yLocTemp < 1) problem2 = true;
            if(!problem2) problem2 = !(p -> buildAndPlaceShip(i+1, orienTemp, xLocTemp, yLocTemp));
        }while(problem2);
        
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
    
    finishTurnPrompt();
    clearScreen();
    if(m_gameOver == false) switchPlayerPrompt();

//PLAYER2 TURN
    if(m_gameOver == false)
    {
        turnIO(m_player2);//gathers input and prints player boards
        m_player2 -> playerTurn(m_tempX, m_tempY, m_player1 -> hitCheck(m_tempX, m_tempY));//updates the player's boards and prints the result of the shot
        std::cout<<m_player1 -> updatePlayerShotAt(m_tempX, m_tempY);//updates the opposing player's boards and prints the result of the shot
        m_gameOver = m_player1-> loserCheck();
        
        finishTurnPrompt();
        clearScreen();
        if(m_gameOver == false) switchPlayerPrompt();
    }
}
void game::turnIO(player* p)
{
    bool problem = false;
    int ASCII_OFFSET = 65;
    string coordinatesTemp = "";
    
    do
    {
        if(problem == false) cout<< p -> printBoard();
        problem = false;
        cout << "Please enter a coordinate (ex. F8): ";
        std::getline(std::cin, coordinatesTemp);
        
        
        if(coordinatesTemp.length() > 3  || coordinatesTemp.length() < 2 ||
           !isStringInt(coordinatesTemp.substr(1)) ||
           !isStringLetter(coordinatesTemp.substr(0,1)) ) problem = true;
        if(stoi(coordinatesTemp.substr(1)) > 10 || stoi(coordinatesTemp.substr(1)) < 1 ) problem = true;

        if(!problem)
        {
            m_tempX = (int)toupper(coordinatesTemp[0]) - ASCII_OFFSET;
            coordinatesTemp.erase(0,1);
            m_tempY = stoi(coordinatesTemp) - 1;
            if(p -> m_board.m_shotGrid[m_tempY][m_tempX] != '.') problem = true;
        }
        if(problem) std::cout<<"\n**Invalid input. Please try again.**\n";
    }while(problem);
    
    
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

    cout << "        _      _                     _\n";
    cout << "       (_)    | |                   | |  \n";
    cout << " __   ___  ___| |_ ___  _ __ _   _  | |\n";
    cout << " \\ \\ / / |/ __| __/ _ \\| '__| | | | |_|\n";
    cout << "  \\ V /| | (__| || (_) | |  | |_| |  _\n";
    cout << "   \\_/ |_|\\___|\\__\\___/|_|   \\__, | |_| \n";
    cout << "                              __/ |  \n";
    cout << "                             |___/     \n";
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
void game::finishSetUpPrompt()
{
    clearScreen();
    std::string dummy;
    std::cout<<"\n***The battle is about to begin!***\n";
    std::cout<<m_player1 -> getName()<<", press enter when you are ready: ";
    std::getline(std::cin, dummy);
}
void game::finishTurnPrompt()
{
    std::string dummy;
    std::cout<<"\nPress enter when you are finished with your turn: ";
    std::getline(std::cin, dummy);
}
bool game::isStringInt(std::string s)
{
    return (s.find_first_not_of("0123456789") == std::string::npos);
    //find_first_not_of returns std::string::npos if no matches are found
}

bool game::isStringLetter(std::string s)
{
    std::string store = "ABCDEFGHIJ";
    store +=            "abcdefghij";
    return (s.find_first_not_of(store) == std::string::npos);
}