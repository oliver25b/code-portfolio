//----------------------------------------------------------------------------
//                  CS 215 - Project 2 - MiniMud
//----------------------------------------------------------------------------
// Author:  Oliver Bartz
// Date:  3/19/2021
// Description:  This program plays a game based off of a text file.
// Assistance: I received help from the following: project 2 documents/specifications, https://www.w3schools.com/cpp/cpp_strings_concat.asp, 
//				class powerpoints, office hours with Tasmia (who explained which structures involved partial arrays),  https://stackoverflow.com/questions/15637556/no-suitable-constructor-exists-to-convert-from-test-to-test-constructor,
//				https://www.iar.com/knowledge/support/technical-notes/compiler/expression-must-be-a-modifiable-lvalue-error/, office hours with Michael, who helped me find a couple typos and remove unnecessary arguments
//-----------------------------------------------------------
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "gameutils.h"
using namespace std;


//logo:
void printlogo() {
	cout << " _____________________________\n|OFF+ +ON                     |\n|  .-----------------------.  |\n|  |  .-----------------.  |  |\n|  |  |                 |  |  |\n|  |  |     MINIMUD     |  |  |\n|  |  |    ADVENTURE    |  |  |\n|  |  |                 |  |  |\n|  |  |  -OLIVER BARTZ  |  |  |\n|  |  '-----------------'  |  |\n|  |__GAME BOY_____________|  |\n|           ________          |\n|     ,    (Nintendo)         |\n|   _| |_   \"\"\"\"\"\"\"\"     .-.  |\n| -[_   _]-         .-. (   ) |\n|    |_|           (   ) '-'  |\n|     '             '-'   A   |\n|                    B        |\n|             ___   ___       |\n|            (___) (___)  ,., |\n|           Select Start ;:;: |\n|                       ,;:;' /\n|                      ,:;:'.'\n'--------------------------`\n";
}


string getInputFileName() {
	cout << "Enter name of the game to play: ";
	string filename;
	getline(cin, filename);
	filename = filename.append(".txt");
	return filename;
}

void initItems(item item[]) {
	for (int i = 0; i < MAX_ITEMS; i++) {
		item[i].shortDesc = "";
		item[i].longDesc = "";
	}
	//cout << "***DEBUG: initItems has ran.***\n";
}

void initRooms(room r[]) {
	for (int i = 0; i < MAX_ROOMS; i++) {
		r[i].shortDesc = "";
		r[i].longDesc = "";
		r[i].north = NO_EXIT;
		r[i].south = NO_EXIT;
		r[i].east = NO_EXIT;
		r[i].west = NO_EXIT;
		r[i].numItems = 0;
	 	initItems(r[i].items);
	}
	//cout << "***DEBUG: initRooms has ran***\n";
}

/*void initWinData(winDataStruct & s) {
	s.winMessage = "";
	s.winRoom = NO_EXIT;
	s.numWinItems = 1;
	initItems(s.winItem); 
}


item removeItem(int index, item a[], int & numItems) {
	item rem; //= { "", "" }; // rem.shortDes = "", rem.longDes = ""
	if((index >= 0) && (index < numItems)) {
		rem = a[index];
		//numItems = numItems - 1;
		for (int i = index; i < numItems; i++) {
			a[i] = a[i + 1];
		}
	}    
	else if (index < 0){
		string error = "removeItem: invalid index = ";
		error.append(to_string(index));
		gameAbort(error);
	}
	return rem;  
}*/

void addItem(item n, item items[], int & numItems) {
	cout << "attempting to add item " << n.shortDesc << " using addItem";
	if (numItems >= MAX_ITEMS) {
		string error = "addItem: maximum number of items exceeded!\n";
		gameAbort(error);
	}
	if (numItems == 0)
		items[0] = n;
	else 
		items[numItems + 1] = n;
	numItems = numItems + 1;
	cout << "***DEBUG: after addItem, there are now " << numItems << " items and the item just added has shortDesc " << items[numItems].shortDesc << "***\n";
}

void addItem(string shortdes, string longdes, item items[], int & numItems) {
	item newItem;
	newItem.shortDesc = shortdes;
	newItem.longDesc = longdes;
	addItem(newItem, items, numItems); 
}


string getCmd(string & remainder) {
	string input, cmd;
	cout << "==> ";
	if (cin.peek() == '\n') cin.ignore();
	getline(cin, input);              //it hated when i tried to use cleanGetLine so this will have to work
	cmd = split(input, remainder);
	return cmd;
}

/*string makeExitList(room thisRoom) {
	string exitList = "You can go:";
	if (thisRoom.north != NO_EXIT) exitList += " north,";
	if (thisRoom.south != NO_EXIT) exitList += " south,";
	if (thisRoom.east != NO_EXIT) exitList += " east,";
	if (thisRoom.west != NO_EXIT) exitList += " west.";
	exitList[exitList.length() - 1] = '. '; // change last comma to a period
	return exitList;
}
*/
void doLook(room area, bool length) {
	cout << "doLook has been fed " << area.numItems << " items to look at\n";
	if (length == true) {
		cout << area.shortDesc << "\n";
		if (area.numItems == 0) {
			cout << "There's nothing in this room.\n";
		}
		else if (area.numItems == 1)
			cout << "You notice the following: " << area.items[area.numItems].shortDesc << ".\n";
		else {
			for (int i = area.numItems; i > 0; i--) {
				cout << "You notice the following: " << area.items[i].shortDesc << ", ";
			}
			cout << ".\n";
		}
	}
	else {
		cout << area.longDesc << "\n";
		if (area.numItems == 0) {
			cout << "There's nothing in this room.\n";
		}
		else if (area.numItems == 1)
			cout << "You notice the following: " << area.items[area.numItems].longDesc << ".\n";
		else {
			for (int i = area.numItems; i > 0; i--) {
				cout << "You notice the following: " << area.items[i].longDesc << ", ";
			}
			cout << ".\n";
		}
	}
	string output;
	//output = makeExitList(area);  
	cout << output;
}

void doLook(room r) {
	doLook(r, false);
}

/*
//----------------------------------------------------------------------------
//							doInventory
//----------------------------------------------------------------------------
// Given: the player's inventory (partial array of items)
// This is the game's response to the "inv"/"i" (inventory) command.
// Prints a message telling the player what he/she is holding.
//----------------------------------------------------------------------------
void doInventory(item item[], int numItems) {
	if (numItems == 0)
		cout << "You don't have anything.\n";
	else {
		cout << "You are holding: ";
		for (int i = 0; i < (numItems - 1); i++)		// for all but last item          i think this might break if numItems = 0
			cout << item[i].shortDesc << ", ";			// print short desc with comma
		cout << item[numItems - 1].shortDesc << ".\n";  // for last item, use period and newline
	}
} // doInventory()

//----------------------------------------------------------------------------
//							goNorth
//----------------------------------------------------------------------------
// Given:    partial array of rooms
// Modifies: index of current room
// This is the game's response to the player entering the "north"/"n" command.
// When the north exit exists, changes the current room index and performs
// a "look" command with a short room description
void goNorth(int& currentRoom, room rooms[]) {
	if (rooms[currentRoom].north == NO_EXIT)
		cout << "You can't go north.\n";
	else {
		currentRoom = rooms[currentRoom].north;
		doLook(rooms[currentRoom], true); // true = show short room desc.    ////////start with fixing this one!!!!!!!!!!!
	}
} // goNorth()

void goSouth(int& currentRoom, room rooms[]) {
	if (rooms[currentRoom].south == NO_EXIT)
		cout << "You can't go south.\n";
	else {
		currentRoom = rooms[currentRoom].south;
		doLook(rooms[currentRoom], true);
	}
}

void goEast(int& currentRoom, room rooms[]) {
	if (rooms[currentRoom].east == NO_EXIT)
		cout << "You can't go east.\n";
	else {
		currentRoom = rooms[currentRoom].east;
		doLook(rooms[currentRoom], true);
	}
}

void goWest(int& currentRoom, room rooms[]) {
	if (rooms[currentRoom].west == NO_EXIT)
		cout << "You can't go west.\n";
	else {
		currentRoom = rooms[currentRoom].west;
		doLook(rooms[currentRoom], true);  
	}
}

int findItem(item items[], int& numItems, string search) {
	int index = NOT_FOUND;
	//printItems(items, numItems);
	cout << "***DEBUG: the number of items that findItem has been fed is " << numItems << "***\n";
	for (int i = 0; i <= numItems; i++) {
		//cout << "***DEBUG: the for loop inside findItem is running! searching item " << i << "'s short description, " << items[i].shortDesc << ", for " << search << "***\n";
		if (items[i].shortDesc == search) {   
			index = i;
			//cout << "***DEBUG: an item has been found in search, with index of " << index << "***\n";
			return index;
		}

	}
	cout << "***DEBUG: index of findItem has returned " << index << "***\n";
	return index;
}

void doExamine(string nameItem, item roomInv[], int numRoomItems, item playerInv[], int numPlayerItems) {
	int invPos;
	 invPos = findItem(roomInv, numRoomItems, nameItem);
	if (invPos == NOT_FOUND) {
		invPos = findItem(playerInv, numPlayerItems, nameItem);
		if (invPos == NOT_FOUND) {
			cout << "You see no " << nameItem;
		}
		else {
			cout << playerInv[invPos].longDesc;
		}
	}
	else {
		cout << roomInv[invPos].longDesc;
	}
}

void doTake(string nameItem, item roomInv[], int& numObjRoom, item playerInv[], int& numObjPlayer) {
	int index;
	item object;
	index = findItem(roomInv, numObjRoom, nameItem);
	if (index != NOT_FOUND) {
		if (numObjPlayer < MAX_ITEMS) {
			object = removeItem(index, roomInv, numObjRoom);
			addItem(object, playerInv, numObjPlayer);     
			cout << "You take the " << nameItem;
			numObjRoom--;
			numObjPlayer++;
		}
		else
			cout << "Your hands are full, you can't take that.";
	}
	else {
		index = findItem(playerInv, numObjPlayer, nameItem); 
		if (index != NOT_FOUND)
			cout << "You already have the " << nameItem;
		else
			cout << "You see no " << nameItem;
	}
}

void doDrop(string nameItem, item roomInv[], int& numRoomObj, item playerInv[], int& numPlayerObj) {
	item object;
	int index;
	index = findItem(playerInv, numPlayerObj, nameItem);
	if (index != NOT_FOUND) {
		if (numRoomObj < MAX_ITEMS) {
			object = removeItem(index, playerInv, numPlayerObj);
			addItem(object, roomInv, numRoomObj);  
			cout << "You drop the " << nameItem << ".";
			numPlayerObj--;
			numRoomObj++;
		}
		else
			cout << "The room is full of stuff; you can't drop that.";
	}
	else {
		index = findItem(roomInv, numRoomObj, nameItem);
		if (index != NOT_FOUND)
			cout << "You don't have the " << nameItem;
		else
			cout << "You have no " << nameItem;
	}
}

bool gameWon(winDataStruct w, room r[], int numRooms) {
	int index;
	for (int i = 0; i < numRooms; i++) {
		if (w.numWinItems <= r[i].numItems) {
			index = findItem(r[w.winRoom].items, w.numWinItems, w.winItem[i].shortDesc);
			if (index != NOT_FOUND) {
				return true;
			}
			else return false;
		}
		else return false;
	}
	return false;
}
*/
void loadData(room rooms[], int& numRooms, winDataStruct& winData) {
	// variable declarations
	ifstream f;				// input file handle
	string tag;				// first word extracted from each line
	string filename;		// name of input file
	string data;			// data read from file using cleanGetline()
	int roomNdx = -1;		// index of the "current room" being read/populated
							// this should always be numRooms-1 

	// initialize the rooms and winData
	initRooms(rooms);
	//initWinData(winData);  

	// get input file name and open the input file; abort on failure
	filename = getInputFileName();
	f.open(filename);
	if (f.is_open() == false) {
		string error = "Unable to open ";
		error.append(filename);
		gameAbort(error);
	}
	
	// read line-by-line and store data in the game data structures
	f >> tag;
	while (tag != "END:") {
		//cout << "reading the file!" << "\n";
		if (tag == "ROOM:") {
			numRooms++;		// starting a new room
			roomNdx++;		// increment every time numRooms is incremented
			cleanGetline(f, rooms[roomNdx].shortDesc); // short desc on remainder of ROOM: line
			cleanGetline(f, rooms[roomNdx].longDesc);  // long desc on next line by itself (no tag)
		}
		else if (tag == "ITEM:") {
			string shortDesc, longDesc;
			cleanGetline(f, shortDesc);
			cleanGetline(f, longDesc);
			//cout << "***DEBUG: about to feed addItem with shortDesc " << shortDesc << " , longDesc " << longDesc << ", room index " << roomNdx << ", and number of items in room " << rooms[roomNdx].numItems << "***\n";
			addItem(shortDesc, longDesc, rooms[roomNdx].items, rooms[roomNdx].numItems);
			//cout << "***DEBUG: an item " << rooms[roomNdx].items[1].shortDesc << " has been read from the file and applied to a room " << rooms[roomNdx].shortDesc << " with an index of " << roomNdx << "***\n";
		}
		else if (tag == "WIN_ITEM:") {
			cleanGetline(f, data);
			addItem(data, "", winData.winItem, winData.numWinItems);
		}
		else if (tag == "NORTH:")
			f >> rooms[roomNdx].north;
		else if (tag == "SOUTH:")
			f >> rooms[roomNdx].south;
		else if (tag == "EAST:")
			f >> rooms[roomNdx].east;
		else if (tag == "WEST:")
			f >> rooms[roomNdx].west;
		else if (tag == "WIN_ROOM:")
			f >> winData.winRoom;
		else if (tag == "REMARK:")
			cleanGetline(f, data);		// data is junk, throw it away
		else if (tag == "WIN_TEXT:")
			cleanGetline(f, winData.winMessage);
		else if (tag == "END:")
			gameAbort("Game ended");
		else
			gameAbort("Unknown tag in " + filename + ": " + tag);

		// check for read failure and read the next tag
		if (f.fail())
			gameAbort("Failure while reading input file " + filename);
		f >> tag;
	}
	cout << "DEBUG: at the end of loadData, there are " << numRooms << " rooms, and room zero has " << rooms[0].numItems << " items. The first item is " << rooms[0].items[1].shortDesc << "***\n";
}


void startUp(room r[], int& numRooms, item i[], int& numItems, winDataStruct& w) { // r is room, i is player inventory
	printlogo();
	initItems(i);
	loadData(r, numRooms, w);
	cout << "loadData says that the room has " << r[0].items[0].shortDesc << " as item 0 and " << r[0].items[1].shortDesc << "as item 1\n";
	numItems = 0;
	//cout << "***DEBUG: startUp has retrieved room information. Room 0, for example, has an item " << r[0].items[1].shortDesc << "***\n";
	cout << "You awaken covered in sweat. You don't recognize where you are...\n";
	//cout << "***DEBUG: this room has " << r[0].numItems << " items, and you are in room " << r[0].shortDesc << "***\n";
	doLook(r[START_ROOM], true);  
}

//----------------------------------------------------------------------------
//							main
//----------------------------------------------------------------------------

int main() {
	// declare data structures
	room rooms[MAX_ROOMS];
	item items[MAX_ITEMS];
	winDataStruct winData;

	// declare other variables
	string cmd;					// command entered by user (first word of input)
	string remainder;			// remainder of command entered by user
	bool   gameWasWon = false;	// check with gameWon() as needed
	int invSize, numRooms = 0, roomIdx = 0;

	// start up: load game data from file and initialize player inventory
	startUp(rooms, numRooms, items, invSize, winData);
	//cout << "***DEBUG: startUp has completed and item 1 has a shortdesc of " << rooms[0].items[1].shortDesc << "***\n";
	// get first command input
	cmd = getCmd(remainder);

	// repeat until "exit" entered or the game is won
	while (cmd != "exit" && !gameWasWon) {


		//printItems(rooms[roomIdx].items, rooms[roomIdx].numItems);


		if (cmd == "help")
			printHelp();
		// add cases for other commands and invocations
		else if (cmd == "look" || cmd == "l")
			doLook(rooms[roomIdx], false);
		/*else if (cmd == "inv" || cmd == "i"){
			//invSize++;
			doInventory(items, invSize);
		}
		else if (cmd == "exa" || cmd == "x") {
			// DEBUG cout << rooms[roomIdx].items[1].shortDesc;
			doExamine(remainder, rooms[roomIdx].items, rooms[roomIdx].numItems, items, invSize);
		}
		else if (cmd == "take" || cmd == "t")
			doTake(remainder, rooms[roomIdx].items, rooms[roomIdx].numItems, items, invSize);
		else if (cmd == "drop" || cmd == "d")
			doDrop(remainder, rooms[roomIdx].items, rooms[roomIdx].numItems, items, invSize);
		else if (cmd == "north" || cmd == "n")
			goNorth(roomIdx, rooms);
		else if (cmd == "south" || cmd == "s")
			goSouth(roomIdx, rooms);
		else if (cmd == "east" || cmd == "e") {
			//cout << "you said to go east, so let's try doing that\n";
			goEast(roomIdx, rooms);
		}
		else if (cmd == "west" || cmd == "w") {
			//cout << "you said to go west, let's try that \n";
			goWest(roomIdx, rooms);
		}
		else // the user entered an unrecognized command
			cout << "What??\n";
		// check if game was won and print win message or get next user input
		gameWasWon = gameWon(winData, rooms, numRooms);
		if (gameWasWon)
			cout << winData.winMessage << endl;
		else
			cmd = getCmd(remainder);*/
	}

	system("pause");
	return 0;
}





