#include <iostream>
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <cstring>
#include <cstdlib>

using namespace std;

struct stud {
    long nz;
    char fioLudi[80], gr[6];
    float rs;
    char ball[16];
} st;

int z = sizeof(stud);
char sh[][250] =
{ "                             Студенты факультета ",
    "|==============|=================|==================|=======================|======================|",
    "|№ зачет книжки|    Фамилия      |Название группы   |    Сред.вступ.балл    |   Размер стипендии   |",
    "|==============|=================|==================|=======================|======================|",
    "|--------------|-----------------|------------------|-----------------------|----------------------|"
};

ifstream fin;
ofstream fout;
fstream io;

void p();
void cht();
void sozd();
void dop();
void zf();
void poisk1();
void poisk2();
void kor();
void filtr(char*);
void psh();

int main() {
    setlocale(LC_ALL, "RUS");
    fout.open("lr12.txt");
    if (!fout) {
        cout << "Ошибка при открытии файла результатов";
        system("pause");
        return 1;
    }
    sozd();
    cht();
    dop();
    cht();
    poisk1();
    poisk2();
    kor();
    cht();
    fout.close();
    return 0;
}

void psh() {
    for (int i = 0; i < 6; i++)
        fout << sh[i] << endl;
}

void p() {
    fout << "|" << setw(14) << st.nz << "|" << setw(17) << st.fioLudi << "|"
        << setw(18) << st.gr << "|" << setw(23) << st.ball << "|" << setw(22) << st.rs << "|\n";
}

void sozd() {
    fout << " СОЗДАНИЕ ФАЙЛА ";
    // Перенос вывода сообщения на создание файла перед открытием файла данных
    io.open("binary.bin", ios::out | ios::binary);
    if (!io) {
        cout << "Ошибка открытия нового бинарного файла";
        system("pause");
        return;
    }
    fin.open("sozd.txt");
    if (!fin) {
        cout << "Ошибка при открытии файла данных";
        system("pause");
        return;
    }
    psh();
    zf();
    fin.close();
    io.close();
}

void dop() {
    // Перенос вывода сообщения на дополнение файла перед открытием файлов
    fout << "\n\n ДОПОЛНЕНИЕ ФАЙЛА НОВЫМИ ЗАПИСЯМИ" << endl;
    fin.open("dop.txt", ios::in); // открытие файла данных для дополнения
    if (!fin) {
        cout << "Ошибка открытия файла данных для дополнения";
        system("pause");
        return;
    }
    //открытие бинарного файла в режиме дополнения
    // Исправление ошибки в названии файла - должен быть "binary.bin", а не "binary.cpp"
    io.open("binary.bin", ios::app | ios::binary);
    if (!io) {
        cout << "Ошибка открытия бин. файла для дополнения";
        system("pause");
        return;
    }
    for (int i = 1; i < 5; i++)
        fout << sh[i] << endl;
    zf();
    fin.close(); io.close();
}

void cht() {
    int n = 0;
    float s = 0;
    // Перенос вывода сообщения на чтение файла перед открытием файла
    fout << "\n  ЧТЕНИЕ ФАЙЛА\n";
    fin.open("binary.bin", ios::in | ios::binary);
    if (!fin) {
        cout << "Ошибка открытия бинарного файла для чтения";
        system("pause");
        return;
    }
    psh();
    while (fin.read((char*)&st, z)) {
        p();
        s += st.rs;
        n++;
    }
    fout << sh[5] << endl << "Суммарная стипендия = " << s << endl
        << "Средняя стипендия = " << s / n << endl
        << "Количество структур в файле = " << n << endl;
    fin.close();
}

void zf() {
    char T[80];
    while (!fin.eof()) {
        fin >> st.nz;
        fin.get(st.fioLudi, 11);
        filtr(st.fioLudi);
        fin.get(st.gr, 17);
        filtr(st.gr);

        fin >> st.rs;
        fin.getline(T, 80);
        io.write((char*)&st, z);
        p();
    }
    fout << sh[5] << endl;
}

void filtr(char* Stroka) {
    char Source[255] = "";
    int x, x1 = 0, x2 = strlen(Stroka) - 1;
    while (Stroka[x1] == ' ') x1++;
    while (Stroka[x2] == ' ' || Stroka[x2] == '\n') x2--;
    for (x = x1; x <= x2; x++)
        Source[x - x1] = Stroka[x];
    Source[x - x1] = '\0';
    strcpy(Stroka, Source);
}

void poisk1() {
    char name[20]; //символьный массив для хранения поискового признака
    fin.open("poisk1.txt");  //открытие файла данных для поиска
    if (!fin) {
        cout << "Ошибка открытия файла данных для поиска 1";
        system("pause");
        return;
    }
    fout << "\n\n  ПОИСК ПО ФАМИЛИИ СТУДЕНТА\n";
    io.open("binary.bin", ios::in | ios::binary); //открытие бин. ф. для чтения
    if (!io) {
        cout << "Ошибка открытия бинарного файла для чтения ";
        system("pause");
        return;
    }
    while (fin.peek() != EOF) {
        fin.getline(name, 20);
        filtr(name);
        fout << "\nИщем студента с фамилией - \"" << name << "\"" << endl;
        if (!strcmp(name, "")) {
            fout << "Нет фамилии для поиска\n";
            continue;
        }
        io.seekg(0, ios::beg); //указатель бин. файла устанавливается на начало
        while (io.peek() != EOF) { //пока не достигнут символ конца файла
            io.read((char*)&st, z); //читаем из файла одну структуру в st 
            if (strcmp(st.fioLudi, name) == 0) { //сравниваем поле fio структуры st с name
                p();
                goto m; //если совпадение выводим данные структуры и управление передается на метку m
            }
        }
        fout << "Студент с фамилией \"" << name << "\" не найден" << endl;
    m:;
    }
    fin.close();
    io.close();
}

void poisk2() {
    char grup[8];
    unsigned int stip;
    fin.open("poisk2.txt", ios::in);
    if (!fin) {
        cout << "Ошибка открытия файла данных для поиска 2";
        system("pause");
        return;
    }
    fout << "\n\n ПОИСК ПО НАИМЕНОВАНИЮ ГРУППЫ СТУДЕНТА И"
        "ПО РАЗМЕРУ СТИПЕНДИИ\n";
    io.open("binary.bin", ios::in | ios::out | ios::binary);
    if (!io) {
        cout << "Ошибка открытия бинарного файла для чтения ";
        system("pause");
        return;
    }
    while (fin.peek() != EOF) {
        fin.getline(grup, 8);
        int k = 0;
        fin >> stip >> ws;
        fout << "\nИщем в группе -" << "\"" << grup << "\""
            << " студентов со стипендией > = " << stip << endl;
        if ((!strcmp(grup, "")) && (stip == 0.0)) {
            fout << "Нет для поиска ни группы, ни стипендии \n";
            continue;
        }

        io.seekg(0, ios::beg);
        while (!io.eof() && io.read((char*)&st, z))
            if ((!strcmp(st.gr, grup) || !strcmp(grup, "")) && (stip <= st.rs || stip == 0)) {
                p(); k++;
            }
        if (!k) fout << "Таких студентов нет" << endl;
    }
    fin.close(); io.close();
}


void kor() {
    char t[80];		//массив - буфер
    char name[25]; //для хранения фамилии студента – поисковый признак 
    float stip;			//переменная для новой стипендии
    fout << "\n\n		КОРРЕКЦИЯ ФАЙЛА\n\n";
    fin.open("kor.txt", ios::in);
    if (!fin) {
        cout << "Ошибка открытия файла данных для коррекции";
        system("pause");
        return;
    }
    while (fin.peek() != EOF) {	//1 цикл ввода данных для коррекции
        fin.get(name, 17); filtr(name); fin >> stip; fin.getline(t, 80);
        int k = 0;
        if (!strcmp(name, ""))
        {
            fout << "\nНет фамилии для поиска структуры\n"; continue;
        }
        //открытие бинарного файла в режиме чтения и записи
        io.open("binary.cpp", ios::in | ios::out | ios::binary);
        if (!io) {
            cout << "Ошибка открытия бин. файла для его коррекции";
            system("pause");
            return;
        }
        while (io.read((char*)&st, z)) // 2
            if (!strcmp(st.fioLudi, name)) {                //если найдена структура 
                p(); st.rs = stip; p();     //изменяем ее
                io.seekp(-z, ios::cur); //смещаем указатель файла на одну структуру назад
                io.write((char*)&st, z); //запись в файл откорректированной структуры
                k++; break;
            } // while 2
        if (!k) fout << "Студент с ФИО - " << name << " не найден" << endl;
        io.close();
    }// while 1
    fin.close(); io.close();

}
}
