#include"game.h"
#include<string>

using namespace std;


///This constructs some of the more important variables and helps limit loops.
game::game()
{
    m_gameOver = false;
    m_tempX = 0;
    m_tempY = 0;
    m_player1 = nullptr;
    m_player2 = nullptr;
    m_mode = 0;

    m_clearScreenString = "";
    for(int i=0; i<70;i++)//we construct this string once, that way we don't have to run the loop
    {//every time we want to clear the screen
        m_clearScreenString += "\n";
    }
}

///Deconstructing player objects.
game::~game()
{
    delete m_player1;
    delete m_player2;
    delete m_player2AI;
}

///This is the main game loop.
void game::play()
{
    setUp();
    while(m_gameOver == false)
    {
        fullTurn();
    }
    closingScreen();
}

///creates 2 players with 3 ships each, used to skip shipIO and speed up testing
///
///ships are placed in upper left corner of the board horizontally
void game::testPlay()
{
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

///calls the functions that allow the users to set up their boards
void game::setUp()
{
    setUpIO();

    shipIO(m_player1);
    finishTurnPrompt();
    clearScreen();
    
    if(m_mode == 0) {
        shipIO(m_player2);
    } else { 
        aiShipIO(m_player2AI);
    }

    finishTurnPrompt();
    clearScreen();

    finishSetUpPrompt();
}

///gets the name of the a player and their number of ships.
void game::setUpIO()
{
    string name = "";
    string name0 = "";
    string shipCount = "";
    string shipCount0 = "";
    string aiChoice = "";
    bool problem = false;
//PLAYER1
    do
    {
        problem = false;
        cout << "Player 1, please input your name: ";
        std::getline(std::cin, name);
        cout << "Please enter the number of ships you could like to have? (1-6): ";
        std::getline(std::cin, shipCount);
        cout << "Would you like to play with AI (Y/N): ";
        std::getline(std::cin, aiChoice);

        if(!isStringInt(shipCount) || shipCount.length() == 0 || aiChoice.length() != 1) problem = true;
        if(!problem)
        {
            if(stoi(shipCount) > 6 || stoi(shipCount) < 1 ) problem = true;
            if(toupper(aiChoice[0]) != 'Y' && toupper(aiChoice[0]) != 'N') problem = true;
        }
        if(problem) std::cout<<"\n**Invalid input. Please try again.**\n";

    }while(problem);
    m_player1 = new player(name, stoi(shipCount));
    m_mode = toupper(aiChoice[0]) == 'N' ? 0 : 1; 
    

    finishTurnPrompt();
    clearScreen();
//PLAYER2
    if(m_mode == 0) {
        do
        {
            problem = false;
            cout << "Player 2, please input your name: ";
            std::getline(std::cin, name0);
            cout << "Please enter the number of ships you could like to have? (1-6): ";
            std::getline(std::cin, shipCount0);
            //INPUT VALIDATION
            if(!isStringInt(shipCount0) || shipCount0.length() == 0) problem = true;
            if(!problem)
            {
                if(stoi(shipCount0) > 6 || stoi(shipCount0) < 1 ) problem = true;
            }
            if(problem) std::cout<<"\n**Invalid input. Please try again.**\n";

        }while(problem);
        m_player2 = new player(name0, stoi(shipCount0));
    } else {
        int diffTemp = aiSetUpIO();
        //shipCount0 = shipCount;
        m_player2AI = new AI(stoi(shipCount), diffTemp);
        cout << "AI has been created!\n";
    }

    finishTurnPrompt();
    clearScreen();
}

int game::aiSetUpIO()
{
    bool problem;
    string aiDifficulty;

    do
    {
        problem = false;
        cout << "What difficulty would you like the AI to be?\n";
        cout << "0 is easy, 1 is medium, 2 is hard: ";
        std::getline(std::cin, aiDifficulty);
        if(!isStringInt(aiDifficulty) || aiDifficulty.length() != 1) problem = true;
        if(!problem){
            if(stoi(aiDifficulty) > 2 || stoi(aiDifficulty) < 0) problem = true;
        }
        if(problem) cout <<"\n**Invalid difficulty input. Please try again.**\n";

    } while (problem);

    return (stoi(aiDifficulty));
    
}


///allows the user to place their ships.
///@param a pointer to the player who is taking their turn
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

                //INPUT VALIDATION
                if(orientationInputTemp.length() != 1 ||
                   (toupper(orientationInputTemp[0]) != 'H' &&
                   toupper(orientationInputTemp[0]) != 'V') ) problem = true;
                if(coordinatesTemp.length() > 3  || coordinatesTemp.length() < 2 ||
                   !isStringInt(coordinatesTemp.substr(1)) ||
                   !isStringLetter(coordinatesTemp.substr(0,1)) ) problem = true;
                if(problem) std::cout<<"\n**Invalid input. Please try again.**\n";
            }
            while(problem);
            //CONVERT INPUT
            xLocTemp = (int)toupper(coordinatesTemp[0]) - ASCII_OFFSET;
            coordinatesTemp.erase(0,1);
            yLocTemp = stoi(coordinatesTemp) - 1;
            orienTemp = (toupper(orientationInputTemp[0]) == 'H');

            if(yLocTemp > 9 || yLocTemp < 0) problem2 = true;
            if(!problem2) problem2 = !(p -> buildAndPlaceShip(i+1, orienTemp, xLocTemp, yLocTemp));
        }while(problem2);

        cout<< p -> printShipBoard();

    }
}

void game::aiShipIO(AI* p)
{
    bool problem = false;
    int xLocTemp, yLocTemp;
    bool orienTemp;

    cout << "Now placing ships for AI: \n";
    //cout << p->getShipCount() << "\n";
    for (int i = 0; i < p -> getShipCount(); i++) {
        do
        {
            xLocTemp = p->randomCoord();
            yLocTemp = p->randomCoord();
            orienTemp = (p->randomOrien() == 0) ? 0 : 1;
            problem = !(p -> buildAndPlaceShip(i+1, orienTemp, xLocTemp, yLocTemp));
        } while (problem);
        //cout << "Placed a ship\n";
    }
    cout << "AI ships placed!\n";
    cout << p->printShipBoard(); //for testing get rid of this when done
}

///Runs the player turns.
///
///This is one of the most important methods in the entire program. it steps through the game process one by one.
void game::fullTurn()
{
//PLAYER1 TURN
    turnIO(m_player1);//gathers input and prints player boards

    if(m_mode == 0) {
        m_player1 -> playerTurn(m_tempX, m_tempY, m_player2 -> hitCheck(m_tempX, m_tempY) );//updates the player's boards and prints the result of the shot
        std::cout<<m_player2 -> updatePlayerShotAt(m_tempX, m_tempY);//updates the opposing player's boards and prints the result of the shot
        m_gameOver = m_player2-> loserCheck();
    } else {
        m_player1 -> playerTurn(m_tempX, m_tempY, m_player2AI -> hitCheck(m_tempX, m_tempY) );
        std::cout<<m_player2AI -> updatePlayerShotAt(m_tempX, m_tempY);
        m_gameOver = m_player2AI-> loserCheck();
    }

    finishTurnPrompt();
    clearScreen();
    if(m_gameOver == false) switchPlayerPrompt();

//PLAYER2 TURN
    if(m_gameOver == false)
    {
        if(m_mode == 0) {
            turnIO(m_player2);//gathers input and prints player boards
            m_player2 -> playerTurn(m_tempX, m_tempY, m_player1 -> hitCheck(m_tempX, m_tempY));//updates the player's boards and prints the result of the shot
            std::cout<<m_player1 -> updatePlayerShotAt(m_tempX, m_tempY);//updates the opposing player's boards and prints the result of the shot
        } else {
            //aiTurnIO(m_player2AI);
            cout << "AI firing!\n";
            m_player2AI -> aiTurn(m_player1);
        }
        m_gameOver = m_player1-> loserCheck();
        

        finishTurnPrompt();
        clearScreen();
        if(m_gameOver == false) switchPlayerPrompt();
    }
}

///gathers the input for a half turn (only one player goes), sets m_shotX and m_shotY based on input, prints full board.
///@param p is the player being modified.
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
        //INPUT VALIDATION
        if(coordinatesTemp.length() > 3  || coordinatesTemp.length() < 2 ||
           !isStringInt(coordinatesTemp.substr(1)) ||
           !isStringLetter(coordinatesTemp.substr(0,1)) ) problem = true;
        if(!problem)
        {
            if(stoi(coordinatesTemp.substr(1)) > 10 || stoi(coordinatesTemp.substr(1)) < 1 ) problem = true;
        }
        if(!problem)
        {   //CONVERT INPUT
            m_tempX = (int)toupper(coordinatesTemp[0]) - ASCII_OFFSET;
            coordinatesTemp.erase(0,1);
            m_tempY = stoi(coordinatesTemp) - 1;
            if(p -> m_board.m_shotGrid[m_tempY][m_tempX] != '.') problem = true;//place the ship
        }
        if(problem) std::cout<<"\n**Invalid input. Please try again.**\n";
    }while(problem);
}

void game::aiTurnIO(AI* p) // I don't think we need this actually, do it all in the AI's play methods
{
    bool problem = false;

    cout <<"AI firing!\n";
    do
    {
        m_tempX = p->randomCoord();
        m_tempY = p->randomCoord();
        if(p -> m_board.m_shotGrid[m_tempY][m_tempX] != '.') problem = true;
    } while (problem);
    
}

///after a winner has been determined, print a closing screen stating the winner
void game::closingScreen()
{
    if( m_player1->loserCheck() == true)
    {
        if (m_mode == 0) {
            cout << "Congratulations " << m_player2->getName() << ", you have won!\n\n";
        } else {
            cout << "The AI has won! \n\n";
        }
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

///clears the screen to help secrecy of the players info
void game::clearScreen()
{
    std::cout<<m_clearScreenString;
}

///Allows the user to move away from the screen while the next player takes their turn
void game::switchPlayerPrompt()
{
    std::string dummy;
    std::cout<<"\nPress enter when the next player is ready: ";
    std::getline(std::cin, dummy);
}

///waits for the next player to press enter then switches players
void game::finishSetUpPrompt()
{
    clearScreen();
    std::string dummy;
    std::cout<<"\n***The battle is about to begin!***\n";
    std::cout<<m_player1 -> getName()<<", press enter when you are ready: ";
    std::getline(std::cin, dummy);
}

///Allows the user to see the result of their turn before the screen gets cleared
void game::finishTurnPrompt()
{
    std::string dummy;
    std::cout<<"\nPress enter when you are finished with your turn: ";
    std::getline(std::cin, dummy);
}

///helper method to see if a string is an int
///@param s the string to be checked
///@return true if the string is a positive int, false otherwise
bool game::isStringInt(std::string s)
{
    return (s.find_first_not_of("0123456789") == std::string::npos);
    //find_first_not_of returns std::string::npos if no matches are found
}

///helper method to see if a string contains the letters allowable as coordinates
///@param s the string to be checked
///@return true if the string is a a-j, false otherwise
bool game::isStringLetter(std::string s)
{
    std::string store = "ABCDEFGHIJ";
    store +=            "abcdefghij";
    return (s.find_first_not_of(store) == std::string::npos);
}
