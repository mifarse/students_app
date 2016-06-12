#include "structures.h"
#include "flow.h"
#include "students.h"


float flow_avg(){
    float mark = 0;
    int i = 0; Group* g = group_top;
    while (g){
        mark += group_avg(g->title);
        g = g->next;
        i++;
    }
    mark /= i;
    return mark;
}

void flow_printGoodStudents(){
    char filename[100];
    char date[50];
    time_t now = time(0);
    tm *ltm = localtime(&now);
    float mark = flow_avg();
    Group*g = group_top;
    Student*s;
    int i = 0, j = 0;


    strftime(filename, 100, "Выше среднего %d-%m-%Y %I:%M:%S.txt",ltm);
    ofstream report;
    report.open(filename);
    strftime(date, 50, "%c", ltm);
    report << "ОТЧЕТ ПО ПОТОКУ СТУДЕНТОВ\nФункция: вывод студентов с баллом выше средного\nВремя запроса: " << date << endl << "Средний балл на потоке: " << mark << "\n\n";

    while (g){
        s = g->student_top;
        while (s){
            if (student_avg(s) > mark){
                student_print(s);
                report << s->fullname << " (гр. " << g->title << ") имеет средний балл " << student_avg(s) << endl;
                j++;
            }
            i++;
            s = s->next;
        }
        g = g->next;
    }
    report << "\n\nКоличество студентов: " << j << " из " << i << ". Это составляет " << float(j)*100/i << "%";
    cout << "Отчет о студентах сохранен в файл " << filename;
}

void flow_printExcellentStudents(){
    Group*g = group_top;
    Student*s; char filename[100]; char date[50];
    int i = 0, j = 0;

    time_t now = time(0);
    tm *ltm = localtime(&now);
    strftime(filename, 100, "Отличники %d-%m-%Y %I:%M:%S.txt",ltm);
    ofstream report;
    report.open(filename);
    strftime(date, 50, "%c", ltm);
    report << "ОТЧЕТ ПО ПОТОКУ СТУДЕНТОВ\nФункция: вывод отличников\nВремя запроса: " << date << "\n\n";

    while (g){
        s = g->student_top;
        while (s){
            if (student_avg(s) >= 5 ){
                student_print(s);
                report << s->fullname << " (гр. " << g->title << ")\n";
                j++;
            }
            i++;
            s = s->next;
        }
        g = g->next;
    }

    report << "\n\nКоличество студентов: " << j << " из " << i << ". Это составляет " << float(j)*100/i << "%";
    cout << "Отчет о студентах сохранен в файл " << filename;
}
