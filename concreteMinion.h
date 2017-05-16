#ifndef __CONCRETEMINION_H__
#define __CONCRETEMINION_H__
#include "card.h"
#include "minion.h"

class airElemental: public minion{
    public:
    airElemental();
};

class earthElemental: public minion{
    public:
    earthElemental();
};

class boneGolem : public minion {
    public:
    boneGolem();
    void trigger(master* gm, triggerType t);
};

class fireElemental : public minion {
    int playid;
    public:
    fireElemental(int playid);
    int getOwner();
    void trigger(master* gm, triggerType t);
};

class potionSeller : public minion{
    public:
    potionSeller();
    void trigger(master* gm, triggerType t);
};

class novicePyromancer : public minion{
    public:
    novicePyromancer();
    void use(master* gm, int i, int j);
};

class apprenticeSummoner : public minion{
    public:
    apprenticeSummoner();
    void use(master* gm);
};

class masterSummoner : public minion{
    public:
    masterSummoner();
    void use(master* gm);
};

#endif
