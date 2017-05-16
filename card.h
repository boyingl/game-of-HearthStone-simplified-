#ifndef __CARD_H__
#define __CARD_H__
#include "changeTriggerType.h"
#include <string>
//class def

class master;

class card{

protected:
    std::string name;
    std::string dscr;
    int cost;
    
public:
    const int id;
    card(std::string name,int id,int cost,std::string dscr);
    virtual void play(master* gm)=0;
    virtual void play(master* gm,int i,int j)=0;
    virtual void trigger(master* gm, triggerType t);
    virtual std::string getName();
    virtual std::string getDscr();
    virtual int getCost();
    virtual ~card()=0;
};


#endif


