#include "enchantment.h"
#include "gameMaster.h"
#include <string>
using namespace std;

enchantment::enchantment(string name, int id, int cost, string dscr):complexMinion(name,id,cost,dscr){
}

void enchantment::play(master* gm){
    if(core){
		complexMinion* m=this;
		gm->play(m);
    }
	else {
		gm->error();//indicates invalid play
	}
}

void enchantment::play(master* gm,int i,int j){
	if (!core) 	gm->play(this,i,j);
	else gm->error();
}

//default pass throught behavior. to be overrided by minions with actual stat modifier
int enchantment::getAttack(){//safety precaution. if core is empty, returns -1
 if(core) return core->getAttack();
 else return -1;
}

int enchantment::getDefence(){
    return (core)?core->getDefence():-1;
}

void enchantment::setDefence(int value){
	if (core) core->setDefence(value);
}

int enchantment::getCost() {
	return (core) ? cost + core->getCost() : cost;
}

int enchantment::getRCost(){
	return (core)? core->getRCost() : -1; 
}

std::string enchantment::getDscr(){
    return (core)? core->getDscr() : dscr;
} 

std::string enchantment::getName() {
    return (core)? core->getName() : name;
}


bool enchantment::isMinionDead() {
	return (getDefence() <= 0);
}

void enchantment::damage(int d){
	if (core) core->damage(d);
}


//gm call getAction, check if action >=1
void enchantment::use(master* gm){
  if(core) core->use(gm);
}

void enchantment::use(master *gm, int i, int j) {
		if (core) core->use(gm, i, j);
}

void enchantment::changeMinionLife(changeType t, int i) {
	if (core) core->changeMinionLife(t, i);
}

void enchantment::changeMinionAttack(changeType t, int i) {
	if (core) core->changeMinionAttack(t, i);
}

void enchantment::trigger(master* gm,triggerType t){
	if (core) core->trigger(gm, t);
}

inst enchantment::instance() {
	inst tar{ getAttack(),getDefence(),getDscr(),std::vector<int>() };
	inchant(tar.ens);
	return tar;
}

void enchantment::inchant(std::vector<int>& lv) {
	if (core) {//recursive calls to place their id. first in first out
		core->inchant(lv);
		lv.emplace_back(id);
	}
}


complexMinion* enchantment::getCore() {//layer stripping
	return core;
}

//go layer by layer until core which will invoke minion::changeAction
void enchantment::changeAction(int value){
	if(core) core->changeAction(value);
}


void enchantment::fillAction(){
	if(core) core->fillAction();
}

enchantment::~enchantment(){}


void enchantment::enchant(complexMinion* cm){
	if(!core) core = cm;
	else core->enchant(cm);
}



int enchantment::getAction(){
	return core? core->getAction() : -1;
}

