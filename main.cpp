#include "structures.h"
#include "groups.h"
#include "students.h"
#include "files.h"
#include "flow.h"

void home(bool &leave_loop, bool is_file_loaded){
    system("clear");
    cout << "[ КОЛ-ВО ГРУПП В ПРОГРАММЕ: " << number_of_groups  << " ]" << endl;
    cout << "> ГЛАВНОЕ МЕНЮ " << endl;
    cout << "МЕНЮ ПРИЛОЖЕНИЯ\n (1) ФАЙЛ\n (2) ГРУППА\n (3) ПОТОК" << endl;
    leave_loop = true;
};

int main(){
    bool is_file_loaded = false, leave_loop = false;
    int i, select = 0, title;
    char menu_main[]   = "МЕНЮ ПРИЛОЖЕНИЯ\n (1) ФАЙЛ\n (2) ГРУППА\n (3) ПОТОК";
    char menu_file[]   = "МЕНЮ ФАЙЛА\n (1) Зазгрузить .csv\n (2) Загрузить из бинарника\n (3) Сохранить структуру в файл .csv\n (4) Сохранить структуру в бинарный файл";
    char menu_group[]  = "МЕНЮ ГРУПП\n (1) Вывести список групп\n (2) Вывести студентов группы №\n (3) Вывести отличников группы №\n (4) Вывести двоечников группы №\n (5) Средний балл группы №\n (6) Создать новую группу\n (7) Удалить группу по номеру\n (8) Добавить студента в группу №\n (9) Удалить студента  по номеру студбилета";
    char menu_flow[]  = "МЕНЮ ПОТОКА\n (1) Вывести средний бал всего потока\n (2) Вывод студентов со средним баллом выше, чем у потока\n (3) Вывести отличников (круглых)";

    while(1){
        switch(select){
            case 1:{
                cout << "[ КОЛ-ВО ГРУПП В ПРОГРАММЕ: " << number_of_groups  << " ]" << endl;
                cout << "> ГЛАВНОЕ МЕНЮ > ФАЙЛ " << endl;
                cout << menu_file;
                while (!leave_loop){
                    cout << endl << "Ввод пункта меню ФАЙЛ >";
                    cin >> select;
                    if (cin) {
                        switch(select){
                            case 1:{
                                files_load(is_file_loaded);
                                break;
                            }
                            case 2:{
                                files_loadBinary();
                                break;
                            }
                            case 3:{
                                files_save();
                                break;
                            }
                            case 4:{
                                files_saveBinary();
                                break;
                            }
                            default:{
                                home(leave_loop, is_file_loaded);
                            }
                        }
                    } else {
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                }
                break;
            }
            case 2:{
                cout << "[ КОЛ-ВО ГРУПП В ПРОГРАММЕ: " << number_of_groups  << " ]" << endl;
                cout << "> ГЛАВНОЕ МЕНЮ > ГРУППА " << endl;
                cout << menu_group << endl;

                while (!leave_loop){
                    cout << endl << "Ввод пункта меню ГРУППА >";
                    cin >> select;
                    if (cin) {
                        switch(select){
                            case 1:{
                                group_printList();
                                break;
                            }
                            case 2:{
                                    group_printStudents();
                                break;
                            }
                            case 3:{
                                group_printStudents(5);
                                break;
                            }
                            case 4:{
                                group_printStudents(2);
                                break;
                            }
                            case 5:{
                                cout << group_avg();
                                break;
                            }
                            case 6:{
                                cout << "Введите номер группы для создания: ";
                                cin >> title;
                                if (cin){
                                    if (group_isExists(title)){
                                        cout << "Группа с таким номером уже существует.";
                                    } else {
                                        group_push(title, 0);
                                        cout << "Группа успешно добавлена!";
                                    }
                                } else {
                                    cout << "Ошибка правильности ввода.";
                                    cin.clear();
                                    cin.ignore(256, '\n');
                                    }
                                break;
                            }
                            case 7:{
                                group_delete();
                                break;
                            }
                            case 8:{
                                group_addStudent();
                                break;
                            }
                            case 9:{
                                student_delete();
                                break;
                            }
                            default:{
                                home(leave_loop, is_file_loaded);
                            }
                        }
                    } else {
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                }
                break;
            }
            case 3:{
                cout << "[ КОЛ-ВО ГРУПП В ПРОГРАММЕ: " << number_of_groups  << " ]" << endl;
                cout << "> ГЛАВНОЕ МЕНЮ > ПОТОК " << endl;
                cout << menu_flow << endl;
                while (!leave_loop){
                    cout << endl << "Ввод пункта меню ПОТОК >";
                    cin >> select;
                    if (cin) {
                        switch(select){
                            case 1:{
                                cout << "Средний балл потока: " << flow_avg();
                                break;
                            }
                            case 2:{
                                flow_printGoodStudents();
                                break;
                            }
                            case 3:{
                                flow_printExcellentStudents();
                                break;
                            }
                            default:{
                                home(leave_loop, is_file_loaded);
                            }
                        }
                    } else {
                        cin.clear();
                        cin.ignore(256, '\n');
                    }
                }
                break;
            }
            default:{
                home(leave_loop, is_file_loaded);
            }
        }
        cout << "Ввод пункта главного меню >";
        cin >> select;
        if (!cin) {
            cin.clear();
            cin.ignore(256, '\n');
        }
        system("clear");
        leave_loop = false;
    }

	return 0;
}
