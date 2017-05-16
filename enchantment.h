#ifndef __ENCHANTMENT_H__
#define __ENCHANTMENT_H__
#include "complexMinion.h"
#include <string>

class enchantment: public complexMinion{
    protected:
    complexMinion* core = nullptr;
    public:
    enchantment(std::string,int,int,std::string);//ctor
    void play(master* gm) override;//only possible if the enchantment wraps a complexMinion
    void play(master* gm,int i,int j) override;//play an unbound enchantment on a target
    int getAttack() override;//pass through and (potentially) modify stats
    void setDefence(int value) override;
    int getDefence() override;
    int getCost() override;
    int getRCost() override;
    std::string getDscr() override;
    std::string getName() override;
    bool isMinionDead() override; //Any minion that modifies Defence stat needs to overload this function. even if the function content is the same.
    void damage(int d) override;//take damage
    void use(master* gm) override;
    void use(master* gm, int i, int j) override;//these functions arent pure virtual because they serve as default behavior
    void changeMinionLife(changeType t, int i) override;
    void changeMinionAttack(changeType t, int i) override;
    void trigger(master* gm, triggerType t) override;
    inst instance() override;
    void inchant(std::vector<int>& lv) override;
    complexMinion* getCore() override;
    void changeAction(int value) override;
    void fillAction() override;
    void enchant(complexMinion* cm) override; //special for haste
    int getAction() override;
    ~enchantment()=0;
};

#endif
