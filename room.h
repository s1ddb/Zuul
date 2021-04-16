#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <cstring>
#include <map>

using namespace std;

class Room {


 public:

  Room(); //calling cpp file


  //getters

  map<int, char*>* getExits();

  char* getDescription();
  int getID();
  int getItem();
  

  //setters

  void setExits(map<int, char*>);
  
  void setDescription(char*);
  void setID(int);
  void setItem(int);

 private:

  map<int, char*> exits;

  char* description;
  int id;
  int item;

};


#endif
