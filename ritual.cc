#include"ritual.h"
#include "gameMaster.h"

#include <string>
using namespace std;
ritual::ritual(string name, int id, int cost, string dscr, int charge, int rcost) :card{ name,id,cost,dscr }, charge{ charge }, rcost{rcost} {}

void ritual::play(master* gm){
    gm->play(this);
}

void ritual::play(master* gm,int,int){
	gm->error();
}

int ritual::getCharge(){
    return charge;
}

void ritual::changeCharge(int value) {
  charge += value;
}

int ritual::getRCost(){
  return rcost;
}

ritual::~ritual(){}
