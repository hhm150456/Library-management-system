#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Library_system.h"

using namespace std;

Library_system l;

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
	}

	void add_book()
	{
		fstream books;
		books.open("books.txt", ios::app);
		books.seekp(0, ios::end);
		record_offset = books.tellp();
		books << Book_index << "|";
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

	void delete_book_id(string id)
	{
		int offset = l.search_id(id);
		int size=0;
		string field;
		fstream books("books.txt", ios::out );
		fstream index("index.txt", ios::out);
		if (!books.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		if (!index.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		books.seekp(offset);
		books.put('*');
		
		//best_fit(size);
		index.close();
		books.close();
	}

	/*void best_fit(int size)
	{
		fstream avail("avail_list.txt", ios::out | ios::binary);
		string record;
		
	}*/

	void delete_book_name(string name)
	{
		fstream books("books.txt", ios::in| ios::out);
		if (!books.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		fstream index("index.txt", ios::in | ios::out);
		if (!index.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		int matches = l.search_name(name);
		char flag;
		index.seekp(0);
		string field, record, move, offset_1, offset_2;
		if (matches > 1)
		{
			cout << "Enter the id of the record you are searching for: " << endl;
			string id;
			getline(cin, id);
			delete_book_id(id);
		}
		else
		{
			do {
				books.read((char*)&flag, 1);
				books.seekg(-1, ios::cur);
				if (flag == '*')
				{
					getline(index, move, '$');
					continue;
				}
				else
				{
					getline(books, move, '|');
					getline(books, field, '|');
					if (field == name)
					{
						int x = field.length() + 2 + move.length();
						books.seekp(-x, ios::cur);
						books.put('*');
						index.put('*');
					}
					break;
				}
			} while (getline(books, record, '$') && getline(index, move, '$'));
			getline(index, offset_1, '|');
			getline(index, move, '$');
			getline(index, offset_2, '|');
			//best_fit(stoi(offset_2) - stoi(offset_1));
			index.close();
			books.close();
		}
	}

	void update_book_id(string id, book n, short header)
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
		books.seekg(update_offset);
		//delete file
		//compare n.size to header
		if ()
		index.close();
		books.close();
	}

	void update_book_name(string name, book n, short header)
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
		int matches = l.search_name(name);
		char flag;
		string record, p_id;
		if (matches > 1)
		{
			cout << "Enter the id of the record you want to update: " << endl;
			string id;
			getline(cin, id);
			update_book_id(id, n, header);
		}
		else
		{
			int no = l.number_of_books();
			int counter = 0;
			string title;
			while (counter < no)
			{
				books.read((char*)&flag, 1);
				if (flag == '*')
				{
					getline(books, record, '$');
					getline(index, record, '$');
					continue;
				}
				books.seekg(-1, ios::cur);
				getline(books, p_id, '|');
				getline(books, title, '|');
				if (name == title)
				{
					int x = title.length() + 2 + p_id.length();
					books.seekp(-x, ios::cur);
					n.add_book();

				}
				else
				{
					getline(index, record, '$');
					getline(books, record, '$');
				}
				++counter;
			}
		}
		index.close();
		books.close();
	}
};
