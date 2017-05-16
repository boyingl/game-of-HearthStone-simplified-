#ifndef __RITUAL_H__
#define __RITUAL_H__
#include "card.h"

class master;
#include <string>
class ritual: public card{
    protected:
    int charge;
    int rcost;
    public:
    ritual(std::string,int,int,std::string,int charge, int rcost);
    void play(master* gm) override;
    void play(master* gm,int i,int j) override;//dummy
    void trigger(master* gm, triggerType t)=0;
    int getCharge();
    int getRCost();
    void changeCharge(int value);
    ~ritual();
};
#endif

