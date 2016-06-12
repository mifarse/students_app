#include "structures.h"
#include "groups.h"
#include "students.h"

Group* group_top = 0;
int number_of_groups = 0;

void group_push(int title, int students){
	Group* p;
	if (group_top){
		p = new Group(title, students, group_top);
		group_top = p;
	}
	else {
		group_top = new Group(title, students);
	}
	number_of_groups++;
};

void group_printList(){
	Group* p = group_top;
	if (!number_of_groups)
        cout << "Групп нет. Загрузите или создайте!\n";
	while (p != 0){
		cout << "Номер группы: " << p->title;
		cout << " Количество студентов: " << p->students << endl;
		p = p->next;
	}
}

void group_increment(int title){
    Group* p = group_top;
    while (p != 0){
		if (p->title == title){
            p->students += 1;
            break;
		} else {
            p = p->next;
		}
	}
}

bool group_isExists(int title){
    Group* p = group_top;
    bool flag = false;

    while (p != 0){
		if (p->title == title){
            flag = true;
            break;
		} else {
            p = p->next;
		}
	}
	return flag;
}

Group* group_getByTitle(int title){
    Group* p = group_top;
    while (p != 0){
		if (p->title == title){
            p->student_top;
            break;
		} else {
            p = p->next;
		}
	}
	return p;
}

void group_printStudents(int mode){
    int title; int i; bool print = true;
    group_printList();
    cout << "Номер группы для загрузки: ";
    cin >> title;
    if (cin){
        Group* g = group_getByTitle(title);
        if (g){
            Student* s = g->student_top;
            switch (mode){
                case 0: {
                    while (s){
                        student_print(s);
                        s = s->next;
                    }
                    break;
                }
                case 5:{
                    cout << "Все отличники группы №" << title << endl;
                    while (s){
                        for (i = 0; i < 7; i++){
                            if (s->marks[i] != 5){
                                print = false;
                                break;
                            }
                        }
                        if (print){
                            printf("%-25s \t %6i  %-12s  %-11s  ", s->fullname, s->studnumber, s->bdate, s->phone);
                            for (i = 0; i < 7; i++)
                                cout << s->marks[i];
                            cout << endl;
                        }
                        s = s->next;
                        print = true;
                    }
                    break;
                }
                case 2:{
                    print = false;
                    cout << "Все двоечники группы №" << title << endl;
                    while (s){
                        for (i = 0; i < 7; i++){
                            if (s->marks[i] == 2){
                                print = true;
                                break;
                            }
                        }
                        if (print){
                            printf("%-25s \t %6i  %-12s  %-11s  ", s->fullname, s->studnumber, s->bdate, s->phone);
                            for (i = 0; i < 7; i++)
                                cout << s->marks[i];
                            cout << endl;
                        }
                        s = s->next;
                        print = false;
                    }
                    break;
                }
            }
        } else {
            cout << "Группа не найдена. Посмотрите список загруженных групп.";
        }
    } else {
        cout << "Некорректный ввод данных!";
        cin.clear();  cin.ignore(256, '\n');
    }
}

float group_avg(int arg_title){
    int title, i; float avg = 0;
    if (arg_title == 0){
        cout << "Номер группы: ";
        cin >> title;
    } else title = arg_title;
    Group* g = group_getByTitle(title);
    if (g){
        Student* s = g->student_top;
        while (s){
            avg += student_avg(s);
            s = s->next;
        }
        return avg/float(g->students);
    } else {
        cout << "Группа по запросу не найдена.";
        return avg;
    }
}

void group_delete(int arg_title){
    int title, i;
    if (arg_title == 0){
        cout << "Номер группы для удаления: ";
        cin >> title;
    } else title = arg_title;
    Group* g = group_getByTitle(title);
    Group* t;
    if (g){
        Student* s = g->student_top;
        Student* p;
        while (s){
           p = s;
           s = s->next;
           delete[] p;
        }
        t = group_top;
        if (t == g){
            group_top = t->next;
        }
        while (t){
            if (t->next == g){
                t->next = g->next;
                break;
            }
            t = t->next;
        }
        delete[] g;
        cout << "Все студенты группы удалены. Группа удалена. \n";

    } else {
        cout << "Неудачное удаление. Группа не найдена\n";
    }
}

void group_addStudent(){
    int title; Student* s; char fullname[100], marks[7], bdate[12];
    int studnumber; char phone[11];
    cout << "Добавить студента в группу №: ";
    cin >> title;
    if (cin){
        if(group_getByTitle(title)){
            cout << "Введите имя студента: ";
            cin.ignore(256, '\n');
            cin.getline(fullname, sizeof(fullname));
            s = student_push(title, fullname);
            strcpy(s->fullname, fullname);
            cout << "№ студбилета: ";
            cin >> studnumber;
            if (cin) {
                s->studnumber = studnumber;
                cout << "Дата рождения ГГГГ-ММ-ДД: ";
                cin >> bdate;
                strcpy(s->bdate, bdate);
                cout << "Мобильный телефон: ";
                cin >> phone;
                strcpy(s->phone, phone);
                cout << "Оценки студента (7 цифр в строчку): ";
                cin >> marks;
                strcpy(s->raw_marks, marks);
                student_addMarks(s, marks);
            } else {
                cout << "Неудачный ввод. Студент не добавлен. ";
                cin.clear();
                cin.ignore(256, '\n');
                student_delete(s);
            }
        } else {
            cout << "Ошибычкэ. Группа не найдена.";
        }
    } else {
        cout << "Что-то пошло не так...";
        cin.clear();
        cin.ignore(256, '\n');
    }
}
