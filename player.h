#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <string>
#include <iostream>
#include "exceptionType.h"
#include "changeTriggerType.h"


class card;
class textDisplay;
class master;
class complexMinion;
class ritual;
class enchantment;
class spell;


class player{

  //gm* owner/visitor for card
private:
  //visitor of card, 
  master* gameMaster;
  std::string name;
  int attack = 0;
  int life;
  int magic; //no bound
  int id; //player 1 or 2
  const int initLife = 20;

  const int initMagic = 3;
  const unsigned int maxHand = 5;

  const int initHand = 5;
  const unsigned int maxRitual = 1;
  const unsigned int maxArmy = 5;


  std::vector <card*> hand;
  std::vector <card*> deck;
  std::vector <complexMinion*> minionArmy;
  ritual* oneRitual;
  std::vector <complexMinion*> grave;

  
  //is gonna be set by placeMinion
  //placeMinion record the index -> fire trigger
  //trigger might potentially ask to hurt or destory this guy
  int curMinion = -1; //the index in hand that is gonna be played

  void draw();
  //strip minion, destory enchant, put minion at grave
  //called during damaging minion, index verified
  void moveDeadMinion(int index);
  void swapCard(int i, int j);

public:
  
  card* createCard(std::string name) throw(exceptionError);
  //for create player factory
  player(master* gm,int id);
  //if deck -f given, is file stream, else std
  void setupDeck(std::istream& deckStream , bool isShuffle) throw(exceptionError);
  void setupHand();
  void setName(std::string name);

  std::string getName();
  int getMagic();
  int getMagicCost(int i) throw (exceptionError);
  int getMagicRCost(int i) throw (exceptionError);
  int getLife();
  int getAttack();
  void setAttack(int value);
  bool isPlayerDead();
  int getCurMinionIndex();
  //master call this on active player at every sot
  void sotSetup();

  //master call this on appropriate player, first index always the index in hand/ army
  //second, third are target, pass it to card
  //card allow master visit or print error if mix target
  //index is verified to be [1,5] but might be > actual size, need to check
  //play the ith card in hand

  //player check magic cost met
  //master reduce magic
  void play(int handIndex) throw(exceptionError);
  void play(int handIndex, int player, int targetCard) throw(exceptionError);

  void use(int index) throw(exceptionError);
  void use(int index, int tPlayer, int tIndex) throw(exceptionError);
  //use, let gm visit card
  //  hand[i]->useability(p, j, gm) //this play let gm visit it
    //play enchant, got to gm, gm call decorate minion with the enchant para & player side & target card
  //  remove from hand


  //at attack, master query minion damage point through this
  //call that minion's damage points
  int getDamage(int index) throw(exceptionError);

  //player check ritual has leftover charge
  void trigger(triggerType type);

  int getMinionSize();

  int getAction(int i) throw(exceptionError);
  void changeAction(int i) throw(exceptionError); //decrease army[i]'s action by 1'
 



//---------------------this is called by card visitor master, modify minion/ hand/ army/ player---------------------
  //damage ith in army with damagePoint, move dead minion at the end
  void damage(int index, int damagePoint) throw(exceptionError);

  void damageAll(int damagePoint);

  //damage the player, throw exist game error at player death
  void damage(int damagePoint) throw(exceptionError);

  void enchantMinion(enchantment* enchCard, int index) throw(exceptionError);

  void placeRitual(ritual* aritual);

  complexMinion* reviveMinion() throw(exceptionError);

  void changeMinionAttack(int index, changeType, int value) throw(exceptionError);

  void changeMinionLife(int index, changeType, int value) throw(exceptionError);

  void placeMinion(complexMinion* theMinion) throw(exceptionError);
  //   add
  //   trigger(enter)
  //   sendtrigger(enter)

  void removeSpell(spell* usedSpell);

  void removeRitual() throw (exceptionError);

  void removeMinion(int index) throw (exceptionError);

  void returnHand(int index) throw (exceptionError); 

  void changeMagic(int num);

  void addRitualCharge(int num) throw (exceptionError);


  //if layer = -1, strip all
  void stripMinion(int index, int layer) throw (exceptionError);


//delete cards in hand, deck, minion_army, ritual, grave yard
  ~player();


  //////////trigger!!!!!!!!!!!


//-------------if testing mode------------------
//called by master, no need to go to card, modify hand, draw or discard
  //in debug mode, can draw a card from external command
  void testDraw();

  //discard the ith card
  void discard(int i) throw(exceptionError);

  friend class textDisplay;
  friend class graphicDisplay;

};

#endif



