#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <cstring>

using namespace std;


class Item {

 public:

  Item();

  void setName(char*);
  char* getName();

  void setID(int);
  int getID();
  

 private:

  char* objname;
  int id;

};

#endif
