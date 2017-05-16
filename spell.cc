#include "spell.h"
#include "gameMaster.h"

#include <string>
#include <iostream>
using namespace std;

spell::spell(string name, int cost, int id, string description): card{name, cost, id, description}{
}

void spell::play(master* gm){
  gm->error();
}

void spell::play(master* gm,int player, int targetCard){
  gm->error();
}

spell::~spell(){}






