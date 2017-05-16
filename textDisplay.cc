#include "textDisplay.h"
#include "player.h"
#include "ritual.h"
#include "minion.h"
#include "enchantment.h"
#include "spell.h"
#include <iostream>
#include <sstream>
using namespace std;

textDisplay::textDisplay(player* p1,player* p2):display{p1,p2}{}

complexMinion* textDisplay::takeMinion(player* p, int i){
    if(p->minionArmy.size()<=i)
    return nullptr;
    else{
    return p->minionArmy[i];
    }
}

void textDisplay::getMinion(player* p,card_template_t t[]){
    for (int i = 0;i < 6;i++) {
	complexMinion* temp = (i < 5) ? takeMinion(p,i) : (p->grave.size())?p->grave.back():nullptr;
	if (temp) {
	    int cost = temp->getRCost();
	    inst con = temp->instance();
	    if (cost == -1) {
		t[i] = display_minion_no_ability(temp->getName(), temp->getCost(), con.atk, con.dfn);
	    }
	    else if (cost == -2) {
		t[i] = display_minion_triggered_ability(temp->getName(), temp->getCost(), con.atk, con.dfn, con.dscr);
	    }
	    else {
		t[i] = display_minion_activated_ability(temp->getName(), temp->getCost(), con.atk, con.dfn, cost, con.dscr);
	    }
	}
	else {
	    t[i] = CARD_TEMPLATE_BORDER;
	}
    }
    t[6] = (p->oneRitual)? display_ritual(p->oneRitual->getName(), p->oneRitual->getCost(), p->oneRitual->getRCost(), p->oneRitual->getDscr(), p->oneRitual->getCharge()) : CARD_TEMPLATE_BORDER;
}


void textDisplay::showBoard(){
    card_template_t pl1=display_player_card(1,p1->name,p1->life,p1->magic);
    card_template_t pl2=display_player_card(2,p2->name,p2->life,p2->magic);
    card_template_t c1[7];
    card_template_t c2[7];
    getMinion(p1,c1);
    getMinion(p2,c2);
    cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
    for (int i = 0; i < 165;i++) {
	cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT<<endl;
    for (int i = 0; i < pl1.size();i++) {
	cout << EXTERNAL_BORDER_CHAR_UP_DOWN << c1[6][i] << CARD_TEMPLATE_EMPTY[i]<< pl1[i] << CARD_TEMPLATE_EMPTY[i] << c1[5][i] << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
    }
    for (int i = 0; i < c1[0].size();i++) {
	cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
	for (int j = 0;j < 5;j++)
	    cout << c1[j][i];
	cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
    }
    for (int i = 0;i < CENTRE_GRAPHIC.size();i++) {
	cout << CENTRE_GRAPHIC[i] << endl;
    }
    for (int i = 0; i < c1[0].size();i++) {
	cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
	for (int j = 0;j < 5;j++)
	    cout << c2[j][i];
	cout << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
    }
    for (int i = 0; i < pl1.size();i++) {
	cout << EXTERNAL_BORDER_CHAR_UP_DOWN << c2[6][i] << CARD_TEMPLATE_EMPTY[i] << pl2[i] << CARD_TEMPLATE_EMPTY[i] << c2[5][i] << EXTERNAL_BORDER_CHAR_UP_DOWN << endl;
    }
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
    for (int i = 0; i < 165;i++) {
	cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    }
    cout << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT <<endl;
}

void textDisplay::inspectMinion(player* p,int i){
    complexMinion *temp=takeMinion(p,i);
    std::vector<card_template_t> t;
    if (temp) {
    int cost = temp->getRCost();
        inst con = temp->instance();
        if (cost == -1) {
            t.emplace_back(display_minion_no_ability(temp->getName(), temp->getCost(), con.atk, con.dfn));
        }
        else if (cost == -2) {
            t.emplace_back(display_minion_triggered_ability(temp->getName(), temp->getCost(), con.atk, con.dfn, con.dscr));
        }
        else {
            t.emplace_back(display_minion_activated_ability(temp->getName(), temp->getCost(), con.atk, con.dfn, cost, con.dscr));
        }
    for( int i : con.ens ){
        if(i==0){
	t.emplace_back(display_enchantment_attack_defence("Giant Strength",1,"","+2","+2"));
        }
        else if(i==1){
	t.emplace_back(display_enchantment_attack_defence("Enrage",2,"","*2","*2"));
        }
        else if(i==2){
	t.emplace_back(display_enchantment("Haste",1,"Enchanted minion gains +1 action each turn"));
        }
        else if(i==3){
	t.emplace_back(display_enchantment("Magic Fatigue",0,"Enchanted minion's activated ability costs 2 more"));
        }
        else if(i==4){
	t.emplace_back(display_enchantment("Silence",1,"Enchanted minion cannot use abilities"));
        }
    }
    }
    else {
        t.emplace_back(CARD_TEMPLATE_BORDER);
    }
    for (int i=0;i<t.size()/5;i++){
    for(int u=0;u<t[i*5].size();u++){
        for(int j=0;j<5;j++){
	cout<<t[i*5+j][u];
        }
    cout<<endl;
    }
    }
    if(t.size()>0&&t.size()%5){
    for(int u=0;u<t[0].size();u++){
    for(int k=t.size()-t.size()%5;k<t.size();k++){
        cout<<t[k][u];
    }
    cout<<endl;	
    }}
}

void textDisplay::showHand(player* p){
    std::vector<card_template_t> sss;
    for(auto cp : p->hand){
    minion* m=dynamic_cast<minion*>(cp);    
    enchantment *e=dynamic_cast<enchantment*>(cp);
    spell *s=dynamic_cast<spell*>(cp);
    ritual *r=dynamic_cast<ritual*>(cp);
    card_template_t ss;
    if(m){
            int cost = m->getRCost();
            inst con = m->instance();
            if (cost == -1) {
        ss = display_minion_no_ability(m->getName(), m->getCost(), con.atk, con.dfn);
        }
        else if (cost == -2) {
                ss = display_minion_triggered_ability(m->getName(), m->getCost(), con.atk, con.dfn, con.dscr);
        }
            else {
                ss = display_minion_activated_ability(m->getName(), m->getCost(), con.atk, con.dfn, cost, con.dscr);
            }
    }
    if(e){
        int i=e->id;
        if(i==0){
                ss=display_enchantment_attack_defence("Giant Strength",1,"","+2","+2");
            }
            else if(i==1){
                ss=display_enchantment_attack_defence("Enrage",2,"","*2","*2");
            }
            else if(i==2){
                ss=display_enchantment("Haste",1,"Enchanted minion gains +1 action each turn");
            }
            else if(i==3){
                ss=display_enchantment("Magic Fatigue",0,"Enchanted minion's activated ability costs 2 more");
            }
            else if(i==4){
                ss=display_enchantment("Silence",1,"Enchanted minion cannot use abilities");
            }
    }
    if(s){
        ss=display_spell(s->getName(),s->getCost(),s->getDscr());
    }
    if(r){
        ss=display_ritual(r->getName(),r->getCost(),r->getRCost(),r->getDscr(),r->getCharge());
    }
    sss.emplace_back(ss);
    }
    for (int i=0;i<sss.size()/5;i++){
    for(int u=0;u<sss[i*5].size();u++){
        for(int j=0;j<5;j++){
	cout<<sss[i*5+j][u];
        }
        cout<<endl;
    }
    }
    if(sss.size()&&sss.size()%5){
    for(int u=0;u<sss[0].size();u++){
    for(int k=sss.size()-sss.size()%5;k<sss.size();k++){
        cout<<sss[k][u];
    }
    cout<<endl;
    }}
}


void textDisplay::notify(triggerType){
    
}

