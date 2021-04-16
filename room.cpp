#include <iostream>
#include <cstring>
#include <map>

#include "room.h"

using namespace std;

Room::Room() {

  
}


//setter for description
void Room::setDescription(char* Desc){

  description = Desc;

}


//getter for description
char* Room::getDescription(){
  
  return description;

}



//setter for exits
void Room::setExits(map<int, char*> Exit) {

  exits = Exit;

}

// getter for exits
map<int, char*>* Room::getExits() {

  return &exits;

}


//setter for ID
void Room::setID(int TheID){

  id = TheID;

}

//getter for ID
int Room::getID(){

  return id;

}


//setter for items
void Room::setItem(int newItem) {

  item = newItem;

}


//getter for items
int Room::getItem(){

  return item;

}






