#include "player.h"
#include "gameMaster.h"
#include "textDisplay.h"
#include "graphicDisplay.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <string>
#include "exceptionType.h"

using namespace std;

int main(int argc, char* argv[]){
  //deal with command line argument
  string gameSourceName = "";
  string deck1SourceName = "";
  string deck2SourceName = "";

  bool displayGraphics = false;
  bool isInTesting = false;

  int numArgs = argc -1;
  std::vector<std::string> args{argv, argv+argc};

  //potential improvement????
  if(numArgs != 0){
    try{
      for(int i = 1; i < argc; i++){
        cout << args[i] << endl;
      }
      for(int i = 1; i < argc; i++){
        if(args[i] == "-init"){
          i++;
          gameSourceName = string(args[i]);
        }
        else if(args[i] == "-deck1"){
          i++;
          deck1SourceName = string(args[i]);    
        }
        else if(args[i] == "-deck2"){
          i++;
          deck2SourceName = string(args[i]);
        }
        else if(args[i] == "-graphics") displayGraphics = true;
        else if(args[i] == "-testing") isInTesting = true;
        else if(args[i] == "-easy") deck2SourceName = "easy.deck";
        else if(args[i] == "-medium") deck2SourceName = "medium.deck";
        else if(args[i] == "-hard") deck2SourceName = "hard.deck";
        else throw arguError(string(args[i] + " is a invalid command line argument"));
      }
    }
    catch(arguError ae){
      ae.printMsg(cout);
      return 0;
    }
  }

  ifstream finGame {gameSourceName};
  istream& gameSource = (gameSourceName == "")? cin : finGame;
  bool fromCin = (gameSourceName == "");
  deck1SourceName = (deck1SourceName == "")? "defualt.deck" : deck1SourceName;
  deck2SourceName = (deck2SourceName == "")? "defualt.deck" : deck2SourceName;

  ifstream deck1Source {deck1SourceName};
  ifstream deck2Source {deck2SourceName};



  //setup game master gm with game source 
    //factory create side
    //setup side1 with & deck source & should shuffle flag
    //setup side2
    //assign side to active/nonactive
  master* gm = new master{};
  gm->setTesting(isInTesting);
  gm->setGraphics(displayGraphics);
  //check sequence
  gm->setupGame(deck1Source, deck2Source, gameSource);
  int counter = 0;
  string commandLine;
//game loop
  try{    
    while(true){
    //cmd loop
    while(true){
      cout << "this is player " << gm->getActiveName() << "'s turn" << endl;
      if(fromCin) {if(!getline(cin, commandLine)) throw exitGame("no more input");}
      else {
        if(!getline(gameSource, commandLine)){
        fromCin = true;
        continue;
        }
      } 
      try{
        istringstream cLine {commandLine};
        string command;
        cLine >> command;

         //quit
        if(command == "quit")  throw exitGame(string("user input quit command"));
   
         //end
        else if(command == "end") break;
   
         //attack(i, j)
        else if(command == "attack") {
          int i, j;
          if( !(cLine >> i)) throw commandError("invalid attack command, attack requires at least 1 index");
          if(i < 0 || i > 5 ) throw commandError("invalid attack command, 1st index out of range");
          if(! (cLine >> j))  gm->passDamage(i);
          else if(j < 0 || j > 5) throw commandError("invalid attack command, 2nd index out of range");
          else gm->passDamage(i, j); //need passDamage(1& 2 para)
        }
       
         //play (aka use & place), use i's in hand on p'j
        else if(command == "play") {
          int i, p;
          string j; //might be 1~5 or r
          if( !(cLine >> i)) throw commandError("invalid play command, need at least 1 index");
          if(i < 0 || i > 5 ) throw commandError("invalid play command, 1st index out of range");

          if(! (cLine >> p))  gm->passPlay(i);  //play this card in hand, card has no target

          else if(p < 0 || p > 2) throw commandError("invalid play command, 2nd index out of range");
          //try read in the third command
          else if(! (cLine >> j)) throw commandError("invalid play command, cannot have 2 indices only");

          //has all three 
          else{
            istringstream third {j};
            int index;
            //check if int or char
            if(third >> index){
              if(index < 0 || index > 6) throw commandError("invalid play command, 3rd index out of range");
              else gm->passPlay(i, p, index);
            }
            else if(j == "r"){
              gm->passPlay(i, p, 6); //6 is ritual
            }
            else throw commandError("invalid play command, invalid 3rd index");
          }         
        }
   
        //use the i's card in army on p'j
        //same as play, potential optimization, code reuse???
        else if(command == "use"){          
          int i, p;
          string j; //might be 1~5 or r
          if( !(cLine >> i)) throw commandError("invalid use command, need at least 1 index");
          if(i < 0 || i > 5 ) throw commandError("invalid use command, 1st index out of range");

          if(! (cLine >> p))  gm->passMinionAbility(i);  //play this card in hand, card has no target

          else if(p < 0 || p > 2) throw commandError("invalid use command, 2nd index out of range");
          //try read in the third command
          else if(! (cLine >> j)) throw commandError("invalid use command, cannot have 2 indices only");

          //has all three 
          else{
            istringstream third {j};
            int index;
            //check if int or char
            if(third >> index){
              if(index < 0 || index > 6) throw commandError("invalid use command, 3rd index out of range");
              else gm->passMinionAbility(i, p, index);
            }
            else if(j == "r"){
              gm->passMinionAbility(i, p, 6); //6 is ritual
            }
            else throw commandError("invalid use command, invalid 3rd index");
          }  
        }
      
         //inspect
        else if(command == "inspect"){
          int i;
          if( !(cLine >> i)) throw commandError("invalid inspect command, attack requires 1 index");
          gm->passInspectMinion(i);
          if(displayGraphics) gm->gpassInspectMinion(i);
        }
   
         //hand
        else if(command == "hand"){
          gm->passShowHand();
          if(displayGraphics) gm->gpassShowHand();
        }
   
         //help
        else if(command == "help"){
          cout << "Commands: help -- Display this message.\n" <<
                  "          end -- End the current player's turn.\n" <<
                  "          quit -- End the game.\n" <<
                  "          attack minion other-minion -- Orders minion to attack other-minion.\n" <<
                  "          attack minion -- Orders minion to attack the opponent.\n" <<
                  "          play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\n" <<
                  "          use minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player.\n" <<
                  "          inspect minion -- View a minion's card and all enchantments on that minion.\n" <<
                  "          hand -- Describe all cards in your hand.\n" << 
                  "          board -- Describe all cards on the board." << endl;
        }
     
         //-----if testing mode
         //draw
        else if(command == "draw"){
          if(isInTesting) gm->passDraw();
          else throw commandError("cannot call draw in non testing mode");
        }

         //discard
        else if(command == "discard"){
          int i;
          if( !(cLine >> i)) throw commandError("invalid discard command, attack requires 1 index");
          if(isInTesting) gm->passDiscard(i);
          else throw commandError("cannot call draw in non testing mode");
        }

        else if(command == "board"){
          gm->passShowBoard();
          if(displayGraphics) gm->gpassShowBoard();
        }

        else throw commandError(commandLine + string( " is a invalid command"));
      }
      catch(commandError ce)  {ce.printMsg(cout);}
    }
    gm->passTrigger(endTurn); 
    gm->swap();
    if(counter) gm->passSotSetup();
    else counter ++;
    gm->passTrigger(startTurn);
    }
  } 
  catch(exitGame eg)  {
    eg.printMsg(cout); 
    delete gm;
    return 0;
  }

  cout << "no more command input, game ends" << endl;
  

  delete gm;
  return 0;  
}




