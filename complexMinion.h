#ifndef __COMPLEXMINION_H__
#define __COMPLEXMINION_H__
#include "card.h"
#include <vector>
#include <string>
struct inst{ //instance variable for minions to account for the change in stats from enchant
    int atk;
    int dfn;
    std::string dscr; //description
    std::vector<int> ens; // list of enchants from oldest to newest
	inst(int,int,std::string,std::vector<int>);
};

class complexMinion : public card{

  public:
    complexMinion(std::string,int,int,std::string);
    virtual int getAttack()=0;
    virtual int getDefence()=0;
    virtual void setDefence(int value) = 0;
    virtual void damage(int d)=0;
    virtual int getCost() = 0;
    virtual int getRCost() = 0;
    virtual void use(master* gm)=0;
	virtual void use(master* gm, int i, int j) = 0;
	virtual void changeMinionLife(changeType t, int i) = 0;
	virtual void changeMinionAttack(changeType t, int i) = 0;
	virtual bool isMinionDead()=0;
    virtual complexMinion* getCore()=0;
    virtual void changeAction(int value) = 0;
    virtual void fillAction() = 0;
    virtual int getAction() = 0;
    virtual void enchant(complexMinion* cm) = 0;
    ~complexMinion();


    virtual inst instance()=0;//produces a collection of information regarding the instance of minion
    virtual void inchant(std::vector<int>&) = 0;//helper function for instance
};
#endif
