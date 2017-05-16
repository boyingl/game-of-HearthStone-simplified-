#include "player.h"
#include "gameMaster.h"
#include "exceptionType.h"
#include "changeTriggerType.h"
#include "concreteSpell.h"
#include "concreteRitual.h"
#include "concreteEnchantment.h"
#include "concreteMinion.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <iostream>
#include "card.h"
using namespace std;


//hand full or deck empty not draw, else move card from deck to hand
void player::draw(){
  //if the deck is empty, do nothing
  if(0 == deck.size()) return;
  //if hand is full, do nothing
  else if(maxHand <= hand.size()) return;

  else {
    hand.push_back(deck.back());
    deck.pop_back();
  }
  return;
}


void player::moveDeadMinion(int index){
  stripMinion(index, -1);
  grave.push_back(minionArmy[index]);
  vector<complexMinion*>::iterator it = minionArmy.begin() + index;
  minionArmy.erase(it);  
}


void player::swapCard(int i, int j){
  card* tmp;
  tmp = deck[i];
  deck[i] = deck[j];
  deck[j] = tmp;
}

card* player::createCard(string name) throw(exceptionError){
  card* theCard;

  //spell
  if("Banish" == name){
    theCard = new banish{};
  }

  else if("Unsummon" == name){
    theCard = new unsummon{};
  }

  else if("Recharge" == name){
    theCard = new recharge{};
  }

  else if("Disenchant" == name){
    theCard = new disenchant{};
  }

  else if("Raise Dead" == name){
    theCard = new raiseDead{};
  }

  else if("Blizzard" == name){
    theCard = new blizzard{};
  }

  //minions
  else if("Air Elemental" == name){
    theCard = new airElemental{};    
  }

  else if("Earth Elemental" == name){
    theCard = new earthElemental{};
  }

  else if("Bone Golem" == name){
    theCard = new boneGolem{};    
  }

  else if("Fire Elemental" == name){
    theCard = new fireElemental{id};    
  }

  else if("Potion Seller" == name){
    theCard = new potionSeller{};
  }

  else if("Novice Pyromancer" == name){
    theCard = new novicePyromancer{};    
  }

  else if("Apprentice Summoner" == name){
    theCard = new apprenticeSummoner{};
  }

  else if("Master Summoner" == name){
    theCard = new masterSummoner{};    
  }

  //enchantment
  else if("Giant Strength" == name){
    theCard = new giantStrength{};    
  }

  else if("Enrage" == name){
    theCard = new enrage{};
  }

  else if("Haste" == name){
    theCard = new haste{};    
  }

  else if("Magic Fatigue" == name){
    theCard = new magicFatigue{};    
  }

  else if("Silence" == name){
    theCard = new silence{};
  }

  //ritual
  else if("Dark Ritual" == name){
    theCard = new darkRitual{};    
  }

  else if("Aura of Power" == name){
    theCard = new auraPower{id};
  }

  else if("Standstill" == name){
    theCard = new standstill{};    
  }

  else if("Crazy Player" == name){
    theCard = new crazyPlayer{};    
  }

  else throw exitGame(string("fail to initalize the card") + name);

  return theCard;
}


player::player(master* gm, int id)
: gameMaster{gm}, oneRitual{nullptr}, id{id}{
  life = initLife;
  magic = initMagic;
}


//if deck -f given, is file stream, else std
//cannot initalize card, throw error

void player::setupDeck(istream& deckStream, bool isShuffle) throw(exceptionError){
  string cardName;
  while(getline(deckStream, cardName)){
    //card copy constructor
    card* aCard = createCard(cardName); //might throw at here
    deck.push_back(aCard);
  }
  if(isShuffle){
    int counter = 0;
    int deckSize = deck.size();
    int index;         // v1 in the range 0 to size-1
    for(; counter < deckSize; counter++){
      index = rand() % deckSize;
      if(index < 0 || index >= deckSize) cout << "random gives a out of range index";
      swapCard(counter, index);
    }
  }
  else{
    int deckSize = deck.size();
    vector<card*> tmp;
    for(auto p: deck) tmp.push_back(p);
    deck.clear();
    for(int i = 0; i < deckSize; i++){
      deck.push_back(tmp.back());
      tmp.erase(tmp.end()-1);
    }
  }
  return;
}

void player::setupHand(){
  for(int i = 0; i < maxHand; i++) draw();
}

void player::setName(string theName){
  name = theName;
}


string player::getName(){
  return name;
}



int player::getMagic(){
  return magic;
}


int player::getMagicCost(int i) throw (exceptionError){
  if(i > hand.size()) throw commandError("trying to use out of range card in hand");
  else return hand[i]->getCost();
}

int player::getMagicRCost(int i) throw (exceptionError){
  if(i > minionArmy.size()) throw commandError("trying to use out of range card in hand");
  else return minionArmy[i]->getRCost();
}


int player::getLife(){
  return life;
}

int player::getAttack(){
  return attack;
}

void player::setAttack(int value){
  attack = value;
}


bool player::isPlayerDead(){
  return life == 0;
}

int player::getCurMinionIndex(){
  return curMinion;
}

void player::sotSetup(){
  magic ++;
  for(auto& m: minionArmy) m->fillAction();
  draw();
}



void player::play(int handIndex) throw(exceptionError){
  if(handIndex >= hand.size()) throw commandError("invalid command, attampt to play an out of range card");

  //donno where to move minion, master tell me what to do
  //if come back here, side effect done
  int magicCost = hand[handIndex]->getCost();
  magic = magicCost > magic? 0 : magic-magicCost;
  hand[handIndex]->play(gameMaster);
  vector<card*>::iterator itErase = hand.begin() + handIndex;
  hand.erase(itErase);
}



void player::play(int handIndex, int tPlayer, int tIndex) throw(exceptionError){
  if(handIndex >= hand.size()) throw commandError("invalid command, attampt to play an out of range card");
  
  int magicCost = hand[handIndex]->getCost();
  magic = magicCost > magic? 0 : magic-magicCost; 
  hand[handIndex]->play(gameMaster,tPlayer, tIndex);
  vector<card*>::iterator itErase = hand.begin() + handIndex;
  hand.erase(itErase); 
}


void player::use(int index) throw(exceptionError){
  if(index >= minionArmy.size()) throw commandError("invalid command, attampt to use an out of range card");
  minionArmy[index]->use(gameMaster); //pass as value see if can use
  minionArmy[index]->changeAction(-1);
  int magicCost = minionArmy[index]->getRCost();
  magic = magicCost > magic? 0 : magic-magicCost;
}


void player::use(int index, int tPlayer, int tIndex) throw(exceptionError){
  if(index >= minionArmy.size()) throw commandError("invalid command, attampt to use an out of range card");
  minionArmy[index]->use(gameMaster, tPlayer, tIndex); //pass as value see if can use
  minionArmy[index]->changeAction(-1);
  int magicCost = minionArmy[index]->getRCost();
  magic = magicCost > magic? 0 : magic-magicCost;
}

//master, if attack one para, attack player, does not query
  //call that minion's damage points
int player::getDamage(int index) throw(exceptionError){
  if(index >= minionArmy.size()) throw commandError("invalid command, getDamage on use an out of range card");
  return minionArmy[index]->getAttack();
}




void player::trigger(triggerType type){

  for(auto& c : minionArmy)  c->trigger(gameMaster, type);

  if(!oneRitual) return;
  else oneRitual->trigger(gameMaster ,type);
}




int player::getMinionSize(){
  return minionArmy.size();
}


int player::getAction(int i) throw(exceptionError){  
  if(i >= minionArmy.size()) throw commandError("invalid command, get Action of an out of range card");
  return minionArmy[i]->getAction();
}


void player::changeAction(int i) throw(exceptionError){ 
  if(i >= minionArmy.size()) throw commandError("invalid command, change action of an out of range card");
  minionArmy[i]->changeAction(i);
}

//damage ith in army with damagePoint
//if damage on something does not exist, do nothing
//damage the complex minion
void player::damage(int index, int damagePoint) throw(exceptionError){
  if(index >= minionArmy.size()) throw commandError("invalid command, damage an out of range card");
  else {
    //can also call change minion life
    minionArmy[index]->damage(damagePoint);
    if(minionArmy[index]->isMinionDead()){
      //minion exit trigger happens, gm will call trigger on active then non active
      gameMaster->passTrigger(exitMinion);
      //put the dead minion in the yard & erase it from army
      grave.push_back(minionArmy[index]);
      vector<complexMinion*>::iterator itErase = minionArmy.begin() + index;
      minionArmy.erase(itErase);
    }
  }
}


void player::damageAll(int damagePoint){
  int index = 0;
  for(auto& n: minionArmy)  n->damage(damagePoint);

  for(auto& p: minionArmy){
     if(p->isMinionDead()){
      //minion exit trigger happens, gm will call trigger on active then non active
      gameMaster->passTrigger(exitMinion);
      //put the dead minion in the yard & erase it from army
      grave.push_back(p);
      vector<complexMinion*>::iterator itErase = minionArmy.begin() + index;
      minionArmy.erase(itErase);
    } 
      index ++;
  }
}


//damage the player, throw player name if dead
void player::damage(int damagePoint) throw(exceptionError){
  if(damagePoint >= life) throw exitGame("player" + name + "is dead, game end");
  else life -= damagePoint;
}


  //   //play, let gm visit card
  // play(i, p, j){
  //   hand[i]->play(p, j, gm) //this play let gm visit it
  // }
  //
void player::enchantMinion(enchantment* enchCard, int index) throw(exceptionError){
  if(index >= minionArmy.size()) throw commandError("invalid command, enchant an out of range card");
  //this enchant, set base minion as this pointer passed in
  //set layer as this pointer->getLayer ++
  enchCard->enchant(minionArmy[index]);
  minionArmy[index] = enchCard;
}


void player::placeRitual(ritual* aritual){
  if(oneRitual) delete oneRitual;
  oneRitual = aritual;
}


complexMinion* player::reviveMinion() throw(exceptionError){
  if(grave.size() == 0) throw commandError("the grave is empty, cannot revive minion");
  if(minionArmy.size() == maxArmy) throw commandError("the army is full, cannot revive minion");
  complexMinion* revived = grave.back();
  minionArmy.push_back(revived);
  grave.erase(grave.end()-1);
  gameMaster->passTrigger(enterMinion);
  return revived;
}


void player::changeMinionAttack(int index, changeType type, int value) throw(exceptionError){
  if(index >= minionArmy.size()) throw commandError("invalid command, change minion attack on an out of range card");
  minionArmy[index]->changeMinionAttack(type, value);
}


void player::changeMinionLife(int index, changeType type, int value) throw(exceptionError){
  if(index >= minionArmy.size()) throw commandError("invalid command, change minion life on an out of range card");
  minionArmy[index]->changeMinionLife(type, value);
  if(minionArmy[index]->isMinionDead()){
      //minion exit trigger happens, gm will call trigger on active then non active
      gameMaster->passTrigger(exitMinion);
      //put the dead minion in the yard & erase it from army
      grave.push_back(minionArmy[index]);
      vector<complexMinion*>::iterator itErase = minionArmy.begin() + index;
      minionArmy.erase(itErase);
    }
}




//move the first in hand(verified as a minion to army)
void player::placeMinion(complexMinion* theMinion) throw (exceptionError){
  if(minionArmy.size() == maxArmy) throw commandError("army full, cannot place minion");
  minionArmy.push_back(theMinion);
  curMinion = minionArmy.size() -1;
  gameMaster->passTrigger(enterMinion);
}


void player::removeSpell(spell* usedSpell){
  delete usedSpell;
}



void player::removeRitual() throw (exceptionError){
  if(! oneRitual) throw commandError("no ritual exists for deleting");
  delete oneRitual;
  oneRitual = nullptr;
}


void player::removeMinion(int index) throw (exceptionError){
  if(index >= minionArmy.size()) throw commandError("cannot remove non-existing minion");
  gameMaster->passTrigger(exitMinion);
  delete minionArmy[index];
  vector<complexMinion*>::iterator it = minionArmy.begin() + index;
  minionArmy.erase(it);
}


//does striptting internally
//trigger, strip, put hand, erase army slot
void player::returnHand(int index) throw (exceptionError){
   if(index >= minionArmy.size()) throw commandError("cannot remove non-existing minion");
   gameMaster->passTrigger(exitMinion);
   stripMinion(index, -1);
   hand.push_back(minionArmy[index]);

   vector<complexMinion*>::iterator it = minionArmy.begin() + index;
   minionArmy.erase(it);   
}


//minion will check if magic is enough
//if enough, do stuff & gm reduce magic here
//thus num should be <= magic for this method to be called
//change Magic, pos increase, neg decrease
void player::changeMagic(int num){
  magic += num;
}


void player::addRitualCharge(int num) throw (exceptionError){
  if(! oneRitual) throw commandError("no ritual at all, cannot add charge");
  oneRitual->changeCharge(num);
}


//layer = -1, strip to end
void player::stripMinion(int index, int layer)  throw (exceptionError){
   if(index >= minionArmy.size()) throw commandError("cannot strip non-existing minion");

  //complex minion has strip that will return the one layer base
  //and set that pointer to null
  if(layer == -1){
    while(minionArmy[index]->getCore() != nullptr){
      complexMinion* stripped = minionArmy[index]->getCore();
      //delete the enchant
      delete minionArmy[index];
      minionArmy[index] = stripped;
      layer --;
    } 
  }
  else{
    while(layer != 0){
      complexMinion* stripped = minionArmy[index]->getCore();
      //delete the enchant
      delete minionArmy[index];
      minionArmy[index] = stripped;
      layer --;
    } 
  } 
}



  //use, let gm visit card
  //  hand[i]->useability(p, j, gm) //this play let gm visit it
    //play enchant, got to gm, gm call decorate minion with the enchant para & player side & target card
  //  remove from hand
//delete cards in hand, deck, minion_army, ritual, grave yard
player::~player(){//delete  hand, deck, minion_army, ritual, grave{}
  for(auto n : hand) if(n) delete n;
  for(auto n : deck) if(n) delete n;
  for(auto n : minionArmy) if(n) delete n;
  if(oneRitual) delete oneRitual;
  for(auto n : grave) if(n) delete n;
}





//-------------if testing mode------------------
  //in debug mode, can draw a card from external command
void player::testDraw(){
  draw();
}


//discard the ith card
void player::discard(int i) throw (exceptionError) {
  if(i >= hand.size()) throw commandError("cannot discard unexisting card");
  delete hand[i];
  vector<card*>::iterator it = hand.begin() + i;
  hand.erase(it);
}
