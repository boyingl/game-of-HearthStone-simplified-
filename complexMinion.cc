#include "complexMinion.h"
#include <string>
using namespace std;


inst::inst(int a, int d, string ds, std::vector<int> v) :atk{ a }, dfn{ d }, dscr{ ds }, ens{ v }{}

complexMinion::complexMinion(string name,int id,int cost,string dscr):card{name,id,cost,dscr}{}

complexMinion::~complexMinion(){
}
