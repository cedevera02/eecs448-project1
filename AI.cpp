#include "AI.h"
#include <stdlib.h> //srand and rand from here
#include <time.h> //this allows us to get the time to generate a random seed using srand
#include <iostream>


///AI CONSTRUCTOR
///
///@param shipCount Takes in the amount of ships chosen for game play
///@param difficulty 0 = easy, 1= medium, 2 = hard. AI difficulty
AI::AI(int shipCount, int difficulty)
{
    std::srand(time(0));
    m_sinkCount = 0;
    m_mediumState = 0;
    m_directionTracker = -1;
    m_oppsShipsSunk = 0;
    m_failChecker = false;
    m_difficulty = difficulty;
    m_name = "AI";
    m_shipCount = shipCount;
    m_ships = new ship* [m_shipCount];
    for(int i=0; i<m_shipCount; i++)
    {
        m_ships[i] = nullptr;
    }
}

/// AI DESTRUCTOR
///
///Simple destructor for the heap allocated array (located in Player Class)
AI::~AI()
{
    
   
}

///METHODS
///
/// This gets the difficulty and returns it.
///@return Returns the difficulty level of AI (0= easy; 1= medium; 2= hard)
int AI::getDifficulty() const
{
    return m_difficulty;
}


//m_player2 -> playerTurn(m_tempX, m_tempY, m_player1 -> hitCheck(m_tempX, m_tempY));//updates the player's boards and prints the result of the shot
//std::cout<<m_player1 -> updatePlayerShotAt(m_tempX, m_tempY);//updates the opposing player's boards and prints the result of the shot
//use these to fire the shots, it will take care of checks
//if(m_board.m_shotGrid[m_tempY][m_tempX] != '.') problem = true; need this for ensuring firing at new loc


///This method is the shot action of the AI when the user chooses easy difficulty. Easy play shoots at random coordinates. 
///
///@param p, the pointer to player one object 
void AI::easyPlay(player* p)
{
   bool problem= false;
  
  
    do{
        problem = false;
        m_initialX= randomCoord();
        m_initialY= randomCoord();
        if(m_board.m_shotGrid[m_initialY][m_initialX] != '.') problem = true;

    }while(problem);

    this-> playerTurn(m_initialX, m_initialY, p->hitCheck(m_initialX, m_initialY));
    std::cout<<p->updatePlayerShotAt(m_initialX,m_initialY);
 

}


bool AI::getFailChecker() const
{
    return m_failChecker;
}

void AI::mediumPlay(player* p)
{
    bool problem = false;
    bool hitChecker = false;
    
  
    if(m_mediumState == 0) {
        do{
            problem = false;
            m_initialX= randomCoord();
            m_initialY= randomCoord();
            if(m_board.m_shotGrid[m_initialY][m_initialX] != '.') problem = true;

        }while(problem);

        hitChecker = p->hitCheck(m_initialX, m_initialY);
        this-> playerTurn(m_initialX, m_initialY, hitChecker);
        std::cout<<p->updatePlayerShotAt(m_initialX,m_initialY);

        if(hitChecker) m_mediumState = 1;

        m_directionTracker = -1;

        m_incNum = 0;

        
    } else if (m_mediumState == 1) {
        do {
            m_directionTracker ++;
            if(m_directionTracker == 4){
                 m_directionTracker = 0;
                 m_incNum += 1;
            }

            if( canFireUp( m_initialX, m_initialY - 1 - m_incNum ) ) {
                
                hitChecker = p->hitCheck(m_initialX, m_initialY - 1 - m_incNum);
                this-> playerTurn(m_initialX, m_initialY - 1 - m_incNum, hitChecker);
                std::cout<<p->updatePlayerShotAt(m_initialX,m_initialY - 1 - m_incNum);
                if(hitChecker) {
                    m_directionX = m_initialX;
                    m_directionY = m_initialY - 1 - m_incNum;
                    m_mediumState = 2; 
                    m_failChecker = false;
                }
                break;
            } else if ( canFireRight( m_initialX + 1 + m_incNum, m_initialY ) ) {
                
                hitChecker = p->hitCheck(m_initialX+1+ m_incNum, m_initialY);
                this-> playerTurn(m_initialX+1+ m_incNum, m_initialY, hitChecker);
                std::cout<<p->updatePlayerShotAt(m_initialX+1+ m_incNum,m_initialY);
                if(hitChecker) {
                    m_directionX = m_initialX + 1+ m_incNum;
                    m_directionY = m_initialY;
                    m_mediumState = 2;
                    m_failChecker = false;
                }
                break;
            } else if ( canFireDown ( m_initialX, m_initialY + 1 + m_incNum ) ) {
                
                hitChecker = p->hitCheck(m_initialX, m_initialY + 1 + m_incNum);
                this-> playerTurn(m_initialX, m_initialY + 1 + m_incNum, hitChecker);
                std::cout<<p->updatePlayerShotAt(m_initialX,m_initialY + 1 + m_incNum);
                if(hitChecker) {
                    m_directionX = m_initialX;
                    m_directionY = m_initialY + 1 + m_incNum;
                    m_mediumState = 2;
                    m_failChecker = false;
                }
                break;
            } else if ( canFireLeft( m_initialX - 1 - m_incNum, m_initialY ) ){
                hitChecker = p->hitCheck(m_initialX - 1 -m_incNum, m_initialY);
                this-> playerTurn(m_initialX-1 -m_incNum, m_initialY, hitChecker);
                std::cout<<p->updatePlayerShotAt(m_initialX-1 -m_incNum,m_initialY);
                if(hitChecker) {
                    m_directionX = m_initialX-1-m_incNum;
                    m_directionY = m_initialY;
                    m_mediumState = 2;
                    m_failChecker = false;
                }
                break;
            }

            
        } while (m_directionTracker < 4);


    } else {
        //change the logic from fire where you can, to go until you miss in a direction
        m_contChecker = true;
        m_failChecker = false;
        //m_incNum = 1;
        hitChecker = false;
    
        do {
            if(m_directionTracker == 0) {
                if(m_directionY - 1 >= 0) {
                    if(m_board.m_shotGrid[m_directionY - 1][m_directionX] == '.') {
                        
                        hitChecker = p->hitCheck(m_directionX, m_directionY - 1);
                        this-> playerTurn(m_directionX, m_directionY - 1, hitChecker);
                        std::cout<<p->updatePlayerShotAt(m_directionX,m_directionY - 1);
                        if(!hitChecker) {
                            m_contChecker = false;
                        }
                        if(p->getSinkCount() > m_oppsShipsSunk) {
                            m_oppsShipsSunk = p->getSinkCount();
                            m_mediumState = 0;
                        }
                        m_directionY -= 1;
                        break;
                    } else if(m_board.m_shotGrid[m_directionY - 1][m_directionX] == 'X') {
                        m_directionY -= 1;
                        m_contChecker = true;
                        m_failChecker = true;
                    }else {
                        m_contChecker = false;
                        m_failChecker = true;
                    }
                } else {
                    m_contChecker = false;
                    m_failChecker = true;
                }

            } else if(m_directionTracker == 1) {
                if(m_directionX + 1 < 10) {
                    if(m_board.m_shotGrid[m_directionY][m_directionX + 1] == '.') {
                        
                        hitChecker = p->hitCheck(m_directionX +1 , m_directionY );
                        this-> playerTurn(m_directionX + 1, m_directionY, hitChecker);
                        std::cout<<p->updatePlayerShotAt(m_directionX + 1,m_directionY);
                        if(!hitChecker) {
                            m_contChecker = false;
                        }
                        if(p->getSinkCount() > m_oppsShipsSunk) {
                            m_oppsShipsSunk = p->getSinkCount();
                            m_mediumState = 0;
                        }

                        m_directionX += 1;
                        break;
                    } else if(m_board.m_shotGrid[m_directionY][m_directionX + 1] == 'X') {
                        m_directionX += 1;
                        m_contChecker = true;
                        m_failChecker = true;
                    } else {
                        m_contChecker = false;
                        m_failChecker = true;
                    }
                } else {
                    m_failChecker = true;
                    m_contChecker = false;
                }

            } else if(m_directionTracker == 2) {
                if(m_directionY + 1 < 10) {
                    if(m_board.m_shotGrid[m_directionY + 1][m_directionX] == '.') {
                        
                        hitChecker = p->hitCheck(m_directionX, m_directionY + 1 );
                        this-> playerTurn(m_directionX, m_directionY + 1, hitChecker);
                        std::cout<<p->updatePlayerShotAt(m_directionX,m_directionY + 1);
                        if(!hitChecker) {
                            m_contChecker = false;
                        }
                        if(p->getSinkCount() > m_oppsShipsSunk) {
                            m_oppsShipsSunk = p->getSinkCount();
                            m_mediumState = 0;
                        }

                        m_directionY += 1;
                        break;
                    } else if (m_board.m_shotGrid[m_directionY + 1][m_directionX] == 'X') {
                        m_directionY += 1;
                        m_contChecker = true;
                        m_failChecker = true;
                    } else {
                        m_contChecker = false;
                        m_failChecker = true;
                    }
                } else {
                    m_failChecker = true;
                    m_contChecker = false;
                }
            } else if(m_directionTracker == 3) {
                if(m_directionX - 1 >= 0) {
                    if(m_board.m_shotGrid[m_directionY][m_directionX - 1] == '.') {
                        
                        hitChecker = p->hitCheck(m_directionX - 1 , m_directionY );
                        this-> playerTurn(m_directionX - 1, m_directionY, hitChecker);
                        std::cout<<p->updatePlayerShotAt(m_directionX - 1,m_directionY);
                        if(!hitChecker) {
                            m_contChecker = false;
                        }
                        if(p->getSinkCount() > m_oppsShipsSunk) {
                            m_oppsShipsSunk = p->getSinkCount();
                            m_mediumState = 0;
                        }

                        m_directionX -= 1;
                        break;
                    } else if (m_board.m_shotGrid[m_directionY][m_directionX - 1] == 'X') {
                        m_directionX -= 1;
                        m_contChecker = true;
                        m_failChecker = true;
                    } else {
                        m_contChecker = false;
                        m_failChecker = true;
                    }
                } else {
                    m_failChecker = true;
                    m_contChecker = false;
                }

            }
        } while (m_contChecker == true);

        
        
        if(m_contChecker == false) {
            m_mediumState = 1;
        }

        /*
        if(m_failChecker == true) {
            m_mediumState = 1;
        }
        */
        
    }

}

void AI::hardPlay(player* p)
{
   bool problem= false;
  
  
    do{
        problem = false;
        for(int i=0; i < 10; i++)
        {
            for(int j=0; j < 10; j++)
            {
                if(p->m_board.m_shipGrid[i][j] == 'o')
                {
                    m_initialX= j;
                    m_initialY= i;
                    break;
                }
            }
        }
        
        if(m_board.m_shotGrid[m_initialX][m_initialY] != '.') problem = true;

    }while(problem);

    this-> playerTurn(m_initialX, m_initialY, p->hitCheck(m_initialX, m_initialY));
    std::cout<<p->updatePlayerShotAt(m_initialX,m_initialY);
}

void AI::aiTurn(player* p)
{
    if(m_difficulty == 0) {
        easyPlay(p);
    } else if (m_difficulty == 1) {
        mediumPlay(p);
    } else {
        hardPlay(p);
    }
}

int AI::randomCoord()
{
    return ( std::rand() % 10) ;
}

int AI::randomOrien()
{
    return ( std::rand() % 2 );
}

bool AI::canFireUp(int xCoord, int yCoord) const
{
    return ( ( yCoord  >= 0 ) && ( m_directionTracker == 0 ) 
    && ( m_board.m_shotGrid[yCoord][xCoord] == '.' ) );
}

bool AI::canFireRight(int xCoord, int yCoord) const
{
    return ( ( xCoord <= 9 ) && ( m_directionTracker == 1) 
    && ( m_board.m_shotGrid[yCoord][xCoord] == '.' ) );
}

bool AI::canFireDown(int xCoord, int yCoord) const
{
    return ( ( yCoord <= 9) && ( m_directionTracker == 2) 
    && ( m_board.m_shotGrid[yCoord][xCoord] == '.' ) );
}

bool AI::canFireLeft(int xCoord, int yCoord) const
{
    return ( ( xCoord >= 0 ) && ( m_directionTracker == 3 ) 
    && ( m_board.m_shotGrid[yCoord][xCoord] == '.' ) );
}