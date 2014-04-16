#ifndef H_Slot
#define H_Slot

#include "types.h"

class Slot{
      Pawn color;
      
public:
    inline Pawn getColor() {return color;}
    inline void setColor(Pawn c) {color = c;}
};


#endif
