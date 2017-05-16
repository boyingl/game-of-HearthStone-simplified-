#ifndef __GRAPHICDISPLAY_H__
#define __GRAPHICDISPLAY_H__
#include "window.h"
#include "display.h"
class player;
class graphicDisplay: public display{
    Xwindow render;
    int x;
    int y;
    int width;
    int height;
public:
  graphicDisplay(player* p1, player* p2, int x, int y);
  void showBoard();
  void showHand(player*);
  void inspectMinion(player*, int i);
    void notify(triggerType t);
};
#endif
