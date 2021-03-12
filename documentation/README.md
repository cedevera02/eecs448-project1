# Team 11 Project 2

EECS 448 Spring 2021

## Description

Project made with C++. It will run in terminal, requires compiling, then run *prog*. 

1.	Game Setup
    - a.	Board size
        - i.	10x10
        - ii.	The columns are denoted by letters (A-J)
        - iii.	The rows are denoted by number (1-10)
    - b.	Number of ships (per player)
        - i.	Given by user
        - ii.	Minimum of 1 and a maximum of 6
    - c.	Types of ships
        - i.	This will be based on the amount of ships chosen.
        - ii.	If a total of 1 ship is chosen, then each player gets a single 1x1 ship
        - iii.	If a total of 2 ships is chosen, then each player gets a 1x1 and a 1x2 ship
        - iv.	This continues up to 6, where each player will a 1x1, 1x2, 1x3, 1x4, and a 1x6 ship
        - v.	Ships are denoted by ‘o’ on the board.
    - d.	Ship placement
        - i.	After the amount of ships is chosen, players are able to secretly orient and place the ships on their board.

2.	Playing the Game
    - a.	Each player will have 2 boards. A ship board and a shot board.
    - b.	Taking turns, players will pick a space on the opponent's board to "fire" at. 
    - c.	They are then informed if the shot was a "hit" or a "miss". 
    - d.	The player's shot board is updated to reflect this.
    - e.	The shot board will show a ‘0’ if the shot missed or an ‘X’ if the shot hit. Similarly, the ship board will show an ‘!’ if the opponent’s shot hit the ship.
    - f.	After each shot, it is the other player's turn.

3.	Destroying a ship
    - a.	Once a ship has been hit in every space it occupies, it is sunk. 
    - b.	For example, if the 1x3 ship occupies the space B3, B4, and B5. 
    - c.	Once the opponent has shot those three spaces, that ship is sunk.

4.	Game End
    - a.	Once a player has sunk all of the opponent's ships, they immediately win.


## Person Hours Log

Be sure to look in the *Project 02 Log* tab of the file:
[Person-Hours Estimate and Log File](https://docs.google.com/spreadsheets/d/1t7uCkne9O2OVWZMFE1MwESn9uMA4EEfdqJAJvanNAyU/edit?usp=sharing)