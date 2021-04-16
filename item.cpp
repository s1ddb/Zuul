#include <iostream>
#include <cstring>

#include "item.h"


using namespace std;

Item::Item() {

}

void Item::setName(char* ItemName) {


  objname = ItemName;

}

char* Item::getName() {

  return objname; //return's the item's name

}



void Item::setID(int ItemID) {

  id = ItemID;

}

int Item::getID() {


  return id;

}
