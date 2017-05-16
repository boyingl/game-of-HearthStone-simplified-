#include "window.h"
#include "graphicUtil.h"
void fillString(Xwindow& xw, int x, int y, const std::string &content, int width, int height, int al){
    int cap=width/6;
    int hc=height/10;
    std::string con;
    if(content.length()>cap*hc){
	con=content.substr(0,cap*hc);
    }
    else{
	con=content;
    }
    int overflow=con.length()/cap;
    for (int i=0;i<overflow;i++){
        xw.drawString(x,y+10*i,con.substr(i*cap,cap));
    }
    int rm=con.length()%cap;
    xw.drawString(x+(cap-rm)*(3*(al+1)),y+overflow*10,con.substr(overflow*cap,rm)); 
}

void drawplayer(Xwindow& xw, int x, int y, const std::string &name, int mana, int life, int width, int height){
    //set up
    xw.fillRectangle(x,y,width,height);
    xw.fillRectangle(x+width/32,y+height/32,width*30/32,height*30/32,0);
    
    //name
    fillString(xw,x+width/8,y+height/4,name,width*3/4,height/2);

    //filling lower boxes
    xw.fillRectangle(x+width/32,y+height*26/32,width*5/32,height*5/32);
    xw.fillRectangle(x+width*26/32,y+height*26/32,width*5/32,height*5/32);
    xw.fillRectangle(x+width/32,y+height*26/32+1,width*5/32-1,height*5/32-1,0);
    xw.fillRectangle(x+width*26/32+1,y+height*26/32+1,width*5/32-1,height*5/32-1,0);
    std::ostringstream m,l;
    m<<mana;
    l<<life;
    xw.drawString(x+width*2/32,y+height*30/32,m.str());
    xw.drawString(x+width*27/32,y+height*30/32,l.str());
}

void drawMinion(Xwindow& xw, int x, int y, const std::string &name, int cost, int atk, int dfn, int width, int height ){
    //set up
    xw.fillRectangle(x,y,width,height);
    xw.fillRectangle(x+width/32,y+height/32,width*30/32,height*30/32,0);
   
    //bar betwen class type and title 
    xw.fillRectangle(x,y+height/6,width,height/6);
    xw.fillRectangle(x+width/32,y+height/6+1,width*30/32,height/6-2,0);
    
    fillString(xw,x+width*2/32,y+height*4/32,name,width*3/4,height/8,-1);
    fillString(xw,x,y+height*9/32,"Minion",width*30/32,height/8,1);
    //filling the lower boxes
    xw.fillRectangle(x+width/32,y+height*26/32,width*5/32,height*5/32);
    xw.fillRectangle(x+width*26/32,y+height*26/32,width*5/32,height*5/32);
    xw.fillRectangle(x+width/32,y+height*26/32+1,width*5/32-1,height*5/32-1,0);
    xw.fillRectangle(x+width*26/32+1,y+height*26/32+1,width*5/32-1,height*5/32-1,0);
    xw.fillRectangle(x+width*26/32,y+height/32,width*5/32,height*9/64);
    xw.fillRectangle(x+width*26/32+1,y+height/32-1,width*5/32-1,height*9/64-1,0);
    std::ostringstream a,d,c;
    a<<atk;
    d<<dfn;
    c<<cost;
    xw.drawString(x+width*2/32,y+height*30/32,a.str());
    xw.drawString(x+width*28/32,y+height*30/32,d.str());
    xw.drawString(x+width*28/32,y+height*4/32,c.str());
}

void drawMinionActive(Xwindow &xw,int x, int y, const std::string& name, int cost, int atk, int dfn, const std::string &dscr, int RCost, int width, int height){
    drawMinion(xw,x,y,name,cost,atk,dfn,width,height);
    xw.fillRectangle(x+width/32,y+height*27/64,width*5/32,height*5/32);
    xw.fillRectangle(x+width/32,y+height*27/64-1,width*5/32-1,height*5/32-1,0);
    std::ostringstream r;
    r<<RCost;
    xw.drawString(x+width*2/32,y+height/2,r.str());
    fillString(xw,x+width*7/32,y+height/2,dscr,width*23/32,height/2);
}

void drawMinionPassive(Xwindow &xw, int x, int y, const std::string& name, int cost, int atk, int dfn, const std::string &dscr, int width, int height){
    drawMinion(xw,x,y,name,cost,atk,dfn,width,height);
    fillString(xw,x+width*2/32,y+height/2,dscr,width*28/32,height/2);
}

void drawEnchant(Xwindow &xw, int x, int y, const std::string &name, int cost, const std::string &dscr,int width, int height){
   //set up
    xw.fillRectangle(x,y,width,height);
    xw.fillRectangle(x+width/32,y+height/32,width*30/32,height*30/32,0);

    //bar betwen class type and title 
    xw.fillRectangle(x,y+height/6,width,height/6);
    xw.fillRectangle(x+width/32,y+height/6+1,width*30/32,height/6-2,0);

    fillString(xw,x+width*2/32,y+height*4/32,name,width*3/4,height/8,-1);
    fillString(xw,x,y+height*9/32,"Enchantment",width*30/32,height/8,1);
    //filling the lower boxes 
    fillString(xw,x+width*2/32,y+height/2,dscr,width*28/32,height/3);
    
    xw.fillRectangle(x+width*26/32,y+height/32,width*5/32,height*9/64);
    xw.fillRectangle(x+width*26/32+1,y+height/32-1,width*5/32-1,height*9/64-1,0);

    std::ostringstream c;
    c<<cost;
    xw.drawString(x+width*28/32,y+height*4/32,c.str());
}

void drawEnchantAD(Xwindow &xw,int x,int y, const std::string &name, int cost, const std::string &dscr, const std::string &atk, const std::string &dfn, int width, int height){
    drawEnchant(xw,x,y,name,cost,dscr,width,height);
    xw.fillRectangle(x+width/32,y+height*26/32,width*5/32,height*5/32);
    xw.fillRectangle(x+width*26/32,y+height*26/32,width*5/32,height*5/32);
    xw.fillRectangle(x+width/32,y+height*26/32+1,width*5/32-1,height*5/32-1,0);
    xw.fillRectangle(x+width*26/32+1,y+height*26/32+1,width*5/32-1,height*5/32-1,0);
    xw.drawString(x+width*3/64,y+height*30/32,atk);
    xw.drawString(x+width*55/64,y+height*30/32,dfn);
}

void drawSpell(Xwindow &xw,int x, int y, const std::string & name,int cost,const std::string &dscr, int width, int height){
   //set up
    xw.fillRectangle(x,y,width,height);
    xw.fillRectangle(x+width/32,y+height/32,width*30/32,height*30/32,0);

    //bar betwen class type and title 
    xw.fillRectangle(x,y+height/6,width,height/6);
    xw.fillRectangle(x+width/32,y+height/6+1,width*30/32,height/6-2,0);

    fillString(xw,x+width*2/32,y+height*4/32,name,width*3/4,height/8,-1);
    fillString(xw,x,y+height*9/32,"Spell",width*30/32,height/8,1);
    fillString(xw,x+width*2/32,y+height/2,dscr,width*28/32,height/2);
    xw.fillRectangle(x+width*26/32,y+height/32,width*5/32,height*9/64);
    xw.fillRectangle(x+width*26/32+1,y+height/32-1,width*5/32-1,height*9/64-1,0);

    std::ostringstream c;
    c<<cost;
    xw.drawString(x+width*28/32,y+height*4/32,c.str());

}

void drawRitual(Xwindow &xw, int x, int y, const std::string &name, int cost, const std::string &dscr, int RCost, int charge, int width, int height){
  //set up
    xw.fillRectangle(x,y,width,height);
    xw.fillRectangle(x+width/32,y+height/32,width*30/32,height*30/32,0);

    //bar betwen class type and title 
    xw.fillRectangle(x,y+height/6,width,height/6);
    xw.fillRectangle(x+width/32,y+height/6+1,width*30/32,height/6-2,0);
    
    fillString(xw,x+width*2/32,y+height*4/32,name,width*3/4,height/8,-1);
    fillString(xw,x,y+height*9/32,"Ritual",width*30/32,height/8,1);
    
    xw.fillRectangle(x+width/32,y+height*27/64,width*5/32,height*5/32);
    xw.fillRectangle(x+width/32,y+height*27/64-1,width*5/32-1,height*5/32-1,0);
    std::ostringstream r,c,ch;
    r<<RCost;
    xw.drawString(x+width*2/32,y+height/2,r.str());
    fillString(xw,x+width*7/32,y+height/2,dscr,width*23/32,height/2); 
    xw.fillRectangle(x+width*26/32,y+height/32,width*5/32,height*9/64);
    xw.fillRectangle(x+width*26/32+1,y+height/32-1,width*5/32-1,height*9/64-1,0);
    c<<cost;
    xw.drawString(x+width*28/32,y+height*4/32,c.str());
    ch<<charge;
    xw.fillRectangle(x+width*26/32,y+height*26/32,width*5/32,height*5/32);
    xw.fillRectangle(x+width*26/32+1,y+height*26/32+1,width*5/32-1,height*5/32-1,0);
    xw.drawString(x+width*55/64,y+height*30/32,ch.str());
}

void drawBorder(Xwindow &xw,int x, int y, int width, int height){
    xw.fillRectangle(x,y,width,height);
    xw.fillRectangle(x+width/32,y+height/32,width*30/32,height*30/32,0); 
}

