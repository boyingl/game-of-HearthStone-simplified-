#ifndef  G_UTIL
#define G_UTIL
#include <iostream>
#include <sstream>

class Xwindow;

void fillString(Xwindow& xw, int x, int y, const std::string &content, int width, int height, int al=0);//al for alignment. 0 for centre, -1 for left, 1 for right
void drawplayer(Xwindow& xw, int x, int y, const std::string &name, int mana, int life, int width=160, int height=160);
void drawMinion(Xwindow& xw, int x, int y, const std::string &name, int cost, int atk, int dfn, int width=160, int height=160);
void drawMinionActive(Xwindow &xw,int x, int y, const std::string& name, int cost, int atk, int dfn, const std::string &dscr, int RCost, int width=160, int height=160);
void drawMinionPassive(Xwindow &xw, int x, int y, const std::string& name, int cost, int atk, int dfn, const std::string &dscr, int width=160, int height=160);
void drawEnchant(Xwindow &xw, int x, int y, const std::string &name, int cost, const std::string &dscr,int width=160, int height=160);
void drawEnchantAD(Xwindow &xw,int x,int y, const std::string &name, int cost, const std::string &dscr, const std::string &atk, const std::string &dfn, int width=160, int height=160);
void drawSpell(Xwindow &xw,int x, int y, const std::string & name,int cost,const std::string &dscr, int width=160, int height=160);
void drawRitual(Xwindow &xw, int x, int y, const std::string &name, int cost, const std::string &dscr, int RCost, int charge, int width=160, int height=160);
void drawBorder(Xwindow &xw,int x, int y, int width=160, int height=160);
#endif

