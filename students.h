#ifndef _STUDENTS_H
#define _STUDENTS_H

#ifndef _GROUPS_H
#include "groups.h"
#endif // _GROUPS

Student* student_push(int, char*);
void student_addMarks(Student*, char*);
float student_avg(Student*);
void student_print(Student*);
void student_delete(Student* s = 0, int studnumber = 0);

#endif // STUDENTS_H

