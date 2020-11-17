#include<iostream>
#include <stdlib.h>
#include<stdio.h>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Student
{
	string name;
	float score;

	Student *next;
}; typedef struct Student Student;

void insert_Node(int data_in, string name_in);
void Visit(Student *std, string label);
void swap(Student *a, Student *b);
void Delete(int percent_line, string buff[]);
void Search(Student *std, int percent_line, string buff[]);
void SORTASC(Student *top);
void SORTDES(Student *top);
void INSERT(int percent_line, string buff[]);

Student *top;
Student *bottom;

int count_list = 0;
bool same = false;
bool not_found = false;
bool found = false;

int main()
{
	string buff[100];
	string filename = "a3.txt";
	int count = 0;

	int pos = 0;
	int data;
	string name;
	string score;
	int intscore;

	int percent_line;

	bool out_flag = true;

	ifstream myfile(filename.c_str());

	if (myfile.is_open() == true)
	{
		while (getline(myfile, buff[count]))
		{
			cout << buff[count] << endl;
			count++;
		}
		myfile.close();
	}
	cout << endl;

	while (out_flag == true)
	{
		for (int line = 0; line < count; line++)
		{
			percent_line = line;

			if (buff[percent_line][0] == '%')
			{
				if (buff[percent_line] == "%INSERT")
				{
					INSERT(percent_line, buff);
				}
				else if (buff[percent_line] == "%VISIT")
				{
					Visit(top, "Visit My List");
				}
				else if (buff[percent_line] == "%SEARCH")
				{
					Search(top, percent_line, buff);
				}

				else if (buff[percent_line] == "%DELETE")
				{
					Delete(percent_line, buff);
				}
				else if (buff[percent_line] == "%SORTASC")
				{
					cout << "Sort Ascending Order" << endl;
					SORTASC(top);
				}
				else if (buff[percent_line] == "%SORTDES")
				{
					cout << "Sort Descending Order" << endl;
					SORTDES(top);
				}
				else if (buff[percent_line] == "%END")
				{
					out_flag = false;
				}

			}

		}
	}

	system("PAUSE");
	return 0;
}

void insert_Node(int data_in, string name_in)
{
	Student *temp = new Student;
	temp->name = name_in;
	temp->score = data_in;

	count_list++;
	if (top== NULL)
	{
		top = bottom = temp;
		bottom->next = NULL;

	}
	else
	{
		temp->next = NULL;
		bottom->next = temp;
		bottom = temp;
	}

}

void INSERT(int percent_line, string buff[])
{

	int data;
	int pos=0;
	string name;
	string score;
	int intscore;
	Student *temp = top;
	Student *temp2 = top;
	data = percent_line + 1;

	while (buff[data][0] != '%')
	{
		while (buff[data][pos] != 32)
		{
			pos++;
		}
		name = buff[data].substr(0, pos);
		score = buff[data].substr(pos + 1, buff[data].length() - (pos + 1));
		intscore = atoi(score.c_str());


		for (temp = top; temp != NULL; temp = temp->next)
		{
			if (name == temp->name)
			{
				temp2 = temp;
				same = true;
			}
		}
		if (same == true)
		{
			temp2->score = intscore;
		}
		else
		{
			insert_Node(intscore, name);
		}
		same = false;
		pos = 0;
		data++;
	}
}

void Delete(int percent_line, string buff[])
{
	int data;
	Student *temp;
	Student *temp2= top;
	Student *prev = top;
	Student *del = top;
	data = percent_line + 1;
	temp = top;

	while (buff[data][0] != '%')
	{
		while (temp != NULL && buff[data] != temp->name)
		{
			prev = temp;
			temp = temp->next;
		}

		for (temp = top; temp != NULL; temp = temp->next)
		{
			if (buff[data] == temp->name)
			{
				temp2 = temp;
				same = true;
			}
		}
		if (same == true)
		{
			del = temp2;
			prev->next = temp2->next;
			delete(del);
		}

		data++;
		same = false;
	}
}
void Search(Student *std, int percent_line, string buff[])
{
	Student *temp;
	int data;
	bool flag = true;
	data = percent_line + 1;

	while (buff[data][0] != '%')
	{
		temp = top;
		while (temp != NULL && flag ==true)
		{
			if (buff[data] != temp->name)
			{
			not_found = true;
			}
			else if (buff[data] == temp->name)
			{
				flag = false;
				cout <<"\n"<<temp->name << " " << temp->score << " WAS FOUND!!\n" << endl;
				not_found = false;
			}


			temp = temp->next;
		}
		if (not_found == true)
		{
			cout << buff[data] << " WAS NOT FOUND!!!!" << endl;
		}

		flag = true;
		not_found = false;
		data++;
	}

}
void SORTASC(Student *top)
{
	Student *temp;
	Student *temp2;

	for (temp = top; temp != NULL; temp = temp->next)
	{
		for (temp2 = top; temp2 != NULL; temp2 = temp2->next)
		{
			if (temp->score < temp2->score)
			{
				swap(temp2->score, temp->score);
				swap(temp2->name, temp->name);

			}
		}

	}
}
void SORTDES(Student *top)
{
	Student *temp;
	Student *temp2;

	for (temp = top; temp != NULL; temp = temp->next)
	{
		for (temp2 = top; temp2 != NULL; temp2 = temp2->next)
		{
			if (temp->score > temp2->score)
			{
				swap(temp2->score, temp->score);
				swap(temp2->name, temp->name);
			}
		}

	}
}
void Visit(Student *std, string label)
{
	Student *temp;

	cout << label << ": " << endl << endl;

	for (temp = std; temp != NULL; temp = temp->next)
	{
		cout << temp->name << " ";
		cout << temp->score << endl;
 	}
	cout << endl;
}


void swap(Student *a, Student *b)
{
	Student temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
