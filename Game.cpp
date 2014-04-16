#include "Game.h"

Game* Game::singleton = NULL;


Pawn Game::getColor(int col,int row){
//return the pawn color at column "col" and row "row"
    if(col >=0 && col <7 && row>=0 && row <6){
        return ((this->grid.at(col)).at(row)).getColor();
    } 
}

void Game::init(bool h,Pawn& hp){
    cout << "initializing game..";
    //sets humain turn and color and clean grid
    winner = 2;//none of two players wins

    this->setHumain(h);
    this->setHumainPawn(hp);
    
    //grid vector indexes start from bottom left to top right of screen
    /* line iterator
       |\
       |
       |
       |
       |
       ---------------> column iterator*/
       
    for(int i=0;i<7;i++){           //column iterator
        for(int j=0;j<6;j++){       //line iterator
            Slot& s = ((this->grid).at(i)).at(j);
            s.setColor(EMPTY);
        }
    }
    cout << "done" <<endl;
}


bool Game::isFreeColumn(int i){
//returns true if column i in grid has free space for a new slot, false if not

    vector<Slot> column = this->getGrid().at(i);
    for(int j=0;j<column.size();j++){   //line iterator
        Slot s = column.at(j);
        if(s.getColor() == EMPTY) return true;
    }
    return false;
}


int Game::getFirstFreeSpot(int i){
//returns first line index in column i where to put a slot, if column i is full it returns -1

    vector<Slot> column = this->grid.at(i);
    for(int j=0;j<=column.size()-1;j++){
        Slot s = column.at(j);
        if(s.getColor()== EMPTY){
            return j;
        }
    }
    return -1;
}

bool Game::isFull(){
    for(int i=0;i<7;i++){
        if(isFreeColumn(i)) return false;
    }
    return true;
}

int Game::whoWins(){
    return winner;
}

void Game::nextMove() throw (out_of_range&, logic_error&){
//handles interaction with humain player to play a new slot in case of humain turn
//puts a new slot using random or AI call in case of computer turn
//sets winner indicator after each played turn

    int column,row;
    
    if(this->isFull()){
        winner = 0;
    }else{
        if(this->isHumain()){   //humain player turn

            cout << "C'est à vous de jouer (";
            if(this->getHumainPawn() == RED) cout << "R)" << endl;
            else cout << "Y)" << endl;
                
            //read position
            cout << "Quelle colonne? ";
            cin >> column;
            if(column<1 || column>7) {
                throw out_of_range("Out of range error");
            }
            
            column--;
            row = this->getFirstFreeSpot(column);
            if(row <0){
                throw logic_error("Logic error");
                return;
            }
    
            //add a new Slot
            if( putSlot(column,row,this->getHumainPawn()))
                winner = 1; //humain wins
            
        }else{                  //computer turn
            cout << "C'est à moi de jouer (";
            if(this->getHumainPawn() == RED) cout << "Y)" << endl;
            else cout << "R)" << endl;                
        
            //read position
            do{
                cout << "Quelle colonne? ";
                column = rand()%7;
            }while(!this->isFreeColumn(column));
            cout << column+1;
            row = this->getFirstFreeSpot(column);
        
            //add a new Slot
            if(this->getHumainPawn()==RED){
                if(putSlot(column,row,YELLOW))
                    winner = -1;
            }else{
                if(putSlot(column,row,RED))
                    winner = -1;   // computer wins
            }
        
        } //if(this->isHumain)
    
    } //if(this->isFull)
}

bool Game::putSlot(int i, int j,Pawn color){
//puts a slot into grid at column "i" and row "j" with specified color "color"
//return true if color wins false if not

    Slot slot;
    slot.setColor(color);
    this->grid[i][j] = slot;
    
    //search for complete line
    int down=0,left=0,right=0,diagul=0,diagur=0,diagdl=0,diagdr=0;
    
    for(int k=0;k<3;k++){
        if(down==k && (j-k-1)>=0 && this->getColor(i, j-k-1)==color)
            down++;
        if(left==k && this->getColor(i-k-1, j)==color)
            left++;
        if(right==k && this->getColor(i+k,j)==color)
            right++;
        if(diagul==k && this->getColor(i-k-1, j+k)==color)
            diagul++;
        if(diagur==k && this->getColor(i+k,j+k)==color)
            diagur++;
        if(diagdl==k && (j-k-1)>=0 && this->getColor(i-k-1,j-k-1)==color)
            diagdl++;
        if(diagdr==k && (j-k-1)>=0 && this->getColor(i+k,j-k-1)==color)
            diagdr++;
    }
    
    if(down>=4 || (left+right)>=4 || (diagul+diagdr) >= 4 || (diagur+diagdl)>=4)
        return true;
    //else
    return false;
}
