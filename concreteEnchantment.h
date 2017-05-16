#ifndef __CONCRETEENCHANTMENT_H__
#define __CONCRETEENCHANTMENT_H__
#include "enchantment.h"

#include <string>

//+2 +2
class giantStrength : public enchantment{
    int dfn=2;
    public:
    giantStrength();
    int getAttack() override;
    int getDefence() override;
    void damage(int d) override;
};

//*2 *2
class enrage : public enchantment{
    int dfn=-1;//enrage will take on the dfn value of the attached minion
    public:
    enrage();
  int getAttack() override;
  int getDefence() override;
    void damage(int d) override;
};


//gain +1 act each turn
class haste : public enchantment{
    int action = 1;
    public:
    haste();
    void enchant(complexMinion* cm) override;
    void trigger(master* gm, triggerType type) override;
    std::string getDscr() override;
    int getAction() override;
    void changeAction(int value) override;
};


//activated ability cost 2 more
class magicFatigue : public enchantment{
    public:
    magicFatigue();
    int getRCost() override;
    std::string getDscr() override;
};

//cannot use ability
class silence : public enchantment{
    public:
  silence();
  void use(master* gm) override;
    std::string getDscr() override;
};









#endif

