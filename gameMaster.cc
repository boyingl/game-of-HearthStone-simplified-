#include "gameMaster.h"
#include "exceptionType.h"
#include "display.h"
#include "textDisplay.h"
#include "graphicDisplay.h"
#include "player.h"

#include <string>
using namespace std;

player* master::createPlayer(istream& deck, string name, int id){
    player* s = new player(this, id);
    s->setName(name);
    s->setupDeck(deck, !isTesting);
    s->setupHand();
    return s;
}


void master::setTesting(bool isInTesting){
  isTesting = isInTesting;
}


void master::setGraphics(bool hasGraphic){
  hasGraphics = hasGraphic;
}

void master::setupGame(istream& d1, istream& d2, istream& source){
    string n1, n2;
    getline(source, n1);
    getline(source, n2);
    container[0] = nullptr;
    container[1] = createPlayer(d1,n1,1);
    container[2] = createPlayer(d2,n2,2);
    active = container[1];
    nonactive = container[2];
    td = new textDisplay{container[1], container[2]};
    if(hasGraphics) gd = new graphicDisplay{container[1], container[2],1280,720};    
}


string master::getActiveName(){
  return active->getName();
}

//check action here
void master::passDamage(int i,int j) throw (exceptionError){
    int action = active->getAction(i);
    if(action < 1) noActionError();
    int d1 = active->getDamage(i);
    int d2 = nonactive->getDamage(j);
    nonactive->damage(j,d1);
    active->damage(i,d2);

    active->changeAction(i);  
}


void master::passDamage(int i) throw (exceptionError){
    int action = active->getAction(i);
    if(action < 1) noActionError();
    int d1 = active->getDamage(i);
    int d2 = nonactive->getAttack(); //get attack value of player
    nonactive->damage(d1);
    active->damage(i, d2);  //the minion get attacked too

    active->changeAction(i);
}


void master::passPlay(int i){  
  int magic = active->getMagic();
  int magicCost = active->getMagicCost(i);
  if(magicCost > magic && (!isTesting)) throw commandError("does not have enough magic to damage with this card");
  active->play(i);    
}


void master::passPlay(int i, int p, int j){
    int magic = active->getMagic();
    int magicCost = active->getMagicCost(i); //cost
    if(magicCost > magic && (!isTesting)) throw commandError("does not have enough magic to damage with this card");
    active->play(i,p,j);
}


void master::passMinionAbility(int i){
    int magic = active->getMagic();
    int magicCost = active->getMagicRCost(i); //rcost
    if(magicCost > magic && (!isTesting)) throw commandError("does not have enough magic to damage with this card");
    int action = active->getAction(i);
    if(action < 1) noActionError();
    active->use(i);
    active->changeAction(i);
}


void master::passMinionAbility(int i, int p, int j){
    int magic = active->getMagic();
    int magicCost = active->getMagicRCost(i); //rcost
    if(magicCost > magic && (!isTesting)) throw commandError("does not have enough magic to damage with this card");
    int action = active->getAction(i);
    if(action < 1) noActionError();
    active->use(i,p,j); 
    active->changeAction(i);   
}


void master::passDraw(){
    active->testDraw();
}


void master::passDiscard(int i){
    active->discard(i);
}

void master::passTrigger(triggerType signal){
  if(signal == endTurn || signal == startTurn) active->trigger(signal);
  else{
    active->trigger(signal);
    nonactive->trigger(signal);  
  }
}


void master::swap(){
    player* t = active;
    active = nonactive;
    nonactive = t;
}

void master::passSotSetup(){
    active->sotSetup();
}

void master::passShowHand(){
  td->showHand(active);
}

void master::passInspectMinion(int i){
  td->inspectMinion(active,i);
}

void master::passShowBoard(){
  td->showBoard();
}

void master::gpassShowHand(){
  gd->showHand(active);  
}

void master::gpassInspectMinion(int i){  
  gd->inspectMinion(active,i);
}

void master::gpassShowBoard(){
  gd->showBoard();
}
master::~master(){
  delete active;
  delete nonactive;
  delete td;
  if(hasGraphics)delete gd;
}

/////////////////////////////////////////////////////////////
//---------------------------play a spell-------------------------------
//card, 1 - 5 or 6 is ritual
void master::play(banish* b, int p, int card){
  if(card == 6) container[p]->removeRitual();
  //remove minion gonna pass trigger
  else container[p]->removeMinion(card);
  active->removeSpell(b);
}


void master::play(unsummon* u, int p, int card){
  container[p]->returnHand(card);
  active->removeSpell(u);
}


void master::play(recharge* r){
  active->addRitualCharge(3);
  active->removeSpell(r);
}


void master::play(disenchant* d, int p, int card){
  container[p]->stripMinion(card, 1);
  active->removeSpell(d);
}


void master::play(raiseDead* r){
    //revive will pass the trigger
  complexMinion* revived = active->reviveMinion();
  revived->setDefence(1);
  active->removeSpell(r);
}


void master::play(blizzard* r){
  active->damageAll(2);
  nonactive->damageAll(2);
  active->removeSpell(r);
}

void master::play(crazyPlayer* r){  
  active->setAttack(1);
  string oldName = active->getName();
  active->setName(oldName + string(" atk:1"));
  active->removeSpell(r);
}
//---------------------------play a minion-------------------------------
void master::play(complexMinion* r){
  active->placeMinion(r);
}


//---------------------------play a enchantments-------------------------------
void master::play(enchantment* d, int p, int card){
  container[p]->enchantMinion(d, card);
}


//---------------------------play a ritual-------------------------------
void master::play(ritual* r){
  active->placeRitual(r);
}


////////////////////////////////////////////////////////////////
//---------------------------use a minion w/o ability---------------------------
// void Master::use(minion* m) throw (exception){
//   cout << "    calling master::use(minion){" << endl;
//   throw commandError("this minion you played has no activated ability to use");
// }


//---------------------------use a minion with ability---------------------------

void master::use(novicePyromancer* m, int p, int card){
  container[p]->damage(card, 1);
}


void master::use(apprenticeSummoner* m) throw(exceptionError){
  int size = active->getMinionSize(); 
  if(size < 5){
    complexMinion* summoned = dynamic_cast< complexMinion* > (active->createCard("Air Elemental"));
    active->placeMinion(summoned);
  }
  else throw commandError("full minion army, cannot apprentice Summon"); 
}


void master::use(masterSummoner* m) throw(exceptionError){
  int size = active->getMinionSize(); 
  if(size < 5){
    int num = (5 - size) > 3? 3 : (5-size);
    for(int i = 0; i < num; i ++){
      complexMinion* summoned = dynamic_cast< complexMinion* > (active->createCard("Air Elemental"));
      //should succeed
      active->placeMinion(summoned);
    }
  }
  else throw commandError("full minion army, cannot apprentice Summon"); 
}  



//---------------------------use a enchantment with ability---------------------------
//silence as mute activated ability
//mute, that is do nothing 
//so silence enchantment should still pass it to gm
void master::use(silence* m){
}



///////////////////////////////////////////////////////////
//if another trigger passed to the card, 
//card will not allow this visitor
//game master only deal with the case that its the right trigger
void master::trigger(boneGolem* b){
  b->changeMinionLife(add, 1);
  b->changeMinionAttack(add, 1);
}


//check if its opponent enter
//fire elemental has get owner method, returning 1 or 2
void master::trigger(fireElemental* f){
  int owner = f->getOwner();
  //if opponent is active
  if(active != container[owner]){
    //opponent' minion enter, opponent is active
    int size = active->getMinionSize();
    int newIndex = active->getCurMinionIndex(); //index set at place minion
    if(newIndex >= size) return;
    else active->changeMinionLife(newIndex, subtract, 1);
  }  
}


void master::trigger(potionSeller* p){
  int num = active->getMinionSize();
  for(int i = 0; i < num; i++){
    active->changeMinionLife(i, add, 1);
  }
}

void master::trigger(haste* h){
  h->changeAction(1);
}

void master::trigger(darkRitual* d){
  active->changeMagic(1);
}

//when minion enters
void master::trigger(auraPower* a){

  int owner = a->getOwner();
  //if opponent is active
  if(active == container[owner]){
    //opponent' minion enter, opponent is active
    int size = active->getMinionSize();
    int newIndex = active->getCurMinionIndex(); //index set at place minion
    if(newIndex >= size) return;
    else {
      active->changeMinionLife(newIndex, add, 1);
      active->changeMinionAttack(newIndex, add, 1);
    }
  } 
}

//when minion enters(enter, trigger)
void master::trigger(standstill* a){
  int size = active->getMinionSize();
  int newIndex = active->getCurMinionIndex(); //index set at place minion

  if(newIndex >= size) return;
  else active->removeMinion(newIndex);
  //then other enter minion thing happen
  //then the player destory instead of place the minion
}

//magic fatigue, cost two more, not ability
//when return & reduce magic, 
//the decorator pattern +2 on existing complex minion



void master::error() throw (exceptionError){
  throw commandError("this is not a valid command");
}

void master::noActionError() throw (exceptionError){
  throw commandError("minnion does not have enough action");
}
