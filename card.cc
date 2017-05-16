#include "card.h"
#include "changeTriggerType.h"
#include <string>
using namespace std;

card::card(string name, int id,int cost,string dscr):name{name},id{id},cost{cost},dscr{dscr}{}

void card::trigger(master*, triggerType) {}//some minions, all spells will be unaffected by trigger.

string card::getName(){
    return name;
}

string card::getDscr(){
    return dscr;
}

int card::getCost(){
    return cost;
}

card::~card(){}



