#ifndef TEXT_DISPLAY
#define TEXT_DISPLAY
#include "display.h"
#include "ascii_graphics.h"
class player;
class complexMinion;

class textDisplay: public display{
    complexMinion* takeMinion(player* p, int i);
    void getMinion(player* p,card_template_t* t);
    public:
    textDisplay(player*,player*);
    void showBoard();
    void inspectMinion(player* p, int i);
    void showHand(player*);
    void notify(triggerType);
    
};

#endif


