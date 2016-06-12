#include "structures.h"
#include "groups.h"
#include "students.h"
#include "files.h"

void files_load( bool &fbool ){
    string row;
    char rowchar[50];
    char *col;
    char file_address[100];
    int i = 0; // Для определения столбца базы
    int group_id;
    Student* dude;

    system("echo 'Доступные файлы:' && ls *.csv");
    cout << endl << "Адрес файла для загрузки базы: ";
    cin >> file_address;

    fstream database;
    database.open(file_address);

    if (database){
        cout << file_address << " Загружаем файл...\n";
        fbool = true;
        while(!database.eof()){
            getline(database, row);
            strcpy(rowchar, row.c_str());
            col = strtok(rowchar, ",");
            while (col != NULL){
                switch(i){
                    case 0: {
                        group_id = atoi(col);
                        if (group_isExists(group_id)){
                            group_increment(group_id);
                        } else {
                            group_push(group_id, 1);
                        }
                        break;
                    }
                    case 1: {
                        dude = student_push(group_id, col);
                        strcpy(dude->fullname, col);
                        break;
                    }
                    case 2: {
                        dude->studnumber = atoi(col);
                        break;
                    }
                    case 3: {
                        strcpy(dude->bdate, col);
                        break;
                    }
                    case 4: {
                        strcpy(dude->phone, col);
                        break;
                    }
                    case 5: {
                        strcpy(dude->raw_marks, col);
                        student_addMarks(dude, col);
                        break;
                    }
                }
                i++;
                if (i > 5) i = 0;
                col = strtok(NULL, ",");
            }
        }
        cout << "Успешная загрузка.";
        database.close();
    } else {
        cout << "Ошибка. Файл не найден.\n";
        fbool = false;
    }
};

void files_save(){
    char filename[100]; int title, i;
    Student* s; Group* g = group_top;

    cout << "Сохранить текущую базу данных в бинарный файл: ";
    cin >> filename;

    ofstream database;
    database.open(filename);

    while (g){
        s = g->student_top;
        title = g->title;
        while(s){
            database << title << "," << s->fullname << "," << s->studnumber << "," << s->bdate << "," << s->phone << ",";
            for (i = 0; i < 7; i++){
                database << s->marks[i];
            }
            database << "\n";
            s = s->next;
        }
        g = g->next;
    }
    cout << "Все студенты сохранены в файл: " << filename;
    database.close();
}

void files_saveBinary(){
    char filename[100]; int title, i;
    Student* s; Group* g = group_top;

    cout << "Название бинарного файла: ";
    cin >> filename;

    ofstream database;
    database.open(filename, ios::binary|ios::out);

    database.write(reinterpret_cast<char*>(&number_of_groups), sizeof(int));
    while (g){
        database.write( reinterpret_cast<char*>(g), sizeof(Group) );
        s = g->student_top;
            while(s){
                database.write( reinterpret_cast<char*>(s), sizeof(Student) );
                s = s->next;
            }
        g = g->next;
    }
    cout << "Файл сохранен!";
    database.close();
}

void files_loadBinary(){
    char filename[100]; int title, i, j, m, groups;
    Student temp_student, *s; Group temp_group(0,0);

    cout << "Доступные файлы в этой папке:";
    system("echo 'Доступные файлы:' && ls *.bin");
    cin >> filename;

    ifstream database;
    database.open(filename, ios::binary|ios::in);

    if (database){
        database.read(reinterpret_cast<char*>(&groups), sizeof(int));
        for (i = 0; i < groups; i++){
            database.read(reinterpret_cast<char*>(&temp_group), sizeof(Group));
            cout << temp_group.title << endl;
            if (!group_isExists(temp_group.title))
                group_push(temp_group.title, 0);

            for (j = 0; j < temp_group.students; j++){
                group_increment(temp_group.title);
                database.read(reinterpret_cast<char*> (&temp_student), sizeof (Student));
                s = student_push(temp_group.title, temp_student.fullname);
                strcpy(s->fullname,   temp_student.fullname);
                strcpy(s->bdate,      temp_student.bdate);
                strcpy(s->phone,      temp_student.phone);
                s->studnumber = temp_student.studnumber;
                strcpy(s->raw_marks, temp_student.raw_marks);
                student_addMarks(s, temp_student.raw_marks);
            }

        }
        cout << "Файл загружен!";
        database.close();
    }
}
