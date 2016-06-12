#include "structures.h"
#include "students.h"

Student* student_push(int group_title, char* flow_fullname){
	Group* g; Student* p, *aim;
	bool already_pushed = false;
	g = group_getByTitle(group_title);
	if (g){
        if ( g->student_top ){
            p = g->student_top;

            if (strcmp(flow_fullname, p->fullname) < 0){
                aim = new Student(p);
                g->student_top = aim;
                already_pushed = true;
            } else {
                while (p->next != 0){
                    if (strcmp(flow_fullname, p->next->fullname) < 0){
                        aim = new Student(p->next);
                        p->next = aim;
                        break;
                    }
                    p = p->next;
                }

                if (p->next == 0){
                    aim = new Student();
                    p->next = aim;
                }
            }
        }
        else {
            g->student_top = new Student();
            aim = g->student_top;
        }
    }
	return aim;
};

void student_addMarks(Student* man, char* marks_str){
    int marks = atoi(marks_str);
    int i = 0;
    man->marks = new int[7];
    while(marks){
        man->marks[i] = marks % 10;
        marks /= 10;
        i++;
    }
}

float student_avg(Student* man){
    int i;
    float avg = 0;
    for (i = 0; i < 7; i++)
        avg += float(man->marks[i]) / 7;
    return avg;
}

void student_print(Student* s){
    int i;
    printf("%-25s \t %6i  %-12s  %-11s  ", s->fullname, s->studnumber, s->bdate, s->phone);
    for (i = 0; i < 7; i++){
        cout << s->marks[i];
    }
    cout << endl;
}

void student_delete(Student* s, int studnumber){
    Group* g = group_top; bool student_found = false;
    Student*t;
    if (!s){
        cout << "Удаление студента по номеру студбилета: ";
        cin >> studnumber;
        while (g && !student_found){
            s = g->student_top;
            while (s){
                if (s->studnumber == studnumber){
                    student_found = true;
                    break;
                }
                s = s->next;
            }
            if (student_found) break;
            g = g->next;
        }
        if (student_found){
            t = g->student_top;
            if (t == s){
                g->student_top = t->next;
            }
            while (t){
                if (t->next == s){
                    t->next = s->next;
                    break;
                }
                t = t->next;
            }
            cout << "Студент найден и удалён: " << s->fullname;
            delete[] s;
        } else {
            cout << "Студент не найден... ";
        }
    } else {
        while (g && !student_found){
            t = g->student_top;
            if (t == s){
                g->student_top = t->next;
                break;
            }
            while (t){
                if (t->next == s){
                    t->next = s->next;
                    student_found = true;
                    break;
                }
                t = t->next;
            }
            g = g->next;
        }
        cout << "Студент найден и удалён: " << s->fullname;
        delete[] s;
    }
}
