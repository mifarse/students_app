#ifndef _GROUPS_H
#define _GROUPS_H


using namespace std;

extern Group* group_top;
extern int number_of_groups;

void group_push(int, int);
void group_printList();
void group_printStudents(int mode = 0);
void group_increment(int);
bool group_isExists(int);
float group_avg(int arg_title = 0);
void group_delete(int arg_title = 0);
void group_addStudent();
Student* group_getTopStudent(int);
Group* group_getByTitle(int);
#endif // _GROUPS
