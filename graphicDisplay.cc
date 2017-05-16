#include "graphicDisplay.h"
#include "graphicUtil.h"
#include "player.h"
#include "ritual.h"
#include "minion.h"
#include "enchantment.h"
#include "spell.h"

graphicDisplay::graphicDisplay(player* p1, player* p2, int x, int y):display(p1,p2),x{x},y{y},render(x,y){
    width=x/5;
    height=y/5;
}

void graphicDisplay::notify(triggerType t){}

void drawFuckingMinions(Xwindow &render,complexMinion* temp,int x, int y, int width, int height){
    if(temp){
            int cost=temp->getRCost();
            inst con = temp->instance();
            if(cost==-1){
                drawMinion(render,x,y,temp->getName(),temp->getCost(),con.atk,con.dfn,width,height);
            }
            else if(cost==-2){
                drawMinionPassive(render,x,y,temp->getName(),temp->getCost(),con.atk,con.dfn,con.dscr,width,height);
            }
            else{
                drawMinionActive(render,x,y,temp->getName(),temp->getCost(),con.atk,con.dfn,con.dscr,cost,width,height);
            }
    }
    else{
	drawBorder(render,x,y,width,height);
    }
}

void graphicDisplay::showBoard(){
    render.fillRectangle(0,0,x, y, 0);
    
    drawplayer(render,2*width,0,p1->name,p1->life,p1->magic,width,height);
    
    if (p1->oneRitual){
	drawRitual(render,0,0,p1->oneRitual->getName(), p1->oneRitual->getCost(),p1->oneRitual->getDscr(),p1->oneRitual->getRCost(),p1->oneRitual->getCharge(),width,height);
    }
    else{
	drawBorder(render,0,0,width,height);
    }
    
    complexMinion* temp=(p1->grave.size()>0)?p1->grave.back():nullptr;
    drawFuckingMinions(render,temp,4*width,0,width,height);
    for(int i=0;i<5;i++){
	temp=(p1->minionArmy.size()>i)?p1->minionArmy[i]:nullptr;
	drawFuckingMinions(render,temp,i*width,height,width,height);
    }
    for(int i=0;i<5;i++){
        temp=(p2->minionArmy.size()>i)?p2->minionArmy[i]:nullptr;
        drawFuckingMinions(render,temp,i*width,3*height,width,height);
    }
    
    drawplayer(render,2*width,4*height,p2->name,p2->life,p2->magic,width,height);
    
    if (p2->oneRitual){
        drawRitual(render,0,4*height,p2->oneRitual->getName(), p2->oneRitual->getCost(),p2->oneRitual->getDscr(),p2->oneRitual->getRCost(),p2->oneRitual->getCharge(),width,height);
    }
    else{
        drawBorder(render,0,4*height,width,height);
    }
    
    temp=(p2->grave.size()>0)?p2->grave.back():nullptr;
    drawFuckingMinions(render,temp,4*width,4*height,width,height);
}

void drawFuckingEnchants(Xwindow &render, enchantment* e, int x, int y, int width, int height){
    if(e){
    if(e->id==0){
        drawEnchantAD(render,x,y,e->getName(),e->getCost(),e->getDscr(),"+2","+2",width,height);
    }
    else if(e->id==1){
        drawEnchantAD(render,x,y,e->getName(),e->getCost(),e->getDscr(),"*2","*2",width,height);
    }
    else{
        drawEnchant(render,x,y,e->getName(),e->getCost(),e->getDscr(),width,height);
    }}
    else{
	drawBorder(render,x,y,width,height);
    }
}

void drawFuckingCard(Xwindow &render, card *cp, int x, int y, int width, int height){
    spell *s=dynamic_cast<spell *>(cp);
    ritual *r=dynamic_cast<ritual *>(cp);
    enchantment *e=dynamic_cast<enchantment *>(cp);
    minion* m=dynamic_cast<minion *>(cp);
    if(s){
	drawSpell(render,x,y,s->getName(),s->getCost(),s->getDscr(),width,height);
    }
    if(r){
	drawRitual(render,x,y,r->getName(),r->getCost(),r->getDscr(),r->getRCost(),r->getCharge(),width,height);
    }
    if(e){
	drawFuckingEnchants(render,e,x,y,width,height);
    }
    if(m){
	drawFuckingMinions(render,m,x,y,width,height);
    }
}

void graphicDisplay::showHand(player* p){
    render.fillRectangle(0,0,x, y, 0);
    if(!p) return;
    for(int i=0;i<p->hand.size();i++){
	drawFuckingCard(render,p->hand[i],(i%5)*width,(i/5)*height,width,height);
    }
}

void graphicDisplay::inspectMinion(player* p, int i){
    render.fillRectangle(0,0,x, y, 0);
    if(!p || p->minionArmy.size()<i) return;
    complexMinion* temp=p->minionArmy[i];
    drawFuckingMinions(render,temp,2*width,0*height,width,height);
    if(temp){
	inst k=temp->instance();
	for(int i=0;i<k.ens.size();i++){
	    if(i==0){
		drawEnchantAD(render,width*(i%5),(1+(i/5))*height,"Giant Strength",1,"","+2","+2",width,height);
	    }
	    else if(i==1){
		drawEnchantAD(render,width*(i%5),(1+(i/5))*height,"Enrage",2,"","*2","*2",width,height);
	    }
	    else if(i==2){
		drawEnchant(render,width*(i%5),(1+(i/5))*height,"Haste",1,"Enchanted minion gains +1 action each turn",width,height);
	    }
	    else if(i==3){
		drawEnchant(render,width*(i%5),(1+(i/5))*height,"Magic Fatigue",0,"Enchanted minion's activated ability costs 2 more",width,height);
	    }
	    else if(i==5){
		drawEnchant(render,width*(i%5),(1+(i/5))*height,"Silence",1,"Enchanted minion cannot use abilities",width,height);
	    }
	}
    }
}
