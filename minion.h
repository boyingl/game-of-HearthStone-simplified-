#ifndef __MINION_H__
#define __MINION_H__

#include "complexMinion.h"
#include <string>
#include "changeTriggerType.h"
class minion : public complexMinion{
    protected:
    int atk;
    int dfn;
	int action;
    int rcost;
    int maxAction = 1;
    public:
    minion(std::string,int,int,std::string,int atk,int dfn, int rcost);
    void play(master* gm) override;
    void play(master* gm, int i, int j) override;//dummy
    int getAttack() override;
    int getDefence() override;
    void setDefence(int value) override;
	int getCost() override;
    int getRCost() override;
	bool isMinionDead() override;
    void damage(int d) override;
    void use(master* gm) override;
	void use(master* gm, int i, int j) override;
	virtual void changeMinionLife(changeType t, int i) override;
	virtual void changeMinionAttack(changeType t, int i) override;
    void trigger(master* gm,triggerType t) override;
	inst instance() override;
	void inchant(std::vector<int>&) override;
	complexMinion* getCore() override;
    void changeAction(int value) override;
    void fillAction() override;
    int getAction() override; 
    void enchant(complexMinion* cm) override;
    ~minion()=0;
};

#endif
