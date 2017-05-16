#ifndef C_RITUALS
#define C_RITUALS
#include "card.h"
#include "ritual.h"
#include "changeTriggerType.h"

class darkRitual : public ritual{
public:
    darkRitual();
    void trigger(master* gm, triggerType t);
};

class auraPower : public ritual{
  int owner;
public:
    auraPower(int playerid);
    void trigger(master* gm, triggerType t);
    int getOwner();
};

class standstill : public ritual{
public:
    standstill();
    void trigger(master* gm, triggerType t);
};

#endif
