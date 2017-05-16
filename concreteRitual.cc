#include "concreteRitual.h"
#include "changeTriggerType.h"
#include "gameMaster.h"

#include <string>
using namespace std;
darkRitual::darkRitual():ritual{"Dark Ritual",0,0,"At the start of oyur turn, gain 1 magic",5,1}{}

void darkRitual::trigger(master *gm, triggerType t){
    if(t==startTurn && charge >= rcost)	{
      gm->trigger(this);
      changeCharge(-rcost);
    }
}

auraPower::auraPower(int playerid):ritual{"Auro of Power",1,1,"Whenever a minion enters play under your control, it gains +1/+1",4,1}{
  owner = playerid;
}

void auraPower::trigger(master *gm, triggerType t){
    if(t==enterMinion && charge >= rcost) {
      gm->trigger(this);
      changeCharge(-rcost);
    }
}

int auraPower::getOwner(){
  return owner;
}

standstill::standstill():ritual{"Standstill",2,3,"Whenever a minion enters a play, destroy it",4,2}{}

void standstill::trigger(master *gm, triggerType t){
    if(t==enterMinion && charge >= rcost) {
      gm->trigger(this);
      changeCharge(-rcost);
    }
}



