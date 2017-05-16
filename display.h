#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include "changeTriggerType.h"
class player;


class display{
	protected:
	player* p1;
  player* p2;
	public:
	display(player*,player*);
	virtual void showBoard()=0;
	virtual void showHand(player*)=0;
  virtual void inspectMinion(player*, int i)=0;
	virtual void notify(triggerType)=0;
	virtual ~display();
};

#endif
