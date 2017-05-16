#include "minion.h"
#include "gameMaster.h"
#include "changeTriggerType.h"

#include <string>
using namespace std;
minion::minion(string name, int id, int cost, string dscr, int atk, int dfn, int rcost) 
:complexMinion{ name,id,cost,dscr }, atk{ atk }, dfn{ dfn }, rcost{rcost} {}

void minion::play(master* gm){
    gm->play(this);
}

void minion::play(master* gm, int, int){
	gm->error();
}

int minion::getAttack(){
	return atk;
}

int minion::getDefence(){
    return dfn;
}


void minion::setDefence(int value){
  dfn = value;
}

int minion::getCost() {
	return cost;
}


int minion::getRCost(){
	return rcost;
}

bool minion::isMinionDead() {
	return (getDefence() <= 0);
}

void minion::damage(int d){
    dfn-=d;
    //death checked by player
}

//default behavior if no use function override
void minion::use(master * gm){
	gm->error();
}

void minion::use(master* gm, int, int) {
	gm->error();
}

void minion::changeMinionLife(changeType t, int i) {
	if (t == add) dfn += i;
	else if (t == subtract)	dfn -= i;
	else if(t==multiply) 	dfn *= i;
}

void minion::changeMinionAttack(changeType t, int i) {
	if (t == add) atk += i;
	else if (t == subtract) atk -= i;
	else if (t == multiply) atk *= i;
}

//will always reset to 1 action points at round start
void minion::trigger(master* gm,triggerType t){
	if (t == startTurn)  fillAction();
}

inst minion::instance() {
	return inst{ getAttack(),getDefence(),getDscr(),std::vector<int>() };
}

//since baseminions aren't enchants, it does not manipulate the vector
void minion::inchant(std::vector<int>&) {}


//emphasis on indicating there is no core present
complexMinion* minion::getCore() {
	return nullptr;
}

void minion::changeAction(int value){
	action += value;
}

void minion::fillAction(){
	if (action >= maxAction) return;
  action = maxAction;
}

int minion::getAction(){
	return action;
}



void minion::enchant(complexMinion* cm){}
minion::~minion(){}
