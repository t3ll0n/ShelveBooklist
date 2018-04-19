#include "BookList.h"
#include <iostream>
#include <fstream>
using namespace std;

BookList::BookList()
{
	head = new BookNode;
	tail = new BookNode;
	head->next = tail;
	tail->next = NULL;
	length = 0;
}


BookList::~BookList()
{
	BookNode * garbage;
	if (current != head)
	{
		resetList();
	}

	while (!atEnd())
	{
		garbage = current;
		advancePosition();
		delete garbage;
	}
}

bool BookList::isEmpty()
{
	if (head->next == tail)
		return true;
	else
		return false;
}

void BookList::insertTitle(string bookTitle)
{
	{
		bool inserted = false;

		if (current != head)
		{
			resetList();
		}

		while (!inserted)
		{
			
			if (isEmpty())
			{
				head->next = new BookNode(bookTitle, head->next);
				inserted = true;
				length++;
			}
			else if ((current->title < bookTitle && current->next == tail) || (current->title < bookTitle && current->next->title > bookTitle) || (atEnd()))
			{
				current->next = new BookNode(bookTitle, current->next);
				inserted = true;
				length++;
			}
			else if (current->title > bookTitle)
			{
				head->next = new BookNode(bookTitle, head->next);
				inserted = true;
				length++;
			}
			else 
			{
				advancePosition();
			}

		}
	}
}


void BookList::removeTitle(string bookTitle)
{
	bool found = false;
	BookNode * removeItem;
	BookNode * trailItem;
	trailItem = NULL;
	removeItem = NULL;

	if (current != head)
	{
		resetList();
	}

	while (!found && !atEnd())
	{
		if (current->title == bookTitle)
		{
			found = true;
			removeItem = current;
		}
		else
		{
			trailItem = current;
			advancePosition();
		}
	}
	if (found == true)
	{
		current = current->next;
		trailItem->next = current;
		delete removeItem;
		length--;
	}
}

int BookList::provideLength()
{
	return length;
}

BookNode * BookList::provideHead()
{
	return head;
}

BookNode *BookList::provideCurrent()
{
	return current;
}

void BookList::resetList()
{
	current = head;
}

string BookList::retrieveTitle()
{
	string title;
	if (current->title == "")
	{
		advancePosition();
	}

	title = current->title;

	return title;
}


void BookList::advancePosition()
{
	if (!atEnd())
	{
		current = current->next;
	}
}

bool BookList::atEnd()
{
	if (current == tail)
	{
		return true;
	}
	else
		return false;
}

void BookList::findPosition(ofstream &outfile, string bookTitle)
{
	{
		bool found = false;

		if (current != head)
		{
			resetList();
		}

		while (!found && current->next != tail)
		{

			if (current == head && head->next->title == bookTitle)
			{
				found = true;
				outfile << "Put " << '"' << bookTitle << '"' << " first" << endl;
			}
			else if (current->next->title == bookTitle)
			{
				found = true;
				outfile << "Put " << '"' << bookTitle << '"' << " after " << '"' << current->title << '"' <<endl;
			}
			else
			{
				advancePosition();
			}

		}
	}
}

