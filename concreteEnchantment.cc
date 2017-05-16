#include "concreteEnchantment.h"
#include "gameMaster.h"
#include <string>
giantStrength::giantStrength():enchantment{"Giant Strength",0,1,""}{}

int giantStrength::getAttack(){
  return dfn+(core->getAttack());
}
int giantStrength::getDefence(){  
  return dfn+(core->getDefence());
}

void giantStrength::damage(int d){
    if(core){
	if (d<=dfn)  dfn-=d;
	else if(d>dfn){
	    core->damage(d-dfn);
	    dfn=0;
	}
    }
}

enrage::enrage():enchantment{"Enrage",1,2,""}{}

int enrage::getAttack(){
    if(core) return 2*(core->getAttack());
}


int enrage::getDefence(){//dfn value is essential for damage calculation
    if(core){
        if(dfn==-1) dfn=core->getDefence();
        return dfn+core->getDefence();
    }
    return dfn+core->getDefence();
}

void enrage::damage(int d){
    if(core){
        if (d<=dfn) dfn-=d;
        else if(d>dfn){
            core->damage(d-dfn);
            dfn=0;
        }
    }
}

haste::haste():enchantment{"Haste",2,1,"Enchanted minion gains +1 action each turn"}{}

void haste::trigger(master* gm, triggerType type){
  if(type == startTurn)  action ++;
}

void haste::changeAction(int value){
    if (action >= value) action -= value;
    else core->changeAction(value - action);
}


std::string haste::getDscr(){
    return core? core->getDscr()+dscr : dscr;
}


void haste::enchant(complexMinion* cm){
    if(core) core->enchant(cm);
    else core = cm;
}


int haste::getAction(){
  return action + core->getAction();
}

magicFatigue::magicFatigue():enchantment{"Magic Fatigue",3,0,"Enchanted minion's activated ability costs 2 more"}{}

int magicFatigue::getRCost(){
  if(core){
    int coreCost = core->getRCost();
    if( coreCost>= 0) return 2 + coreCost;
    return coreCost;
  }
  return -1;
}

std::string magicFatigue::getDscr(){
    return core? core->getDscr()+dscr : dscr;
}



silence::silence():enchantment{"Silence",4,1,"Enhanced minion cannot use abilities"}{}

void silence::use(master* gm){
  gm->use(this);
}

std::string silence::getDscr(){
    return core? core->getDscr():dscr;
}
