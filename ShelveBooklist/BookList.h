#pragma once

#include <string>

using namespace std;

struct BookNode
{
	string title;
	BookNode * next;

	BookNode()
	{

	}
	BookNode(string bookTitle, BookNode * nextItem = NULL)
	{
		title = bookTitle;
		next = nextItem;
	}
};

class BookList
{
public:

	BookList();
	~BookList();

	//Purpose: checks to see if list is empty
	//Requires: head pointer
	//Returns: true of false
	bool isEmpty();
	
	//Purpose: inserts a new title into the linked list
	//Requires: linked list initialized, new title to insert
	//Returns: linked list with new titile inserted
	void insertTitle(string bookTitle);

	//Purpose: removes a title from the linked list
	//Requires: linked list initialized, tile to be removed
	//Returns: linked list with specified title removed
	void removeTitle(string bookTitle);

	//Purpose: returns the value of length
	//Requires: none
	//Returns: length
	int provideLength();
	
	
	//Purpose: returns the head pointer
	//Requires: head pointer initialized
	//Returns: head pointer
	BookNode *provideHead();

	//Purpose: returns the current pointer
	//Requires: current pointer initialized
	//Returns: current pointer
	BookNode *provideCurrent();
		
	//Purpose: resets the current pointer to the head pointer
	//Requires: head pointer initialized
	//Returns: current pointer as head pointer
	void resetList();
	
	//Purpose: returns the title of the current position
	//Requires: current pointer initialized
	//Returns: the title of the current position
	string retrieveTitle();
	
	//Purpose: advances the position of the current pointer
	//Requires: current pointer initialized
	//Returns: current point at next position
	void advancePosition();


	//Purpose: checks to see if the current pointer is at the end
	//Requires: current pointer initialized
	//Returns: true or false
	bool atEnd();

	//Purpose: finds the position of where a title should be inserted
	//Requires: opened output stream, book title to find its place
	//Returns: output stream with where the book should be inserted appended to it
	void findPosition(ofstream &outfile, string bookTitle);

private:

	BookNode * head;
	BookNode * current;
	BookNode * tail;
	int length;
};

