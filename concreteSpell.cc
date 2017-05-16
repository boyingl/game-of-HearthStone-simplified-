#include "spell.h"
#include "concreteSpell.h"
#include "gameMaster.h"
#include <string>

banish::banish():spell{"Banish",0,2,"Destroy target minion or ritual"}{}

void banish::play(master* gm, int i, int j){
    gm->play(this, i, j);
}

unsummon::unsummon():spell{"Unsummon",1,1,"Return target minion to its owner's hand"}{}

void unsummon::play(master* gm, int i, int j){
    gm->play(this,i,j);
}

recharge::recharge():spell{"Recharge",2,1,"Your ritual gains 3 charges"}{}

void recharge::play(master* gm){
    gm->play(this);
}

disenchant::disenchant():spell{"Disenchant",3,1,"Destroy the top enchantment on target minion"}{}

void disenchant::play(master* gm, int i, int j){
    gm->play(this,i,j);
}

raiseDead::raiseDead():spell{"Raise Dead",4,1,"Ressurect the top minion in your graveyard and set its defence to 1"}{}

void raiseDead::play(master *gm){
    gm->play(this);
}

blizzard::blizzard():spell{"Blizzard",5,3,"Deal 2 damage to all minions"}{}

void blizzard::play(master *gm){
    gm->play(this);
}

crazyPlayer::crazyPlayer():spell{"CrazyPlayer", 6, 2, "give your player 1 attack point"}{}

void crazyPlayer::play(master *gm){
  gm->play(this);
}

