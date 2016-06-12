#ifndef STRUCTURES
#define STRUCTURES
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <ctime>

#endif // STRUCTURES
using namespace std;

struct Student
{
    Student(Student * n = 0){
        next  = n;
    }

    char fullname[100];
    int  studnumber;
    char bdate[12];
    char phone[11];
    int* marks;
    char raw_marks[7];
    Student* next;
};

struct Group
{
	Group(int a, int b, Group* c = 0){
		title = a;
		students = b;
		next = c;
	}
	int title;
	int students;
	Group* next;
    Student* student_top = 0;
};


