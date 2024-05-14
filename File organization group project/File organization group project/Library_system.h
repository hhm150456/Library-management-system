#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "book.h"
using namespace std;
class Library_system {
private:
	int Choice;
	char recordDelimiter = '$';
	char fieldDelimiter = '|';
	char deleted_book = '*';
public:
	int choose_operation()
	{
		cin >> Choice;
		if ((Choice > 8) || (Choice < 1))
		{
			cout << "\t\t\t\t\t\t     Invalid! Please choose another operation." << endl;
			choose_operation();
		}
		return Choice;
	}

	void display_books()
	{
		char flag;
		ifstream books("books.txt");
		ifstream index("index.txt");
		string record;
		string field;
		books.seekg(0, ios::beg);
		int no = number_of_books();
		if (books.is_open())
		{
			short counter = 1;
			while (counter <= no)
			{
				books.seekg(0, ios::cur);
				books.read((char*)&flag, 1);
				if (flag == deleted_book) {
					getline(books, record, recordDelimiter);
					getline(index, record, recordDelimiter);
					continue;
				}
				else {
					cout << endl << endl;
					books.seekg(-1, ios::cur);
					getline(index, field, fieldDelimiter);
					cout << "\t\t\t\t\t\t   ID: " << field << endl;
					getline(index, record, recordDelimiter);
					getline(books, field, fieldDelimiter);
					cout << "\t\t\t\t\t\t   Title: " << field << endl;
					getline(books, field, fieldDelimiter);
					cout << "\t\t\t\t\t\t   Author: " << field << endl;
					getline(books, field, fieldDelimiter);
					cout << "\t\t\t\t\t\t   Genre: " << field << endl;
					getline(books, field, fieldDelimiter);
					cout << "\t\t\t\t\t\t   Edition: " << field << endl;
					getline(books, field, fieldDelimiter);
					cout << "\t\t\t\t\t\t   Number of pages: " << field << endl;
					getline(books, field, fieldDelimiter);
					cout << "\t\t\t\t\t\t   Printing house: " << field << endl;
					getline(books, field, fieldDelimiter);
					cout << "\t\t\t\t\t\t   Year of publishing: " << field << endl;
					getline(books, field, fieldDelimiter);
					cout << "\t\t\t\t\t\t   Number of times borrowed: " << field << endl;
					getline(books, record, recordDelimiter);
					++counter;
				}
			}
			books.close();
		}
	}

	void display_top_5()
	{
		int no = number_of_books();
		if (no >= 5)
		{
			no = 5;
			char flag;
			fstream books("books.txt", ios::in | ios::binary);
			fstream index("index.txt", ios::in | ios::binary);
			string record;
			string field;
			books.seekg(0, ios::beg);
			if (books.is_open())
			{
				short counter = 1;
				while (counter <= no)
				{
					books.seekg(0, ios::cur);
					books.read((char*)&flag, 1);
					if (flag == deleted_book) {
						getline(books, record, recordDelimiter);
						getline(index, record, recordDelimiter);
						continue;
					}
					else {
						books.seekg(-1, ios::cur);
						cout << endl << endl;
						getline(index, field, fieldDelimiter);
						cout << "\t\t\t\t\t\t   ID: " << field << endl;
						getline(index, record, recordDelimiter);
						getline(books, field, fieldDelimiter);
						cout << "\t\t\t\t\t\t   Title: " << field << endl;
						getline(books, field, fieldDelimiter);
						cout << "\t\t\t\t\t\t   Author: " << field << endl;
						getline(books, field, fieldDelimiter);
						cout << "\t\t\t\t\t\t   Genre: " << field << endl;
						getline(books, field, fieldDelimiter);
						cout << "\t\t\t\t\t\t   Edition: " << field << endl;
						getline(books, field, fieldDelimiter);
						cout << "\t\t\t\t\t\t   Number of pages: " << field << endl;
						getline(books, field, fieldDelimiter);
						cout << "\t\t\t\t\t\t   Printing house: " << field << endl;
						getline(books, field, fieldDelimiter);
						cout << "\t\t\t\t\t\t   Year of publishing: " << field << endl;
						getline(books, field, fieldDelimiter);
						cout << "\t\t\t\t\t\t   Number of times borrowed: " << field << endl;
						getline(books, record, recordDelimiter);
						++counter;
					}
				}
				books.close();
			}
		}
		else
		{
			display_books();
		}
	}

	int number_of_books() {
		int counter = 0;
		fstream books("books.txt", ios::in);
		if (!books.is_open()) {
			return 0;
		}
		char flag;
		string record;
		books.seekg(0, ios::beg);
		books.read((char*)&flag, 1);
		if (flag == deleted_book)
		{
			getline(books, record, recordDelimiter);
		}
		while (getline(books, record, recordDelimiter)) {
			books.read((char*)&flag, 1);
			if (flag == deleted_book) {
				books.seekg(-1, ios::cur);
				continue;
			}
			else {
				++counter;
			}

		}

		books.close();
		return counter;
	}

	short search_id(string id) 
	{
		fstream books("books.txt", ios::in | ios::binary);
		fstream index("index.txt", ios::in | ios::binary);
		if (!books.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		if (!index.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		int counter = 0;
		string book_id;
		string loc;
		short offset = 0;
		string record;
		string field;
		char flag;
		int no = number_of_books();
		while (counter < no)
		{
			index.read((char*)&flag, 1);
			if (flag == deleted_book)
			{
				getline(index, record, recordDelimiter);
				continue;
			}
			index.seekg(-1, ios::cur);
			getline(index, book_id, fieldDelimiter);
			if (id == book_id)
			{
				getline(index, loc, fieldDelimiter);
				offset = stoi(loc);
				books.seekg(offset, ios::beg);
				cout << "\t\t\t\t\t\t   ID: " << book_id << endl;
				getline(index, record, recordDelimiter);
				getline(books, field, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Title: " << field << endl;
				getline(books, field, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Author: " << field << endl;
				getline(books, field, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Genre: " << field << endl;
				getline(books, field, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Edition: " << field << endl;
				getline(books, field, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Number of pages: " << field << endl;
				getline(books, field, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Printing house: " << field << endl;
				getline(books, field, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Year of publishing: " << field << endl;
				getline(books, field, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Number of times borrowed: " << field << endl <<endl << endl;
				getline(books, record, recordDelimiter);
				return offset;
			}
			else
			{
				getline(index, record, recordDelimiter);
			}
		}
		if (offset == 0)
		{
			return 0;
		}
		++counter;
	}

	int search_name(string name)
	{
		fstream books("books.txt", ios::in | ios::binary);
		fstream index("index.txt", ios::in | ios::binary);
		if (!books.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		if (!index.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		books.seekg(0);
		int counter = 0;
		string title;
		int matches = 0;
		char flag;
		string id;
		string record;
		int no = number_of_books();
		while (counter < no)
		{
			getline(books, title, fieldDelimiter);
			if (name == title)
			{
				books.read((char*)&flag, 1);
				if (flag == deleted_book)
				{
					getline(books, record, recordDelimiter);
					continue;
				}
				books.seekg(-1, ios::cur);
				index.seekg(0);
				int j = 0;
				while (j < counter)
				{
					index.read((char*)&flag, 1);
					if (flag != deleted_book)
					{
						++j;
					}
					getline(index, record, recordDelimiter);
				}
				getline(index, id, fieldDelimiter);
				cout << "\t\t\t\t\t\t   ID: " << id << endl;
				cout << "\t\t\t\t\t\t   Title: " << title << endl;
				getline(books, title, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Author: " << title << endl;
				getline(books, title, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Genre: " << title << endl;
				getline(books, title, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Edition: " << title << endl;
				getline(books, title, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Number of pages: " << title << endl;
				getline(books, title, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Printing house: " << title << endl;
				getline(books, title, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Year of publishing: " << title << endl;
				getline(books, title, fieldDelimiter);
				cout << "\t\t\t\t\t\t   Number of times borrowed: " << title << endl <<endl <<endl;
				getline(books, record, recordDelimiter);
				++matches;
			}
			else
			{
				getline(books, record, recordDelimiter);
			}
			++counter;
		}
		return matches;
	}
};
