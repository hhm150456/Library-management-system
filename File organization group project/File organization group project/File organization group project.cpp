#include <iostream>
#include <fstream>
#include <string>

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
		cout << "\t\t\tPlease enter book info" << endl <<endl;
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
		add_book();
		add_index();
	}

	void add_book()
	{
		fstream books;
		books.open("books.txt", ios::app);
		books << Title << "|";
		books << Author << "|";
		books << Genre << "|";
		books << Edition << "|";
		books << Number_of_pages << "|";
		books << Printing_house << "|";
		books << Year_of_publishing << "|";
		books << Number_of_times_borrowed << "|";
		books << "$";
		record_offset = books.tellp();
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
};

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
		while (getline(books, record,recordDelimiter )) {
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
};

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
		book book;
		if (Choice == 1)
		{
			system("CLS");
			book.get_book();
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
			
		}
		else if (Choice == 4)
		{
			system("CLS");
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