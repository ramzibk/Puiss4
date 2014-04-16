#ifndef H_Game
#define H_Game

using namespace std;

#include <vector>
#include <iostream>
#include <stdexcept>

#include "Slot.h"
#include "types.h"

//singleton class
class Game{
      
        vector<column> grid;
        bool humain;
        Pawn humainPawn;
        int winner;
        //pointer to singleton
         static Game* singleton;
      
        Game(){
            grid.resize(7);
            for(int i=0;i<7;i++){
                grid.at(i).resize(6);
            }
        }
        Game(const Game &);
         ~Game(){delete singleton;}
        void operator=(const Game &);

public:
        //getters
        inline bool isHumain(){return humain;}
        inline Pawn getHumainPawn(){return humainPawn;} 
        inline vector<column> getGrid(){ return grid;};
        Pawn getColor(int col,int row);
                
        //setters
        inline void setHumain(bool h){humain = h;}
        inline void setHumainPawn(Pawn hp){humainPawn = hp;}
        
        //game instance getter
        static Game* getInstance(){
              if(singleton == NULL){
                             singleton = new Game;
              }
              return singleton;
        }

        void init(bool,Pawn&);
        //initializes humain pawn and sets humain first player turn
        bool isFreeColumn(int);
        //return true if column in parameter has a free place for a pawn
        int getFirstFreeSpot(int);
        //return the first free place int column given in parameter
        bool isFull();
        //return true if grid is full, false if not
        int whoWins();
        //return 1 if humain wins, -1 if computer wins, 0 if draw
        void nextMove()throw (out_of_range&, logic_error&);
        //
        bool putSlot(int i,int j,Pawn color);
        //puts a slot int grid at column i and row j with specified color
        //return true if a line with specied color is complete, false if not
};


#endif
