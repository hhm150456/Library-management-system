#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Library_system.h"

using namespace std;

class book {
private:
	string Title;
	int Number_of_times_borrowed;
	int Year_of_publishing;
	int Edition;
	string Author;
	string Genre;
	string Printing_house;
	int Number_of_pages;
	string Book_index;
	int record_offset;
public:
	void get_book()
	{
		cout << "\t\t\tPlease enter book info" << endl << endl;
		cin.ignore(1, '\n');
		cout << "Enter book title: " << endl;
		getline(cin, Title);
		cout << "Enter book author: " << endl;
		getline(cin, Author);
		cout << "Enter book genre: " << endl;
		getline(cin, Genre);
		cout << "Enter book edition: " << endl;
		cin >> Edition;
		cout << "Enter book number of pages: " << endl;
		cin >> Number_of_pages;
		cin.ignore(1, '\n');
		cout << "Enter book printing house: " << endl;
		getline(cin, Printing_house);
		cout << "Enter book year of publishing: " << endl;
		cin >> Year_of_publishing;
		cout << "Enter book number of times borrowed: " << endl;
		cin >> Number_of_times_borrowed;
		cout << "Enter book ID" << endl;
		cin >> Book_index;
		cout << "Do you want to add another book? (Y/N)" << endl;
		char ans;
		cin >> ans;
		if ((ans == 'Y') || (ans == 'y'))
		{
			get_book();
		}
		else if ((ans == 'n') || (ans == 'N'))
		{
			return;
		}
		else
		{
			cerr << "Error. Closing...." << endl;
			return;
		}

	}

	void add_book()
	{
		fstream books;
		books.open("books.txt", ios::app);
		record_offset = books.tellp();
		books << Title << "|";
		books << Author << "|";
		books << Genre << "|";
		books << Edition << "|";
		books << Number_of_pages << "|";
		books << Printing_house << "|";
		books << Year_of_publishing << "|";
		books << Number_of_times_borrowed << "|";
		books << "$";
		books.close();
	}

	void add_index()
	{
		fstream index;
		index.open("index.txt", ios::app);
		index << Book_index << "|";
		index << record_offset << "|";
		index << "$";
		index.close();
	}

	int book_record_size() {
		int size = sizeof(Book_index) + sizeof(Number_of_pages) + sizeof(Printing_house) + sizeof(Number_of_times_borrowed) +
			sizeof(Title) + sizeof(Author) + sizeof(Edition) + sizeof(Year_of_publishing) + sizeof(Genre);
		return size;
	}

	void delete_book(book o)
	{

	}

	void update_book_id(book o, string id)
	{
		Library_system l;
		fstream books("books.txt", ios::in | ios::binary);
		fstream index("index.txt", ios::in | ios::binary);
		if (!books.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		if (!index.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		short update_offset = l.search_id(id);
		if (book_record_size() > o.book_record_size())
		{
			delete_book(o);
			add_book();
			add_index();
		}
		else
		{
			books.seekp(update_offset, ios::beg);
			books << Title << "|";
			books << Author << "|";
			books << Genre << "|";
			books << Edition << "|";
			books << Number_of_pages << "|";
			books << Printing_house << "|";
			books << Year_of_publishing << "|";
			books << Number_of_times_borrowed << "|";
		}
	}

};
