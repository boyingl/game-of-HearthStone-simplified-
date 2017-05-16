#ifndef __GAMEMASTER_H__
#define __GAMEMASTER_H__


#include <string>
#include "concreteMinion.h"
#include "concreteRitual.h"
#include "concreteEnchantment.h"
#include "concreteSpell.h"
#include "exceptionType.h"
#include "display.h"

class textDisplay;
class graphicDisplay;
class complexMinion;
class enchantment;
class player;

enum triggerType;

class master{
    player* active;
    player* nonactive;
    player* container[3];
    player* createPlayer(std::istream& deck,std::string name, int id);
    textDisplay* td;
    graphicDisplay* gd;
    bool isTesting;
    bool hasGraphics;
public:
    void setTesting(bool isInTesting);
    void setupGame(std::istream& deck1, std::istream& deck2,std::istream& source);
    void setGraphics(bool hasGraphic);
    std::string getActiveName();
    void passDamage(int i, int j) throw (exceptionError);
    void passDamage(int i) throw (exceptionError);
    void passPlay(int i);
    void passPlay(int i,int p,int j);
    void passMinionAbility(int i);    
    void passMinionAbility(int i,int p,int j);
    //if testing mode
    void passDraw();
    void passDiscard(int i);
    void passTrigger(triggerType t);
    void swap();
    void passSotSetup();
    void passShowHand();
    void passInspectMinion(int i);  
    void passShowBoard();
    void gpassShowHand();
    void gpassInspectMinion(int i); 
    void gpassShowBoard();
    ~master();

    void play(banish* b, int p, int card);
    void play(unsummon* u, int p, int card);
    void play(recharge* r);
    void play(disenchant* d, int p, int card);
    void play(raiseDead* r);
    void play(blizzard* r);
    void play(crazyPlayer* r);

    void play(complexMinion* c);
    void play(enchantment* e,int p, int card);
    void play(ritual* r);


    void use(novicePyromancer* m, int p, int card);
    void use(apprenticeSummoner* m) throw(exceptionError);
    void use(masterSummoner* m) throw(exceptionError);

    //---------------------------use a enchantment with ability---------------------------
    //silence as mute activated ability
    //mute, that is do nothing 
    //so silence enchantment should still pass it to gm
    void use(silence* m);

    ///////////////////////////////////////////////////////////
    //if another trigger passed to the card, 
    //card will not allow this visitor
    //game master only deal with the case that its the right trigger
    void trigger(boneGolem* b);

    //check if its opponent enter
    //fire elemental has get owner method, returning 1 or 2
    void trigger(fireElemental* f);
    void trigger(potionSeller* p);
    void trigger(haste* h); 
    void trigger(darkRitual* d);
    //when minion enters
    void trigger(auraPower* a);
    //when minion enters(enter, trigger)
    void trigger(standstill* a);

    void error() throw (exceptionError);
    void noActionError() throw (exceptionError);
 
};



#endif
