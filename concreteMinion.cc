#include "gameMaster.h"
#include "concreteMinion.h"
#include <string>
using namespace std;

airElemental::airElemental():minion{"Air Elemental", 0, 0, "", 1, 1,-1}{}


earthElemental::earthElemental():minion{"Earth Elemental", 1, 3, "", 4, 4,-1}{}


boneGolem::boneGolem() : minion{ "Bone Golem",2,2,"Gain +1/+1 whenever a minion leaves play.",1,3,-2 } {}


void boneGolem::trigger(master* gm, triggerType t) {
	minion::trigger(gm, t);
    if (t == exitMinion) gm->trigger(this);
}

fireElemental::fireElemental(int playid) :minion{"Fire Elemental",3,2,"Whenever an opponent's minion enters play, deal 1 damage to it.",2,2,-2},playid(playid) {}

int fireElemental::getOwner() {
    return playid;
}


void fireElemental::trigger(master* gm, triggerType t) {
	minion::trigger(gm, t);
    if (t == enterMinion)	gm->trigger(this);
}

potionSeller::potionSeller():minion{"Potion Seller",4,2,"At the end of your turn, all your minions gain +0/+1.",1,3,-2}{}


void potionSeller::trigger(master* gm, triggerType t){
	minion::trigger(gm, t);
    if (t==endTurn)	gm->trigger(this);
}

novicePyromancer::novicePyromancer():minion{"Novice Pyromancer",5,1,"Deal 1 damage to target minion",0,1,1}{}


void novicePyromancer::use(master* gm,int i,int j){
    gm->use(this,i,j);
}

apprenticeSummoner::apprenticeSummoner():minion{"Apprentice Summoner",6,1,"Summon a 1/1 air elemental",1,1,1}{}


void apprenticeSummoner::use(master* gm){
    gm->use(this);
}

masterSummoner::masterSummoner():minion{"Master Summoner", 7,3,"Summon up to three 1/1 air elementals",2,3,2}{}

void masterSummoner::use(master* gm){
    gm->use(this);
}


