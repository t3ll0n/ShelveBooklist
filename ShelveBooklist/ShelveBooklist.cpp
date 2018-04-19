//-------------------------------------------------------------------------------------------------------
//
// Name: Smith, Tellon
//
// Course: CS 1063 - Data Structures & ADT, Spring 15, Dr. Stringfellow
//
// Program Assignment : #5B
//
// Due Date: Friday, Apr. 24, 2015, 9AM
//
// Purpose: This program uses linked lists to keeps track of books that are shelved, and returned and
//          tells the librarian where the returned books should be inserted on the shelve
//
//-------------------------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include "BookList.h"

using namespace std;

//Purpose: open streams
//Requires: an input stream and output stream
//Returns: an opened input stream and an opened output stream
void openFiles(ifstream & infile, ofstream & outfile);

//Purpose: gets the title of a books from a file
//Requires: an opened infile stream
//Returns: the title of the book
string getTitle(ifstream& infile);

//Purpose: prints the list of books in a linked list
//Requires: an opened output stream, the linked list 
//Returns: output stream with the book list appended to it. linked list unchanged
void printList(ofstream& outfile, BookList& Booklist);

//Purpose: processes the different commands read in the infile 
//Requires: an opened intput stream, an opened output stream, shelve and returned books llinked list 
//Returns: output stream with the processed commands appended to it.
void processCommands(ifstream& infile, ofstream& outfile, BookList& shelvedBooks, BookList& returnedBooks);

//Purpose: prints heading info to outfile
//Requires: an opened output stream
//Returns: output stream with the heading appended to it
void printHeadings(ofstream & outfile);

//Purpose: prints welcome message
//Requires: an opened output stream
//Returns: output stream with the welcome message appended to it
void printWelcomeMessage(ofstream & outfile);

//Purpose: prints exit message
//Requires: an opened output stream 
//Returns: output stream with the exit message appended to it
void printExitMessage(ofstream & outfile);

string extractBookTitle(string& str);
int main()
{
	ifstream infile;
	ofstream outfile;

	string bookTitle;
	BookList shelvedBooks;
	BookList returnedBooks;

	openFiles(infile, outfile);
	
	printHeadings(outfile);

	printWelcomeMessage(outfile);

	//reads in initial list of shelved books
	if (infile)
	{
		bookTitle = getTitle(infile);
		while (bookTitle != "END")
		{
			shelvedBooks.insertTitle(bookTitle);
			bookTitle = getTitle(infile);
		}		
	}//end of if

	processCommands(infile, outfile, shelvedBooks, returnedBooks);

	printExitMessage(outfile);

	system ("pause");
	return 0;


}

void openFiles(ifstream & infile, ofstream & outfile)
{
	char inFileName[40];
	char outFileName[40];

	//open input stream
	cout << "\nPlease enter the input file name: ";
	cin >> inFileName;
	infile.open(inFileName);

	//display error message if specified cannot be opened
	if (!infile)
	{
		cout << "\nERROR: cannot open the specified file. please run the program again." << endl;
		system("pause");
		exit(1);
	}

	//open output stream
	cout << "Enter the output file name: ";
	cin >> outFileName;
	outfile.open(outFileName);
}

string getTitle(ifstream& infile)
{
	string s, junk;
	char ch;

	//read the “, then read the string up to the second “, then read and ignore the rest of the line
	infile >> ch;
	if (!infile.eof() && (ch == '"'))
	{
		getline(infile, s, '"');
		getline(infile, junk);
	}

	if (ch != '"')
	{
		getline(infile, junk);
		return "END";
	}
	return s;
}


void printList(ofstream& outfile, BookList& Booklist)
{
	//reset current
	Booklist.resetList();
	string title;

	outfile << "\nSHELF LIST:" << endl;
	while (!Booklist.atEnd())
	{
		title = Booklist.retrieveTitle();
		outfile << '"' << title << '"' << endl;
		//advances current to the next title
		Booklist.advancePosition();
	}

	if (Booklist.atEnd())
	{
		outfile << "\n";
	}
}

void processCommands(ifstream& infile, ofstream& outfile, BookList& shelvedBooks, BookList& returnedBooks)
{
	string command;
	string title;
	char ch;
	int pos=0;

	
	while (infile >> ch)
	{
		if (ch == 'P' || ch == 'S' || ch == 'E')
		{
			//get position of current cursor in the infile stream, move the position backwards by 
			//one character and then reads the entire line
			pos = infile.tellg();
			infile.seekg(pos - 1);
			getline(infile, command);
			if (command == "PRINT")
			{
				printList(outfile, shelvedBooks);
			}
			else if (command == "SHELVE")
			{
				returnedBooks.resetList();
				if (returnedBooks.isEmpty())
				{
					outfile << "There are no books to shelve" << endl;
				}
				while (!returnedBooks.isEmpty() && !returnedBooks.atEnd())
				{
					title = returnedBooks.retrieveTitle();
					returnedBooks.removeTitle(title);
					shelvedBooks.insertTitle(title);
					shelvedBooks.findPosition(outfile, title);
				}
			}
			else if (command == "END")
			{
				outfile << "END" << endl;
			}
		}//end of main if
		else
		{
			pos = infile.tellg();
			infile.seekg(pos - 1);
			getline(infile, command, '"');
			getline(infile, title, '"');
			if (command == "BORROW ")
			{
				shelvedBooks.removeTitle(title);
			}
			else if (command == "RETURN ")
			{
				returnedBooks.insertTitle(title);
			}
		}//end main else
	}



}

void printHeadings(ofstream & outfile)
{
	outfile << "\nName: Tellon Smith" << endl;
	outfile << "Course: CS 1063 - Data Structures & ADT, Spring 15, Dr. Stringfellow" << endl;
	outfile << "Program Assignment: #5B" << endl;
	outfile << "Due Date: Friday, Apr. 24, 2015, 9AM" << endl;
	outfile << "Purpose: This program uses linked lists to keeps track of books that are shelved," << endl;
	outfile << "          and returned and tells the librarian where the returned books should be" << endl;
	outfile << "          inserted on the shelve" << endl;
}

void printWelcomeMessage(ofstream & outfile)
{
	outfile << "\nWelcome to the Shelve Booklist Program!" << endl;
}

void printExitMessage(ofstream & outfile)
{
	outfile << "\nThank you for using the Shelve Booklist Program... Goodbye!" << endl;
}
