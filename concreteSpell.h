#ifndef _CONCRETESPELL_H__
#define _CONCRETESPELL_H__
#include "card.h"
#include "spell.h"
#include <string>

class banish : public spell{
    public:
    banish();
    void play(master* gm, int i, int j);
};

class unsummon : public spell{
    public:
    unsummon();
    void play(master* gm, int i, int j);
};

class recharge : public spell{
    public:
    recharge();
    void play(master* gm);
};

class disenchant : public spell{
    public:
    disenchant();
    void play(master* gm, int i, int j);
};

class raiseDead : public spell{
    public:
    raiseDead();
    void play(master* gm);
};

class blizzard : public spell{
    public:
    blizzard();
    void play(master* gm);
};

class crazyPlayer : public spell{
public:
    crazyPlayer();
    void play(master* gm);
};
#endif
