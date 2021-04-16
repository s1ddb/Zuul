#include <iostream>
#include <cstring>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>

#include "room.h"
#include "item.h"

using namespace std;


//initializing functions

void initRooms(vector<Room*>* rooms);

void initItems(vector<Item*>* items);

void printRoom(vector<Room*>* rooms, vector<Item*>* items, int currentRoom); //function to print the current room with the items in it

void printInventory(vector<Item*>* items, vector<int> *inv); //function to print out the items inside the inventory

void getItem(vector<Room*>* rooms, vector<Item*>* items, vector<int>* inv, int currentRoom, char objname[]); //function to pick an item up from a room

void dropItem(vector<Room*>* rooms, vector<Item*>* items, vector<int>* inv, int currentRoom, char objname[]); //function to drop an item

int move(vector<Room*>* rooms, int currentRoom, char userinput[]);


int main() {


  //setting up variables inside of main

  vector<Room*>* ListRooms = new vector<Room*>();
  vector<Item*>* ListItems = new vector<Item*>();
  vector<int>* inventory = new vector<int>();

  initRooms(ListRooms); //passes the initialized room to the vector named ListRooms
  initItems(ListItems);

  bool running = true; //sets game running to true
  
  char userinput[40]; //variable for user's input
  int currentRoom = 1; //integer to check which room user is in


  cout << "You are outside your high school. You had graduated last week." << endl;
  cout << "You had left some of your stuff inside before you graduated." << endl << "Go inside and check whatever belongings you have left in your old school and pick them up." << endl;
  cout << "Do not take anything you do not need though! The school might get you in trouble for stealing! good luck!" << endl;
  cout << endl;

  while (running == true) {

    cout << "You are currently in" << endl;
    printRoom(ListRooms, ListItems, currentRoom);
    cin >> userinput;
    cin.ignore(1000, '\n');

    //GO COMMAND
    if (strcmp(userinput, "GO") == 0) {
      
      cout << "Which direction do you want to go?" << endl;
      
      cin >> userinput;
      cin.clear();
      cin.ignore(1000, '\n');
      
      if (move(ListRooms, currentRoom, userinput) == 0) {
	
	cout << endl << "There is nothing there!" << endl;
      
      }
      else {

	currentRoom = move(ListRooms, currentRoom, userinput);
	
      }

    }

    //GET COMMAND
    else if (strcmp(userinput, "GET") == 0) {


      cout << "What item do you want to grab: " << endl;

      cin >> userinput;
      cin.clear();
      cin.ignore(1000, '\n');

      getItem(ListRooms, ListItems, inventory, currentRoom, userinput);


    }

    //DROP COMMAND
    else if (strcmp (userinput, "DROP") == 0) {

      cout << "What do you want to drop?" << endl;

      cin >> userinput;
      cin.clear(); //clears the input for next use
      cin.ignore(1000, '\n'); //terminating char
      
      dropItem(ListRooms, ListItems, inventory, currentRoom, userinput); //drops the selected item
      
    }

    //INVENTORY COMMAND
    else if (strcmp (userinput, "INVENTORY") == 0) {

      if (inventory->size() != 0) {
	
	cout << endl << "You currently have: ";
	printInventory(ListItems, inventory);
	
      }
      else {
	
	cout << endl << "Your inventory is empty." << endl;
	
      }

    }

    //QUIT COMMAND
    else if (strcmp(userinput, "QUIT") == 0) {

      running = false;

    }


    //HELP COMMAND
    else if (strcmp(userinput, "HELP") == 0) {

      cout << "Your commands are: GO, GET, DROP, INVENTORY, QUIT, and HELP." << endl;
    }
    //if none, error
    else {
      cout << endl <<"Invalid input entered." << endl;
    }  


    
//win conditions go here:
  vector<int>::iterator win;


  bool item1 = false;
  bool item2 = false;
  bool item3 = false;
  bool item4 = false;
  bool item5 = false;
  
  for(win= inventory->begin(); win!= inventory->end(); win++) {

    if((*win) == 1) {

      item1 = true;

    }
    if ((*win) == 2) {

      item2 = true;

    }
    if ((*win) == 3) {

      item3 = true;
    }
    if ((*win) == 4) {

      item4 = true;

    }
    if ((*win) == 5) {

      item5 = true;

    }
  }
  
  
  if (currentRoom == 1 && item1 == true && item2 == true && item3 == true) {
    cout << endl << "You win! You got everything you need!" << endl << endl;
    return 0;
  }
  //lose conditions
  if (item5 == true || item4 == true) {
    cout << endl << "Do you really need this?" << endl;
    cout << "You lose!" << endl << endl;
    return 0;
  }    
  

  } // while running
  
  
}





void initRooms(vector<Room*>* rooms) {


  //setting char arrays for each direction
  
  char* north = new char[6];
  strcpy(north, "north");

  char* south = new char[6];
  strcpy(south, "south");

  char* east = new char[5];
  strcpy(east, "east");

  char* west = new char[5];
  strcpy(west, "west");

  
  // entry/exit descriptions:
  //char* north = (char*)("north");
  //char* south = (char*)("south");
  //char* east = (char*)("east");
  //char* west = (char*)("west");
  
  //initializing temp map to pass in the pathways/exits
  map<int, char*> temp;
  
  //rooms:

  //outdoor space room
  Room* outdoor  = new Room();
  
  char* Des = new char[80];
  strcpy(Des, "in the outdoor space.");


  outdoor -> setDescription(Des);
  outdoor -> setID(1);
  temp.insert(pair<int, char*> (2, north));
  outdoor -> setExits(temp);
  outdoor -> setItem(0);
  rooms -> push_back(outdoor);
  temp.clear();

  //attendance room
  Room* attend = new Room();

  char* Att = new char[80];
  strcpy(Att, "in the Attendance room.");

  attend -> setDescription(Att);
  attend -> setID(2);
  temp.insert(pair<int, char*> (4, north));
  temp.insert(pair<int, char*> (3, west));
  temp.insert(pair<int, char*> (1, south));
  attend -> setExits(temp);
  attend -> setItem(0);
  rooms -> push_back(attend);
  temp.clear();

  
  Room* welchall= new Room();

  char* welc = new char[80];
  strcpy(welc, "in the Welcome Hallway.");

  
  welchall-> setDescription(welc);
  welchall-> setID(3);
  temp.insert(pair<int, char*> (2, east));
  temp.insert(pair<int, char*> (5, north));
  welchall-> setExits(temp);
  welchall-> setItem(0);
  rooms -> push_back(welchall);
  temp.clear();

  
  Room* ahall = new Room();

  char* ah = new char[80];
  strcpy(ah, "in the A-Hall.");

  ahall -> setDescription(ah);
  ahall -> setID(5);
  temp.insert(pair<int, char*> (3, south));
  temp.insert(pair<int, char*> (6, west));
  temp.insert(pair<int, char*> (9, east));
  ahall -> setExits(temp);
  ahall -> setItem(0);
  rooms -> push_back(ahall);
  temp.clear();
  
  Room* mathroom = new Room();

  char* math = new char[80];
  strcpy(math, "in the math classroom.");

  mathroom -> setDescription(math);
  mathroom -> setID(6);
  temp.insert(pair<int, char*> (5, east));
  temp.insert(pair<int, char*> (7, north));
  mathroom -> setExits(temp);
  mathroom -> setItem(1/*MathTextbook*/);
  rooms -> push_back(mathroom);
  temp.clear();
  
  Room* astro = new Room();

  char* astr = new char[80];
  strcpy(astr, "in the Astronomy classroom.");

  astro -> setDescription(astr);
  astro -> setID(7);
  temp.insert(pair<int, char*> (6, south));
  astro -> setExits(temp);
  astro -> setItem(0);
  rooms -> push_back(astro);
  temp.clear();
  
  Room* chemlab = new Room();

  char* cheml = new char[80];
  strcpy(cheml, "in the Chemistry lab.");

  chemlab -> setDescription(cheml);
  chemlab -> setID(8);
  temp.insert(pair<int, char*> (9, south));
  chemlab -> setExits(temp);
  chemlab -> setItem(0);
  rooms -> push_back(chemlab);
  temp.clear();
  
  Room* bhall = new Room();
  
  char* bh = new char[80];
  strcpy(bh, "in the B-Hall");
  
  bhall -> setDescription(bh);
  bhall -> setID(9);
  temp.insert(pair<int, char*> (5, west));
  temp.insert(pair<int, char*> (8, north));
  temp.insert(pair<int, char*> (11, south));
  temp.insert(pair<int, char*> (13, east));
  bhall -> setExits(temp);
  bhall -> setItem(0);
  rooms -> push_back(bhall);
  temp.clear();
  
  Room* menlock = new Room();
  
  char* loc = new char[80];
  strcpy(loc, "in the Men's locker room. You should go find your locker");
  
  menlock -> setDescription(loc);
  menlock -> setID(11);
  temp.insert(pair<int, char*> (9, north));
  temp.insert(pair<int, char*> (10, west));
  temp.insert(pair<int, char*> (12, east));
  menlock -> setExits(temp);
  rooms -> push_back(menlock);
  temp.clear();
  
  Room* jancloset = new Room();
  
  
  char* jan = new char[80];
  strcpy(jan, "in the Janitor's closet. What are you even doing here?");
  
  jancloset -> setDescription(jan);
  jancloset -> setID(10);
  temp.insert(pair<int, char*> (8, east));
  jancloset -> setExits(temp);
  jancloset -> setItem(4/*broomstick*/);
  rooms -> push_back(jancloset);
  temp.clear();
  
  Room* music= new Room();
  
  char* musi = new char[80];
  strcpy(musi, "in the Studio! This is the school's music room. It's cool.");
  
  music-> setDescription(musi);
  music-> setID(13);
  temp.insert(pair<int, char*> (9, west));
  temp.insert(pair<int, char*> (14, south));
  music-> setExits(temp);
  music-> setItem(5/*SchoolMedallion*/);
  rooms -> push_back(music);
  temp.clear();
  
  Room* yourlock = new Room();
  
  char* uloc = new char[80];
  strcpy(uloc, "At your locker. You should grab your stuff!");
  
  yourlock -> setDescription(uloc);
  yourlock -> setID(12);
  temp.insert(pair<int, char*> (11, west));
  yourlock -> setExits(temp);
  yourlock -> setItem(2/*Chromebook*/);
  rooms -> push_back(yourlock);
  temp.clear();
  
  Room* curlyhall = new Room();
  
  char* curl = new char[80];
  strcpy(curl, "in the curly hallway! Fancy? No!?");
  
  curlyhall -> setDescription(curl);
  curlyhall -> setID(14);
  temp.insert(pair<int, char*> (13, north));
  temp.insert(pair<int, char*> (15, south));
  curlyhall -> setExits(temp);
  curlyhall -> setItem(0);
  rooms -> push_back(curlyhall);
  temp.clear();
  
  Room* equip = new Room();
  
  char* eqp = new char[80];
  strcpy(eqp, "in the equipment room. No other way to go, just back. Check if you left your helmet here.");

  equip -> setDescription(eqp);
  equip -> setID(15);
  temp.insert(pair<int, char*> (14, south));
  equip -> setExits(temp);
  equip -> setItem(3/*LinkCrewTshirt*/);
  rooms -> push_back(equip);
  temp.clear();
  
  Room* mainoff = new Room();
  
  char* maino = new char[80];
  strcpy(maino, "in the Main office. Here you'll find any school supplies; And your scary counsellor's desk.");
  
  mainoff -> setDescription(maino);
  mainoff -> setID(4);
  temp.insert(pair<int, char*> (2, south));
  mainoff -> setExits(temp);
  mainoff -> setItem(0);
  rooms -> push_back(mainoff);
  temp.clear();
  
}



void initItems(vector<Item*>* items) {
  
  Item* link = new Item();
  link -> setName((char*)("LinkcrewTshirt"));
  link -> setID(3);
  items -> push_back(link);
  
  Item* book = new Item();
  book -> setName((char*)("MathTextbook"));
  book -> setID(1);
  items -> push_back(book);
  
  Item* chrome = new Item();
  chrome -> setName((char*)("Chromebook"));
  chrome -> setID(2);
  items -> push_back(chrome);
  
  Item* bsticc = new Item();
  bsticc -> setName((char*)("broomstick"));
  bsticc -> setID(4);
  items -> push_back(bsticc);
  
  //car keys
  Item* medal = new Item();
  medal -> setName((char*)("SchoolMedallion"));
  medal -> setID(5);
  items -> push_back(medal);
}





int move(vector<Room*>* rooms, int currentRoom, char userinput[]) {

  vector<Room*>::iterator i;

  for (i =rooms->begin(); i != rooms->end(); i++) {

    if (currentRoom == (*i)->getID()) {
      map<int, char*> exits;
      exits = *(*i) -> getExits();

      map<int, char*>::iterator a;
      for (a = exits.begin(); a != exits.end(); ++a) {

	if (strcmp(a -> second, userinput) == 0) {

	  return a -> first;
	  
	}
	
      }

    }

  }
  return 0;

}


void printRoom(vector<Room*>* rooms, vector<Item*>* items, int currentRoom) {
  
  vector<Room*>::iterator rom;
  vector<Item*>::iterator itm;

  for(rom= rooms->begin(); rom!= rooms->end(); rom++) {

    if (currentRoom == (*rom)->getID()) {
      cout << (*rom)->getDescription() << endl;
      cout << "  Exits: ";
      //exits

      for(map<int, char*>::const_iterator it = (*rom) -> getExits() -> begin(); it != (*rom) -> getExits() -> end(); it++) {
	//printing exits
	cout << it -> second << " ";
      }
      cout << endl;
      //items
      cout << "  Items in this room: ";
      
      int itemCount = 0; //for the "there's no items" prompt

      for(itm = items->begin(); itm != items->end(); itm++) {

	if ((*rom)->getItem() == (*itm)->getID()) {
	  //print spcific item
	  cout << (*itm)->getName();
	  itemCount++;
	}
      }
      
      if (itemCount == 0) {
	cout << "There's no items here." << endl;
      } else {
	cout << endl;
      }
    }
  }
}




void printInventory(vector<Item*>* items, vector<int> *inv) {

  vector<Item*>::iterator itm;
  vector<int>::iterator in;

  for(itm = items->begin(); itm != items->end(); itm++) {

    for(in = inv->begin(); in != inv->end(); in++) {

      if (*in == (*itm) -> getID()) {
	cout << (*itm) -> getName() << " ";

      }

    }

  }

  cout << endl; //space

}

void getItem(vector<Room*>* rooms, vector<Item*>* items,vector<int>* inv, int currentroom, char objname[]) {

  vector<Room*>::iterator rom;
  vector<Item*>::iterator itm;
  
  for(rom= rooms->begin(); rom!= rooms->end(); rom++) {
    
    if (currentroom == (*rom) -> getID()) {
      
      for(itm = items->begin(); itm != items->end(); itm++) {
	
	//if item is in room
	if (((*rom) -> getItem() == (*itm) -> getID()) && (strcmp((*itm) -> getName(), objname) == 0)) {

	  //add to inventory
	  inv -> push_back((*itm) -> getID());
	  
	  //set no item in room
	  (*rom) -> setItem(0);
	  
	  cout << endl << "Picked up: " << (*itm) -> getName() << "." << endl;
	  
	  return;

	}
      }
    } 
  }

  cout << "There is no such item in this room." << endl;

}



void dropItem(vector<Room*>* rooms, vector<Item*>* items, vector<int>* inv, int currentRoom, char objname[]) {
  
  int count;
  
  vector<Room*>::iterator rom;
  vector<Item*>::iterator itm;
  vector<int>::iterator i;

  for(rom = rooms->begin(); rom != rooms->end(); rom++) { //go through room

    //if inside currentRoom
    if(currentRoom == (*rom) -> getID()) {

      //if no items are in the room (item limit per room: one)
      if ((*rom) -> getItem() == 0) {
	
	for (itm = items->begin(); itm != items->end(); itm++) { //loop and go through items

	  //if there is an item
	  if (strcmp((*itm) -> getName(), objname) == 0) {
	    
	    for (i = inv -> begin(); i != inv -> end(); i++) { //go through inventory

	      //if the item is in the inventory
	      if ((*i) == (*itm) -> getID()) {
		
		cout << endl << "dropped item: " << (*itm) -> getName() << "." << endl;

		//set/drop item in current room
		(*rom) -> setItem((*itm) -> getID());

		//erase item from inventory
		i = inv -> erase(i);

		return;
		
	      }
	    }
	  }
	  
	  else if (count == items -> size() - 1) {
	    cout << endl << "There is no such item in your inventory." << endl;
	  }
	  count++;
	}
      }
      else {

	cout << endl << "There is an item in the room already! A room can only have 1 item." << endl;
	
      } // else
      
    }// end of if statement
    
  } // end of for loop
  
} //void
