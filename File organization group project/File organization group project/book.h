#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
	book get_book_from_file(string id)
	{
		book r;
		fstream books("books.txt", ios::in);
		int counter = 0;
		books.seekg(0);
		string b_id;
		string record;
		while (!books.eof())
		{
			getline(books, b_id, '|');
			if (id == b_id)
			{
				int x = 1 + b_id.length();
				r.record_offset = books.tellg();
				books.seekg(-x, ios::cur);
				getline(books, r.Book_index, '|');
				getline(books, r.Title, '|');
				getline(books, r.Author, '|');
				getline(books, r.Genre, '|');
				string temp_e;
				string temp_n;
				string temp_y;
				string temp_b;
				getline(books, temp_e, '|');
				getline(books, temp_n, '|');
				getline(books, Printing_house, '|');
				getline(books, temp_y, '|');
				getline(books, temp_b, '|');
				r.Edition = stoi(temp_e);
				r.Number_of_pages = stoi(temp_n);
				r.Year_of_publishing = stoi(temp_y);
				r.Number_of_times_borrowed = stoi(temp_b);
				break;
			}
			else
			{
				getline(books, record, '|');
				++counter;
			}
		}
		return r;
	}

	book get_book_from_file_name(string name)
	{
		book r;
		fstream books("books.txt", ios::in);
		int n = l.number_of_books();
		int counter = 0;
		books.seekg(0);
		string b_id;
		string record;
		string title;

		while (counter < n)
		{
			getline(books, b_id, '|');
			getline(books, title, '|');
			if (name == title)
			{
				int x = 2 + b_id.length()+title.length();
				books.seekg(-x, ios::cur);
				getline(books, r.Book_index, '|');
				getline(books, r.Title, '|');
				getline(books, r.Author, '|');
				getline(books, r.Genre, '|');
				string temp_e;
				string temp_n;
				string temp_y;
				string temp_b;
				getline(books, temp_e, '|');
				getline(books, temp_n, '|');
				getline(books, Printing_house, '|');
				getline(books, temp_y, '|');
				getline(books, temp_b, '|');
				r.record_offset = books.tellg();
				r.Edition = stoi(temp_e);
				r.Number_of_pages = stoi(temp_n);
				r.Year_of_publishing = stoi(temp_y);
				r.Number_of_times_borrowed = stoi(temp_b);
				break;
			}
			else
			{
				getline(books, record, '|');
			}
		}
		return r;
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
		index << '$';
		index.close();
	}

	void delete_book_id(string id)
	{
		int offset = l.search_id(id);
		int size=0;
		book d = get_book_from_file(id);
		string field;
		fstream books("books.txt",ios::in |ios::out );
		fstream index("index.txt", ios::in | ios::out);
		if (!books.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		if (!index.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		index.seekg(0);
		books.seekp(offset);
		books.put('*');
		string b_id;
		while (getline(index, b_id, '$'))
		{
			if (id == b_id)
			{
				break;
			}
		}
		int x = 1 + b_id.length();
		index.seekp(-x,ios::cur);
		index.put('*');
		header(d.get_record_size(),l.search_id(id));
		index.close();
		books.close();
	}

	short get_record_size()
	{
		string temp_e = to_string(Edition);
		string temp_n = to_string(Number_of_pages);
		string temp_y = to_string(Year_of_publishing);
		string temp_b = to_string(Number_of_times_borrowed);
		short x = temp_b.length() + temp_e.length() + Author.length() + temp_y.length() + temp_n.length() + Title.length() +
			Printing_house.length() + Genre.length() + Book_index.length();
		return x;
	}

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
					continue;
				}
				else
				{
					getline(books, move, '|');
					getline(books, field, '|');
					if (field == name)
					{
						book d = get_book_from_file(move);
						int x = field.length() + 2 + move.length();
						books.seekp(-x, ios::cur);
						books.put('*');
						string b_id;
						index.seekg(0);
						while (getline(index, b_id, '$'))
						{
							if (move == b_id)
							{
								break;
							}
						}
						 x = 1 + b_id.length();
						index.seekp(-x, ios::cur);
						index.put('*');
						header(d.get_record_size(),d.record_offset);
						break;
					}
				}
			} while (getline(books, record, '$'));
			index.close();
			books.close();
		}
	}

	void update_book_id(string id, book n)
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
		fstream avail("avail.txt", ios::in | ios::binary);
		if (!books.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		short update_offset = l.search_id(id);
		books.seekg(update_offset);
		delete_book_id(id);
		bool o = true;
		short size = -1;
		string record;
		while (o)
		{
			avail.read((char*)&size, sizeof(short));
			if (size >= n.get_record_size())
			{
				n.add_book();
				n.add_index();
				o = false;
				break;
			}
			else
			{
				getline(avail, record, '$');
				if (avail.eof())
				{
					break;
				}
			}
		}
		if (o == true)
		{
			n.add_book();
			n.add_index();
		}
		index.close();
		books.close();
	}

	short return_head()
	{
		fstream avail("avail.txt", ios::in | ios::binary);
		if (!avail.is_open()) {
			cerr << "Error opening file." << endl;
			return -1;
		}
		short head;
		avail.read((char*)&head, sizeof(short));
		 return head;
	}

	void header( short lastDeletedRecordSize, short offset) {
		fstream avail("avail.txt", ios::in | ios::app);
		if (!avail.is_open()) {
			cerr << "Error opening file."  << endl;
			return;
		}
		avail.seekg(0, ios::beg);
		stringstream file;
		file << avail.rdbuf();
		string Content = file.str();
		stringstream newContent;
		newContent << lastDeletedRecordSize << "|" << offset << "|" << "$" << Content;
		avail.seekp(0, ios::beg);
		avail << newContent.str();
		avail.close();
	}

	void update_book_name(string name, book n)
	{
		Library_system l;
		fstream books("books.txt", ios::in | ios::binary);
		fstream index("index.txt", ios::in | ios::binary);
		fstream avail("avail.txt", ios::in | ios::binary);
		if (!books.is_open()) {
			cerr << "Books are not currently available" << endl;
		}
		if (!index.is_open()) {
			cerr << "Books are not currently available" << endl;
		}if (!avail.is_open()) {
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
			update_book_id(id, n);
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
				avail.seekg(0, ios::beg);
				getline(books, p_id, '|');
				getline(books, title, '|');
				string record;
				if (name == title)
				{
					short size=-1;//=return_head(); 
					bool o = true;
					int x = title.length() + 2 + p_id.length();
					books.seekp(-x, ios::cur);
					delete_book_name(name);
					while (o)
					{
						avail.read((char*)&size, sizeof(short));
						if (size >= n.get_record_size())
						{
							
							n.add_book();
							n.add_index();
							o = false;
							break;
						}
						else
						{
							getline(avail, record, '$');
							if (avail.eof())
							{
								break;
							}
						}
					}
					if (o == true)
					{
						n.add_book();
						n.add_index();
					}
					break;
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
		avail.close();
	}
};
