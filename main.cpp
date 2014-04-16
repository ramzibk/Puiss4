#include <cstdlib>
#include <iostream>
#include <cstdlib>

#include "Game.h"
#include "types.h"

using namespace std;

//overloaded stream operator << 
ostream& operator<<(ostream& , vector<column>);

int main(int argc, char *argv[])
{
    bool humain;
    Pawn couleur;
    char h,c,repeat;
    Game* game = Game::getInstance();
    
    do{
        //read who's first player
        do{
            cout << "Quel joueur commence ? h/c : ";
            cin >> h;
            cout << endl;
        }while( h!='h' && h!='c' && h!='H' && h!='C');
    
        if(h=='h' || h=='H') humain = true;
        else humain = false;
    
        //read humain player color
        do{
            cout << "Quel couleur souhaiter vous utiliser ? y/r : ";
            cin >> c;
            cout << endl;
        }while(c!='y' && c!='r' && c!='Y' && c!='R');
        
        if(c=='Y' || c=='y') couleur = YELLOW;
        else couleur = RED;
        
        //inisialize game
        game->init(humain,couleur);
        
        //print grid
        cout << game->getGrid();
        
        //initialize random generator for computer actions
        srand (time(NULL));
        
        //loop for play
        while(true){
            try{
                game->nextMove();                   //play next move for humain or computer
                
            }catch(out_of_range& oor){
                cerr << "Caught: "<< oor.what() << endl;
                cout << "Column must be in range [1,7]" << endl;
                continue;
            }catch(logic_error& le){
                cerr << "Caught: "<< le.what() << endl;
                cout << "This column is full, choose another one" << endl;
                continue;
            }
            
            cout << game->getGrid();   
                        
            if(game->whoWins() == 1){           //humain player wins
                cout << "Congratulations ! You win" << endl;
                break;
            }else if(game->whoWins() == -1){    //computer wins
                cout << "I win! try again" << endl;
                break;
            }else if(game->whoWins() == 0){     //draw game
                cout << "Draw game ! try again" << endl;   
                break;
            }
            
            //change player
            if(game->isHumain())
                game->setHumain(false);
            else 
                game->setHumain(true);
        }

        do{ 
            cout << "Voulez vous refaire une partie? (o/n) ";
            cin >> repeat;
            cout << endl; 
        }while(repeat!='o' && repeat!='n' && repeat!='O' && repeat!='N');
        
    }while(repeat=='o' || repeat=='O');    
    
    system("PAUSE");
    return EXIT_SUCCESS;
}

ostream& operator<<(ostream& out,const vector<column> grid){
    Slot slot;
    out << " " << endl;
    out <<"+ - - - - - - -+" << endl;
    for(int l=5;l>=0;l--){        //line iterator
        out << "|";
        for(int c=0;c<7;c++){     //column iterator
            slot = (grid.at(c)).at(l);
            if(slot.getColor()==EMPTY)
                out << "  ";
            else if(slot.getColor()==RED)
                out << "o ";
            else if(slot.getColor()==YELLOW)   
                out << "x ";
        }
        out << "|" << endl;
    }
    out <<"+--------------+" << endl;
    out <<"+1 2 3 4 5 6 7 +"<< endl;
    out <<"+--------------+" << endl;
    return out ;        
}
