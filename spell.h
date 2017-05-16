#ifndef __SPELL_H__ 
#define __SPELL_H__
#include "card.h"

#include <string>

class spell: public card{

  public:
    spell(std::string name, int cost, int id, std::string description);
    void play(master* gm) override;
    void play(master* gm,int player, int targetCard) override;
	  ~spell();
};

#endif
