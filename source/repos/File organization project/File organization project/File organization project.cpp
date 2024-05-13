#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int Choice;
const char Delimiter = '|';
short ID;
struct Student
{
	int ID, Age, Marks;
	char Name[30];
};

void Delete_student_records(short id) {
		fstream file("students_data.txt", ios::in|ios::out|ios::binary);

		if (!file.is_open()) {
			cerr << "Error opening file for reading." << endl;
			return ;
		}

		file.seekg(ios::beg);

		char deleted_marker = '*';
		char flag;
		int c = 0;
		string line;
		while (id != 0 && getline(file, line, Delimiter))
		{
			file.read((char*)&flag, 1);
			if (c == id)
				break;
			if (flag != deleted_marker) {
					c++;
			}
		}
		if (id != 0)
			file.seekp(-1, ios::cur);
		file << deleted_marker;
		file.close(); 
	}

void Update_student_records(short id)
{
	fstream file("students_data.txt", ios::in | ios::out);
	if (!file.is_open()) {
		return ;
	}
	fstream index("index.txt", ios::in | ios::out);
	if (!file.is_open()) {
		return;
	}
	fstream size("size.txt", ios::in | ios::out);
	if (!file.is_open()) {
		return;
	}
	char i;
	Student Student_info;
	cout << "Enter new student information:" << endl;
	cout << "\t\t\t\t\t\t   ID: ";
	cin >> Student_info.ID;
	cout << "\t\t\t\t\t\t   Name: ";
	cin >> Student_info.Name;
	cout << "\t\t\t\t\t\t   Age: ";
	cin >> Student_info.Age;
	cout << "\t\t\t\t\t\t   Marks: ";
	cin >> Student_info.Marks;
	string temp_ID, temp_marks, temp_age;
	temp_ID = to_string(Student_info.ID);
	temp_age = to_string(Student_info.Age);
	temp_marks = to_string(Student_info.Marks);

		Delete_student_records(id);
		file.seekp(0, ios::end);
		file << temp_ID.length() << Student_info.ID;
		file << strlen(Student_info.Name) << Student_info.Name;
		file << temp_age.length() << Student_info.Age << temp_marks.length() << Student_info.Marks;

}

void choose_operation()
{
	cin >> Choice;
	if ((Choice > 5) || (Choice < 1))
	{
		cout << "\t\t\t\t\t\t     Invalid! Please choose another operation." << endl;
		choose_operation();
	}
}

int getNumberOfStudents()
{
	fstream file("students_data.txt", ios::in);
	if (!file.is_open()) {
		return 0;
	}
	char deleted_marker = '*';
	char flag;
	int Number_of_students = 0;
	string line;
	file.seekg(0,ios::beg); 
	while (getline(file, line, Delimiter)) {
		file.read((char*)&flag, 1);
		if (flag == deleted_marker) {
			file.seekg(-1, ios::cur);
			continue;
		}
		else {
			++Number_of_students;
		}
		
	}

	file.close();
	return Number_of_students;
}

void Input_Student_Data() {
	fstream file("students_data.txt" ,ios::in|ios::app); 
	if (!file.is_open()) {
		cerr << "Error opening file for writing." << endl;
		return;
	}
	fstream index("index.txt", ios::in | ios::app);
	if (!file.is_open()) {
		return;
	}
	fstream size("size.txt", ios::in | ios::app);
	if (!file.is_open()) {
		return;
	}
	file.seekg(0, ios::cur);

	if (file.tellp() == file.tellg())
	{
		index << 0;
	}
	Student Student_info;
	cout << "Enter student information:" << endl;
	cout << "\t\t\t\t\t\t   ID: " ;
	cin >> Student_info.ID;
	cout << "\t\t\t\t\t\t   Name: ";
	cin >> Student_info.Name;
	cout << "\t\t\t\t\t\t   Age: " ;
	cin >> Student_info.Age;
	cout << "\t\t\t\t\t\t   Marks: " ;
	cin >> Student_info.Marks;
	string temp_ID, temp_marks, temp_age;
	temp_ID = to_string(Student_info.ID);
	temp_age = to_string(Student_info.Age);
	temp_marks = to_string(Student_info.Marks);
	short new_record_size = temp_ID.length() + strlen(Student_info.Name) + temp_age.length() + temp_marks.length();
	file << temp_ID.length() << Student_info.ID;
	file << strlen(Student_info.Name) << Student_info.Name;
	file << temp_age.length() << Student_info.Age << temp_marks.length() << Student_info.Marks;
	file << '|';
	size << new_record_size;
	char answer;
	file.seekp(0, ios::end);
	index << file.tellp();
	cout << "\t\t\t\t\t\t   Do you want to add another record? (y/n)" << endl;
	cin >> answer;
	if((answer == 'y')||(answer=='Y'))
	{ 
		Input_Student_Data();
	}
	else if ((answer == 'n') || (answer == 'N'))
	{
		cout << "\t\t\t\t\t\t   Closing..." << endl;
	}
	else
	{
		cout << "\t\t\t\t\t\t   Invalid! Closing..." << endl;
	}
	file.close();
}

void display_records()
{
	char flag;
	char deleted_marker = '*';
	ifstream Student_records;
	Student_records.open("Students_data.txt");
	char id[10], age[4], marks[4];
	char name[30 + 1];
	char i;
	string line;
	Student_records.seekg(0, ios::beg);
	int no = getNumberOfStudents();
	if (Student_records.is_open())
	{
		short counter = 1;
		while (counter <= no)
		{
			Student_records.seekg(0, ios::cur);
			Student_records.read((char*)&flag,1);
			if (flag == '*') {
				getline(Student_records, line, Delimiter);
				continue;
			}
			else {
				Student_records.seekg(-1, ios::cur);
				Student_records.read((char*)&i, 1);
				int index = i - '0';
				Student_records.get(id, index + 1);
				Student_records.read((char*)&i, 1);
				index = i - '0';
				Student_records.get(name, index + 1);
				Student_records.read((char*)&i, 1);
				index = i - '0';
				Student_records.get(age, index + 1);
				Student_records.read((char*)&i, 1);
				index = i - '0';
				Student_records.get(marks, index + 1);
				Student_records.seekg(1, ios::cur);
				cout << "\t\t\t\t\t\t   ID: " << id << endl;
				cout << "\t\t\t\t\t\t   Name: " << name << endl;
				cout << "\t\t\t\t\t\t   Age: " << age << endl;
				cout << "\t\t\t\t\t\t   Marks: " << marks << endl;
				++counter;
			}
		}
		Student_records.close();
	}
}

int main()
{
	bool repeat = 1;
	while (repeat)
	{
		system("ClS");
		cout << endl;
		cout << endl;
		cout << "\t\t\t\t\t\t\tStudent files" << endl;
		cout << endl;
		cout << "\t\t\t\t\t\t  1. Input student record." << endl;
		cout << "\t\t\t\t\t\t  2. Update student record." << endl;
		cout << "\t\t\t\t\t\t  3. Delete student record." << endl;
		cout << "\t\t\t\t\t\t  4. Display student records." << endl;
		cout << "\t\t\t\t\t\t  5. Display total number of student records." << endl << endl;
		cout << "\t\t\t\t\t\t     Choose your operation: " << endl;
		choose_operation();
		if (Choice == 1)
		{
			Input_Student_Data();
		}
		else if (Choice == 2)
		{
			system("CLS");
			display_records();
			cout << "Enter the number of the record you want to update" << endl;
			cin >> ID;
			--ID;
			Update_student_records(ID);
		}
		else if (Choice == 3)
		{
			system("CLS");
			display_records();
			cout << "Enter the ID of the record you want to delete" << endl;
			cin >> ID;
			--ID;
			Delete_student_records(ID);
		}
		else if (Choice == 4)
		{
			system("CLS");
			display_records();
		}
		else
		{
			system("CLS");
			cout << "Total number of students: " << getNumberOfStudents() <<endl;
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
		}
		else
		{
			cout << "\t\t\t\t\t\t   Invalid! Closing..." << endl;
		}
	}
}