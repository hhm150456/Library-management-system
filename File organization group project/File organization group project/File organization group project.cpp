#include <iostream>
#include <fstream>
#include <string>
#include "book.h"
#include "Library_system.h"

using namespace std;

int main()
{
	Library_system Library_Management_System;
	bool repeat = 1;

	while (repeat)
	{
		system("ClS");
		cout << endl;
		cout << endl;
		cout << "\t\t\t\t\t\tLibrary Management System" << endl;
		cout << endl;
		cout << "\t\t\t\t\t\t  1. Input new book." << endl;
		cout << "\t\t\t\t\t\t  2. Update existing book." << endl;
		cout << "\t\t\t\t\t\t  3. Delete book." << endl;
		cout << "\t\t\t\t\t\t  4. Search for book." << endl;
		cout << "\t\t\t\t\t\t  5. Display all avaliable books." << endl;
		cout << "\t\t\t\t\t\t  6. Display total number of available books." << endl;
		cout << "\t\t\t\t\t\t  7. Display first 5 books in system." << endl << endl;
		cout << "\t\t\t\t\t\t     Choose your operation: " << endl;
		int Choice = Library_Management_System.choose_operation();
		book Book;
		if (Choice == 1)
		{
			system("CLS");
			Book.get_book();
			Book.add_book();
			Book.add_index();
		}
		else if (Choice == 2)
		{
			system("CLS");
			book n_book;
			n_book.get_book();

		}
		else if (Choice == 3)
		{
			system("CLS");
			string name;
			cout << "Enter the name of the record you want to delete: " << endl;
			cin.ignore(1, '\n');
			getline(cin, name);
			Book.delete_book_name(name);
			cout << "Book deleted" << endl;
		}
		else if (Choice == 4)
		{
			system("CLS");
			string name;
			cout << "Enter the name of the record you are searching for: " << endl;
			cin.ignore(1, '\n');
			getline(cin, name);
			int no_of_matches = Library_Management_System.search_name(name);
			if (no_of_matches > 1)
			{
				cout << "Enter the id of the record you are searching for: " << endl;
				string id;
				getline(cin, id);
				Library_Management_System.search_id(id);
			}
		}
		else if (Choice == 5)
		{
			system("CLS");
			Library_Management_System.display_books();
		}
		else if (Choice == 6)
		{
			system("CLS");
			cout << endl << endl;
			cout << "\t\tTotal number of books in the library: " << Library_Management_System.number_of_books() << endl;;
		}
		else
		{
			system("CLS");
			Library_Management_System.display_top_5();
		}
		char answer;
		cout << "\t\t\t\t\t\t     Another operation? (y/n) " << endl;
		cin >> answer;
		if ((answer == 'y') || (answer == 'Y'))
		{
			continue;
		}
		else if ((answer == 'n') || (answer == 'N'))
		{
			repeat = 0;
			cout << "\t\t\t\t\t\t   Closing..." << endl;
			return 0;
		}
		else
		{
			cout << "\t\t\t\t\t\t   Invalid! Closing..." << endl;
			return 0;
		}
	}
}