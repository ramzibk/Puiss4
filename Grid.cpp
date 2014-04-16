#include "Grid.h"

ostream& operator<<( const vector<column> grid); //fin de page 1
       static Game& getInstance();
       //returns the single instance of game
       void init(bool,Pawn&);
       //initialises the humain pawn and sets humain turn
       bool isFreeColumn(int);
       //return true if column in parameter has a free place for a pawn
       int getFirstFreeSpot(int);
       //return the first free place int column given in parameter
       int whoWins();
       //return 1 if humain wins, -1 if computer wins, 0 it is draw game
       void nextMove()throw (out_of_range&, logic_error&);
